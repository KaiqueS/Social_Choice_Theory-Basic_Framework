//This shit is hard. This shit is on progress

#include <iostream>
#include <vector>
#include "agent.h"

int main( ){

	Agent one, two, three, four;

	//PairOfAgents pair;

	one.set_id( "1" );

	two = one;

	//std::cout << two.get_id() << "\n";

	two.set_id( "2" );

	three.set_id( "3" );

	four.set_id( "4" );

	std::vector<PairOfAgents> pairs;

	std::vector<Agent> list{ one, two, three, four };

	one.set_ordering( list );

	two.set_ordering( list );

	three.set_ordering( list );

	four.set_ordering( list );

	for( int i = 0; i < one.get_preferences().size(); ++i )

		std::cout << one.get_preferences()[ i ] << " ";

	std::cout << "\n";

	for( int i = 0; i < two.get_preferences().size(); ++i )

		std::cout << two.get_preferences()[ i ] << " ";

	std::cout << "\n";

	for( int i = 0; i < three.get_preferences().size(); ++i )

		std::cout << three.get_preferences()[ i ] << " ";

	std::cout << "\n";

	for( int i = 0; i < four.get_preferences().size(); ++i )

		std::cout << four.get_preferences()[ i ] << " ";

	std::cout << "\n\n";

	four = one;

	for( int i = 0; i < four.get_preferences().size(); ++i )

		std::cout << four.get_preferences()[ i ] << " ";

	std::cout << "\n";

	if( one == two )

		std::cout << "aimeudeus";

	else

		std::cout << "q coisa louca!!!!";

	std::cout << "\n\n";
}
