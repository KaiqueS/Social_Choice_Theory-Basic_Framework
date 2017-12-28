#include "agent.h"

// Sets pairs of agents. Actually, this is the Gale-Shepley algorithm
// TODO5: Check if there are two equal pairs in list!
void set_pairs( std::vector<Agent> agents, std::vector<PairOfAgents>& list ){

	for( Agent man : agents ){

		if( man.get_sex( ) == 'm' && man.get_status( ) == false ){

			for( Agent woman : man.get_preferences( ) ){

				if( woman.get_status( ) == false ){

					man.set_status( true );

					woman.set_status( true );

					list.push_back( PairOfAgents( man, woman ) );
				}
			}
		}
	}
}
