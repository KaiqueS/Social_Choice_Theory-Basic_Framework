//This shit is hard. This shit is on progress

#include <iostream>
#include <vector>
#include "agent.h"

int main( ){

	Agent one, two, three, four;

	PairOfAgents pair;

	one.set_id( "1" );

	two = one;

	//std::cout << two.get_id() << "\n";

	two.set_id( "2" );

	three.set_id( "3" );

	four.set_id( "4" );

	std::vector<PairOfAgents> pairs;

	std::vector<Agent> list{ one, two, three, four };

	one.set_ordering( list );

	//one.set_preferences( list );

	for( int i = 0; i < one.get_preferences().size(); ++i )

		std::cout << one.get_preferences()[ i ] << " ";

	std::cout << "\n\n";
}
