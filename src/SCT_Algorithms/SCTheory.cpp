#include <vector>
#include <tuple>
#include <map>
#include "agent.h"
#include "options.h"
#include "pairsofopts.h"
#include "socialprefnode.h"
#include "socialchoicegraph.h"

/* Possible optimizations: binary search in rank_generation. Harder, better, faster, stronger.
 *						   order agent's orderings according to alternatives' values
 *						   a ranking class/struct. Easier to manipulates, when compared to tuples
*/

// Generates, without repetition, all combinations of pairs of alternatives
template<typename Prefs> std::vector<PairsOfOpts<Prefs>> pair_generation( std::vector<Agent<Prefs>>& listofagents ){

	PairsOfOpts<Prefs> compairs;

	std::vector<PairsOfOpts<Prefs>> paircomp{ };

	// get all possible combination of pairs, including repeated pairs
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

	// delete repeated combinations
	for( int i = 0; i < paircomp.size( ); ++i ){

		std::tuple<Options<Prefs>, Options<Prefs>> pairs{ };

		std::get<0>( pairs ) = paircomp[ i ].ypref;
		std::get<1>( pairs ) = paircomp[ i ].xpref;

		for( int j = i; j < paircomp.size( ); ++j ){

			// checks if there are pairs a and b s.t. b == inverse( a ), i.e., a == ( x, y ) and b == ( y, x )
			// adds to No Repeated Pairs only one version of the repeated pairs, i.e., ( x, y ) OR ( y, x ),
			// but never both
			if( paircomp[ j ].xpref == std::get<0>( pairs ) && paircomp[ j ].ypref == std::get<1>( pairs ) &&
				paircomp[ j ].xpref != std::get<1>( pairs ) && paircomp[ j ].ypref != std::get<0>( pairs )){

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
template<typename Prefs> std::vector<std::tuple<Options<Prefs>, Options<Prefs>, int, int, int>> rank_generation( std::vector<Agent<Prefs>>& listofagents ){

	// Holder for a pair of options
	PairsOfOpts<Prefs> compairs{ };

	std::vector<PairsOfOpts<Prefs>> ordering = pair_generation( listofagents );

	// quintuples ( x, y, xval, yval, ival ) and then map occurrences into val
	std::tuple<Options<Prefs>, Options<Prefs>, int, int, int> quintuples{ };

	std::vector<std::tuple<Options<Prefs>, Options<Prefs>, int, int, int>> ranking{ };

	// Checks how a pair ( x, y ) is ranked for each agent
	for( int i = 0; i < ordering.size( ); ++i ){

		// Hold both alternatives that will be checked
		compairs.xpref = ordering[ i ].xpref;
		compairs.ypref = ordering[ i ].ypref;

		for( int j = 0; j < listofagents.size( ); ++j ){

			for( int k = 0; k < listofagents[ j ].get_preferences( ).size( ); ++ k ){

				// Search for x in agent's preferences
				if( listofagents[ j ].get_preferences( )[ k ].get_alternatives( ) == compairs.xpref.get_alternatives( ) )

					std::get<0>( quintuples ) = listofagents[ j ].get_preferences( )[ k ];

				// Search for y in agent's preferences
				if( listofagents[ j ].get_preferences( )[ k ].get_alternatives( ) == compairs.ypref.get_alternatives( ) )

					std::get<1>( quintuples ) = listofagents[ j ].get_preferences( )[ k ];
			}

			// Compares x and y values. Increments xval, yval, or ival accordingly
			if( std::get<0>( quintuples ).get_value( ) > std::get<1>( quintuples ).get_value( ) )

				++std::get<2>( quintuples );

			else if( std::get<0>( quintuples ).get_value( ) < std::get<1>( quintuples ).get_value( ) )

				++std::get<3>( quintuples );

			else if( std::get<0>( quintuples ).get_value( ) == std::get<1>( quintuples ).get_value( ) )

				++std::get<4>( quintuples );
		}

		// Stores the ranked tuple
		ranking.push_back( quintuples );

		// Resets the tuple for a new ranking
		quintuples = { };
	}

	// returns a vector of quintuples
	return ranking;
}

template<typename Prefs> void condorcet_paradox( std::vector<Agent<Prefs>>& listofagents ){

	std::vector<std::tuple<Options<Prefs>, Options<Prefs>, int, int, int>> rank = rank_generation( listofagents );

	SocialChoiceGraph<Prefs> choicegraph{ };

	choicegraph.initializvec( listofagents );

	choicegraph.makegraph( rank );

	//SocialPrefNode<Prefs> schoicegraph[ rank.size( ) ];

	// create a graph data structure only for the cycle


	for( int i = 0; i < rank.size( ); ++ i ){

		std::cout << "X: " << std::get<0>( rank[ i ] ).get_alternatives( ) << "\tY: " << std::get<1>( rank[ i ] ).get_alternatives( )
				  << "\tXval: " << std::get<2>( rank[ i ] ) << "\tYval: " << std::get<3>( rank[ i ] ) << "\tIval:  "
				  << std::get<4>( rank[ i ] ) << "\n";
	}

	// check for cycles

}
