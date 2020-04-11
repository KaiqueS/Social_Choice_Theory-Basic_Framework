#include "/Projetos/SocialChoice_VS/Include/testing_grounds.hpp"

#ifndef TESTING_GROUNDS_CPP
#define TESTING_GROUNDS_CPP

const std::vector<std::string> alphabet( ){

	// elem.size is the max num of houses resulting string will have

	std::vector<std::string> alpha = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
									   "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };

	return alpha;
}

// Counts how many elements of each size there will be in a zipping of an alphabet
std::vector<int> num_of_elem( int size ){

	std::vector<int> elements{ };

	int remainder{ size };

	double i{ 1 };

	while( remainder > 0 ){

		if( ( remainder - ( std::pow( static_cast<int>( 26 ), i ) ) > 0 ) ){

			elements.push_back( static_cast<int>( std::pow( 26, i ) ) );

			remainder -= static_cast<int>( std::pow( 26, i ) );
		}

		else{

			elements.push_back( remainder );

			remainder -= static_cast<int>( std::pow( 26, i ) );
		}

		++i;
	}

	return elements;
}
// This code does NOT work for remainder <= 26
// always begin with an empty string, else, shit is bound to happen
// position must begin at 0
std::vector<std::string> zip_alphabet( int remainder ){

	std::vector<std::string> result{ };

	if( remainder <= 0 || remainder < 26 ){

		for( std::vector<int>::size_type i = 0; i < remainder; ++i ){

			result.push_back( alphabet( )[ i ] );
		}

		return result;
	}

	else{

		result = alphabet( );

		std::vector<int>::size_type position{ result.size( ) };

		result.resize( result.size( ) + ( remainder - result.size( ) ) + 1 );

		remainder -= alphabet( ).size( );

		// Problem here: 
		for( std::vector<int>::size_type i = 0; i < result.size( ); ++i ){

			if( remainder <= 0 ){

				return result;
			}

			else{

				std::vector<int>::size_type used_elem{ 0 };

				// Just need to fine tune this
				for( std::vector<int>::size_type j = 0; ( j < remainder ) && ( j < alphabet( ).size( ) ); ++j ){

					result[ position ] += result[ i ] + alphabet( )[ j ];

					++position;

					++used_elem;
				}

				remainder -= used_elem; // This is messing with control flux of for-loop
			}
		}

		return result;
	}
}

std::vector<std::string> newtry( std::vector<std::string> alpha, int remainder ){

	std::vector<std::string> result{ alpha.begin( ), alpha.end( ) };

	if( remainder <= 0 || result.size( ) < 26 ){

		return result;
	}

	else{

		std::vector<int>::size_type position{ result.size( ) };

		result.resize( result.size( ) + ( remainder - result.size( ) ) + 1 );

		remainder -= alpha.size( );

		for( std::vector<int>::size_type i = 0; i < result.size( ); ++i ){

			if( remainder <= 0 ){

				return result;
			}

			else{

				std::vector<int>::size_type used_elem{ 0 };

				for( std::vector<int>::size_type j = 0; ( j < remainder ) && ( j < alpha.size( ) ); ++j ){

					result[ position ] += result[ i ] + alpha[ j ];

					++position;

					++used_elem;
				}

				remainder -= used_elem;
			}
		}
	}

	return result;
}

#endif // TESTING_GROUNDS_CPP