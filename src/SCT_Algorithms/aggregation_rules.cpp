#include <vector>
#include "agent.h"
#include "options.h"
#include "pairsofopts.h"
#include "socialprefnode.h"
#include "pairwiserank.h"
#include "cycle.h"

// Correct this, get the element with the greatest preferences size
template<typename Prefs> Options<Prefs> majority_rule( std::vector<SocialPrefNode<Prefs>>& graph ){

	Options<Prefs> winner{ };

	for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

		for( std::vector<int>::size_type j = 0; j < graph.size( ); ++j ){

			if( graph[ i ].get_preferences( ).size( ) > graph[ j ].get_preferences( ).size( ) ){

				if( graph[ i ].get_preferences( ).size( ) > ( graph.size( ) ) / 2 ){

					winner.set_alternatives( graph[ i ].get_id( ) );
					winner.set_value( graph[ i ].get_preferences( ).size( ) );
				}
			}

			else{

				if( graph[ j ].get_preferences( ).size( ) > ( graph.size( ) ) / 2 ){

					winner.set_alternatives( graph[ j ].get_id( ) );
					winner.set_value( graph[ j ].get_preferences( ).size( ) );
				}
			}
		}
	}

	return winner;
}

template<typename Prefs> void borda_count( std::vector<PairWiseRank<Prefs>>& rank ){


}
