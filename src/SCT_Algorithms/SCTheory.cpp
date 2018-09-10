#include <vector>
#include <tuple>
#include <map>
#include "agent.h"
#include "options.h"
#include "pairsofopts.h"
#include "socialprefnode.h"
#include "socialchoicegraph.h"
#include "pairwiserank.h"

// TODO: REFACTOR! Remove all uses of Tuple. Replace it with a custom data structure -> DONE

/* Possible optimizations: binary search in rank_generation. Harder, better, faster, stronger.
 *						   order agent's orderings according to alternatives' values
*/

// Generates, without repetition, all combinations of pairs of alternatives -> REFACTOR! Remove all uses of Tuple. Replace it with a custom data structure <- -> DONE
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

/* Ranks alternatives. The ranking has a form of a vector of quintuples ( x, y, xval, yval, ival ), where
 * x and y are the alternatives, and the vals represent how many agents prefer one over the other. ival
 * represents indifference. The ranking operates in accord to how agents ranks pairs of alternatives */
template<typename Prefs> std::vector<PairWiseRank<Prefs>> rank_generation( std::vector<Agent<Prefs>>& listofagents ){ // maybe try to return a reference?

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

template<typename Prefs> void condorcet_paradox( std::vector<Agent<Prefs>>& listofagents, std::vector<PairWiseRank<Prefs>>& rank, SocialChoiceGraph<Prefs>& graph ){

	for( int i = 0; i < rank.size( ); ++ i ){

			std::cout << "X: " << rank[ i ].get_optx( ).get_alternatives( )
					  << "\tY: " << rank[ i ].get_opty( ).get_alternatives( )
					  << "\tXval: " << rank[ i ].get_xval( )
					  << "\tYval: " << rank[ i ].get_yval( )
					  << "\tIval: " << rank[ i ].get_ival( ) << "\n";
	}

	graph.initializvec( listofagents );

	graph.makegraph( rank );

	//SocialPrefNode<Prefs> schoicegraph[ rank.size( ) ];

	// create a graph data structure only for the cycle

	// check for cycles

}
