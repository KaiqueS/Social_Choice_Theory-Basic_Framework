#include<vector>
#include <tuple>
#include <map>
#include "agent.h"
#include "options.h"
#include "pairsofopts.h"

// Generates, without repetition, all combinations of pairs of alternatives
template<typename Prefs> std::vector<PairsOfOpts<Prefs>> pair_generation( std::vector<Agent<Prefs>>& listofagents ){

	PairsOfOpts<Prefs> compairs;

	std::vector<PairsOfOpts<Prefs>> paircomp{ };

	// get all possible combination of pairs - ok
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

			if( paircomp[ j ].xpref == std::get<0>( pairs ) && paircomp[ j ].ypref == std::get<1>( pairs ) &&
				paircomp[ j ].xpref != std::get<1>( pairs ) && paircomp[ j ].ypref != std::get<0>( pairs )){

				noreppairs.push_back( paircomp[ i ] );
			}
		}
	}

	// return ordering
	return noreppairs;
}

/*  */
template<typename Prefs> Options<Prefs> condorcet_paradox( std::vector<Agent<Prefs>>& listofagents ){

	Options<Prefs> result{ };

	PairsOfOpts<Prefs> compairs{ };

	std::vector<PairsOfOpts<Prefs>> ordering = pair_generation( listofagents );

	// check each combination for all agents
	for( int i = 0; i < ordering.size( ); ++i ){

		compairs.xpref = ordering[ i ].xpref;
		compairs.ypref = ordering[ i ].ypref;

		std::tuple<Options<Prefs>, Options<Prefs>, int, int> quadruples{ };

		for( int j = 0; j < listofagents.size( ); ++j ){

			// quadruples ( x, y, xval, yval ) and then map occurrences into val
			if( listofagents[ i ].get_preferences( )[ j ] == )
		}
	}

	// one counter per pair
}
