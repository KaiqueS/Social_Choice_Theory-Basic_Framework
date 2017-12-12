//This shit is hard. This shit is on progress

#include <iostream>
#include <vector>
#include "agent.h"

int main( ){

	Agent one, two, three, four;

	PairOfAgents pair;

	one.set_id( "1" );

	two = one;

	std::cout << two.get_id() << "\n";

	three.set_id( "3" );

	four.set_id( "4" );

	one.set_ordering( two );
	one.set_ordering( three );
	one.set_ordering( four );

	std::vector<PairOfAgents> pairs;

	for( int i = 0; i < one.get_preferences().size(); ++i )

		std::cout << one.get_preferences()[ i ] << " ";

	std::cout << "\n\n";

	std::vector<Agent> agent{ one, two, three, four };

	set_pairs( agent, pairs );

	for( int i = 0; i < pairs.size(); ++i )

		std::cout << pairs[ i ].get_id() << "\n";
}
