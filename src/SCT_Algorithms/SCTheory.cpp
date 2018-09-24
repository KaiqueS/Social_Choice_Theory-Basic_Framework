#include <vector>
#include <tuple>
#include <map>
#include "agent.h"
#include "options.h"
#include "pairsofopts.h"
#include "socialprefnode.h"
#include "pairwiserank.h"
#include "helper_functions.cpp"

/* Possible optimizations: binary search in rank_generation. Harder, better, faster, stronger.
 *						   order agent's orderings according to alternatives' values - enables
 *						   binary search
 */

// Generates, without repetition, all combinations of pairs of alternatives
template<typename Prefs> std::vector<PairsOfOpts<Prefs>> pair_generation( std::vector<Agent<Prefs>>& listofagents ){

	PairsOfOpts<Prefs> compairs;

	std::vector<PairsOfOpts<Prefs>> paircomp{ };

	// gets all possible combination of pairs, including repeated pairs
	for( int i = 0; i < listofagents[ 0 ].get_preferences( ).size( ); ++i ){

		compairs.xpref = listofagents[ 0 ].get_preferences( )[ i ];

		for( int j = 0; j < listofagents[ 0 ].get_preferences( ).size( ); ++j ){

			if( j != i ){

				compairs.ypref = listofagents[ 0 ].get_preferences( )[ j ];

				paircomp.push_back( compairs );
			}
		}
	}

	std::vector<PairsOfOpts<Prefs>> noreppairs{ };

	// deletes repeated combinations
	for( int i = 0; i < paircomp.size( ); ++i ){

		Options<Prefs> invrsx{ }, invrsy{ };

		invrsx = paircomp[ i ].ypref;
		invrsy = paircomp[ i ].xpref;

		for( int j = i; j < paircomp.size( ); ++j ){

			// checks if there are pairs a and b s.t. b == inverse( a ), i.e., a == ( x, y ) and b == ( y, x ).
			// Adds to No Repeated Pairs only one version of the repeated pairs: ( x, y ) OR ( y, x ), but nev-
			// er both
			if( paircomp[ j ].xpref == invrsx && paircomp[ j ].ypref == invrsy &&
				paircomp[ j ].xpref != invrsy && paircomp[ j ].ypref != invrsx ){

				noreppairs.push_back( paircomp[ i ] );
			}
		}
	}

	// returns all combinations without repetitions
	return noreppairs;
}

// Ranks alternatives. The ranking has a form of a vector of quintuples ( x, y, xval, yval, ival ), where
// x and y are the alternatives, and the vals represent how many agents prefer one over the other. ival
// represents indifference. The ranking operates in accord to how agents ranks pairs of alternatives
template<typename Prefs> std::vector<PairWiseRank<Prefs>> rank_generation( std::vector<Agent<Prefs>>& listofagents ){

	// Holder for a pair of options
	PairsOfOpts<Prefs> compairs{ };

	std::vector<PairsOfOpts<Prefs>> ordering = pair_generation( listofagents );

	// quintuples ( x, y, xval, yval, ival ) and then map occurrences into val
	PairWiseRank<Prefs> paircomp{ };

	std::vector<PairWiseRank<Prefs>> ranking{ };


	// Checks how a pair ( x, y ) is ranked for each agent
	for( int i = 0; i < ordering.size( ); ++i ){

		// Hold both alternatives that will be checked
		compairs.xpref = ordering[ i ].xpref;
		compairs.ypref = ordering[ i ].ypref;

		for( int j = 0; j < listofagents.size( ); ++j ){

			for( int k = 0; k < listofagents[ j ].get_preferences( ).size( ); ++ k ){

				// Search for x in agent's preferences
				if( listofagents[ j ].get_preferences( )[ k ].get_alternatives( ) == compairs.xpref.get_alternatives( ) )

					paircomp.set_optx( listofagents[ j ].get_preferences( )[ k ] );

				// Search for y in agent's preferences
				if( listofagents[ j ].get_preferences( )[ k ].get_alternatives( ) == compairs.ypref.get_alternatives( ) )

					paircomp.set_opty( listofagents[ j ].get_preferences( )[ k ] );
			}

			// Compares x and y values. Increments xval, yval, or ival accordingly
			if( paircomp.get_optx( ).get_value( ) > paircomp.get_opty( ).get_value( ) )

				paircomp.incrementx( );

			else if( paircomp.get_optx( ).get_value( ) < paircomp.get_opty( ).get_value( ) )

				paircomp.incrementy( );

			else if( paircomp.get_optx( ).get_value( ) == paircomp.get_opty( ).get_value( ) )

				paircomp.incrementi( );
		}

		// Stores the ranked tuple
		ranking.push_back( paircomp );

		// Resets the tuple for a new ranking
		paircomp = { };
	}

	// returns a vector of quintuples
	return ranking;
}

// Creates a graph GRAPH composed by nodes of alternatives. Relates those nodes according to how the alt-
// ernatives are related to each other, i.e., for three alternatives x, y, and z, if x > y, then, one has
// that y is in x.preferred, and x is in y.worsethan. If x == z, then x is in z.indifference and z is in
// x.indifference
template<typename Prefs> std::vector<SocialPrefNode<Prefs>> make_graph( std::vector<Agent<Prefs>>& listofagents, std::vector<PairWiseRank<Prefs>>& rank, std::vector<SocialPrefNode<Prefs>>& graph ){

	// Initializes nodes' ids. Take as argument the ids from an agent
	for( int i = 0; i < graph.size( ); ++i )

		graph[ i ].set_id( listofagents[ 0 ].get_preferences( )[ i ].get_alternatives( ) );

	// Checks how alternatives are related. Links them accordingly to their relation
	for( int i = 0; i < rank.size( ); ++i ){

		for( int j = 0; j < graph.size( ); ++j ){

			// if x > y
			if( rank[ i ].get_xval( ) > rank[ i ].get_yval( ) ){

				// If graph[ j ] == x, set preferredto = y, i.e., x is preferred to y
				if( graph[ j ].get_id( ) == rank[ i ].get_optx( ).get_alternatives( ) ){

					for( int k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_opty( ).get_alternatives( ) )

							graph[ j ].set_pref( graph[ k ] );
					}
				}

				// Else if graph[ j ] == y, set worse = x, i.e., y is worse than x
				else if( graph[ j ].get_id( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

					for( int k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_optx( ).get_alternatives( ) )

							graph[ j ].set_worse( graph[ k ] );
					}
				}
			}

			// if y > x
			else if( rank[ i ].get_xval( ) < rank[ i ].get_yval( ) ){

				// If graph[ j ] == x, set worsethan = y
				if( graph[ j ].get_id( ) == rank[ i ].get_optx( ).get_alternatives( ) ){

					for( int k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_opty( ).get_alternatives( ) )

							graph[ j ].set_worse( graph[ k ] );
					}
				}

				// Else if scgraph[ j ] == y, set preferences = y
				else if( graph[ j ].get_id( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

					for( int k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_optx( ).get_alternatives( ) )

							graph[ j ].set_pref( graph[ k ] );
					}
				}
			}

			// if x == y
			else if( rank[ i ].get_xval( ) == rank[ i ].get_yval( ) ){

				// If scgraph[ j ] == x, set indiff = y
				if( graph[ j ].get_id( ) == rank[ i ].get_optx( ).get_alternatives( ) ){

					for( int k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

							graph[ k ].set_indiff( graph[ j ] );
						}
					}
				}

				// Else if scgraph[ j ] == y, set indiff = x
				else if( graph[ j ].get_id( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

					for( int k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_optx( ).get_alternatives( ) ){

							graph[ k ].set_indiff( graph[ j ] );
						}
					}
				}
			}
		}
	}

	// Returns the graph
	return graph;
}

template<typename Prefs> void condorcet_paradox( std::vector<Agent<Prefs>>& listofagents, std::vector<PairWiseRank<Prefs>>& rank, std::vector<SocialPrefNode<Prefs>>& graph ){

	// Prints social ranking of alternatives
	for( int i = 0; i < rank.size( ); ++i )

		std::cout << rank[ i ] << "\n";

	std::cout << "\n";

	// Creates a graph. This graph will be checked for cycles
	make_graph( listofagents, rank, graph );

	print_graph( graph );

	std::vector<std::vector<Prefs>> cycles{};

	// check for cycles
	for( int i = 0; i < graph.size( ); ++i ){


	}
}
