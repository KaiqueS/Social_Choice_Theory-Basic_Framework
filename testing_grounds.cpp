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

        std::vector<int>::size_type transpose_index{ 0 };

		for (std::vector<int>::size_type j = 0; j < std::tgamma(i + 1) - repetitions; ++j) {

			// switch elements between positions holder[ size - 1 ] and holder[ size - i ]
            std::swap(holder[holder.size() - 1], holder[holder.size() - i - transpose_index ]); // removed - j, it would overflow the vector, accessing elements out of scope

			matrix.push_back(holder);

            if( transpose_index < i - 1 ){

                ++transpose_index;
            }

            else{

                continue;
            }
		}

		holder = preferences;

		repetitions *= i;
	}
}

void generate_profiles_2( Profile preferences ){

	Preferencematrix matrix{};

	for (std::vector<int>::size_type i = 0; i < preferences.size(); ++i) {

		for (std::vector<int>::size_type j = 0; j < ( ( std::tgamma( preferences.size( ) + 1 ) / preferences.size( ) ) - i ); ++j) {

			Profile holder(preferences.size() );

			holder[0] = preferences[i];

			matrix.push_back( holder );
		}
	}
}

void generate_profile_3(Profile preferences) {

	Preferencematrix matrix( std::tgamma(preferences.size() + 1), preferences.size() ); // a matrix with preferences.size! rows and preferences.size columns

	std::vector<int>::size_type k{ 0 };

	for (std::vector<int>::size_type i = 0; i < preferences.size(); ++i) {

		for (std::vector<int>::size_type j = 0; j < matrix.size(); ++j) {

			k = j;

			if (k % matrix[j].size() > 0) {

				k = std::remainder( k, matrix[j].size( ) );

				matrix[j][k] = preferences[i];
			}

			else if ( k % matrix[ j ].size() == 0 ){

				k = std::remainder(k, matrix[j].size());

				matrix[j][k] = preferences[i];
			}

			/*for (std::vector<int>::size_type k = j; k < matrix[j].size(); ++k) { // this is wrong, this should be modular arithmetic

				matrix[j][k] = preferences[i];
			}*/
		}
	}
}