#include "preferencematrix.hpp"
#include <math.h>

// Begin with a number of options. Lets say, n.
// Generate n alternatives in a set, the order here will not be important now. This will be the generator set G
// Then, do the following:
	// how many different lists can one get where the first alternative is, lets say, the first element of G
	// repeat the above until every element of G is used
void generate_all_profiles(Profile preferences) {

	Profile holder{ preferences };

	Preferencematrix matrix{};

	matrix.push_back(holder);

	// Magic number. For now, use it, but find a way to either justify or make it not magic
	int repetitions{ 1 };

	for (std::vector<int>::size_type i = 2; i < preferences.size( ); ++i){

		for (std::vector<int>::size_type j = 0; j < std::tgamma(i + 1) - repetitions; ++j) {

			// switch elements between positions holder[ size - 1 ] and holder[ size - i ]
			std::swap(holder[holder.size() - 1], holder[holder.size() - i - j ]);

			matrix.push_back(holder);
		}

		holder = preferences;

		repetitions *= i;
	}
}