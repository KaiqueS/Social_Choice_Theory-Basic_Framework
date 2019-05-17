#include "profile.hpp"

// remove sort_by_opt( ) if one starts to have problems

/// Constructors & Destructor

// Default constructor. Initializes ALTERNATIVES to its default value
Profile::Profile( ){ alternatives = { }; }

// Alternative parameterized constructor. Resizes ALTERNATIVES to size
Profile::Profile( std::vector<int>::size_type size ){

    alternatives.resize( size );

    for( std::vector<int>::size_type i = 0; i < alternatives.size( ); ++i ){

        alternatives[ i ] = { };
    }
}

// Alternative parameterized constructor. Inserts an Option opt at the
// end of ALTERNATIVES
Profile::Profile( Options opt ){ alternatives.push_back( opt ); }

// Copy construcotr
Profile::Profile( const Profile& copy ){ alternatives = copy.alternatives; }

// Destructor. Clears ALTERNATIVES from memory
Profile::~Profile( ){ clear( ); }

/// Setters

// Sets ALTERNATIVES to alts
void Profile::set_alternatives( std::vector<Options>& alts ){ alternatives = alts; }

// Inserts opt at the end of ALTERNATIVES
void Profile::set_alternatives( Options& opt ){ alternatives.push_back( opt ); }

/// Getters

bool Profile::is_value_sorted( ) const{

    if( _value_sorted == true )

        return true;

    else

        return false;
}
bool Profile::is_opt_sorted( ) const{

	if( _opt_sorted == true )

		return true;

	else

		return false;
}

/// Operators

// Overloaded assignment operator
Profile& Profile::operator=( Profile copy ){

	swap( *this, copy );

    return *this;
}

/// Helpers

// Checks if a profile is empty. If it is, return true.
bool Profile::empty( ){

    if( alternatives.empty( ) )

        return true;

    else

        return false;
}

// Problem here
void Profile::erase( const std::vector<int>::size_type index  ){

    //alternatives.erase( std::remove( alternatives.begin( ), alternatives.end( ), alternatives[ index ] ), alternatives.end( ) );
    alternatives.erase( alternatives.begin( ) + index );
}

void Profile::clear( ){

    alternatives.clear( );

    std::vector<Options>( ).swap( alternatives );
}

void Profile::merge_by_value( std::vector<int>::size_type start, std::vector<int>::size_type middle, std::vector<int>::size_type end ){

	std::vector<int>::size_type n1 = middle - start + 1;
	std::vector<int>::size_type n2 = end - middle;

	Profile left( n1 + 1 );
	Profile right( n2 + 1 );

	for( std::vector<int>::size_type i = 0; i < n1; ++i ){

		left[ i ] = alternatives[ start + i ];
	}

	for( std::vector<int>::size_type i = 0; i < n2; ++i ){

		right[ i ] = alternatives[ middle + i + 1 ];
	}

	// Sentinel - Has to be larger than any element in the array
	left[ n1 ].set_value( std::numeric_limits<int>::max( ) );
	right[ n2 ].set_value( std::numeric_limits<int>::max( ) );

	std::vector<int>::size_type i = 0;
	std::vector<int>::size_type j = 0;

	for( std::vector<int>::size_type k = start; k <= end; ++k ){

		if( left[ i ].get_value( ) <= right[ j ].get_value( ) ) {

			alternatives[ k ] = left[ i ];
			++i;
		}
		else{

			alternatives[ k ] = right[ j ];
			++j;
		}
	}
}

// fix this later - NEEDS TESTING
void Profile::merge_by_opt( std::vector<int>::size_type start, std::vector<int>::size_type middle, std::vector<int>::size_type end ){

	std::vector<int>::size_type n1 = middle - start + 1;
	std::vector<int>::size_type n2 = end - middle;

	Profile left( n1 + 1 );
	Profile right( n2 + 1 );

	for( std::vector<int>::size_type i = 0; i < n1; ++i ){

		left[ i ] = alternatives[ start + i ];
	}

	for( std::vector<int>::size_type i = 0; i < n2; ++i ){

		right[ i ] = alternatives[ middle + i + 1 ];
	}

	// Sentinel - Has to be larger than any element in the array
	left[ n1 ].set_opt( std::to_string( std::numeric_limits<int>::max( ) ) );
	right[ n2 ].set_opt( std::to_string( std::numeric_limits<int>::max( ) ) );

	std::vector<int>::size_type i = 0;
	std::vector<int>::size_type j = 0;

	for( std::vector<int>::size_type k = start; k <= end; ++k ){

		if( left[ i ].get_opt( ) <= right[ j ].get_opt( ) ) {

			alternatives[ k ] = left[ i ];
			++i;
		}
		else{

			alternatives[ k ] = right[ j ];
			++j;
		}
	}
}

void Profile::value_merge_sort( std::vector<int>::size_type start, std::vector<int>::size_type end ){

	if( start < end ){

		std::vector<int>::size_type middle = ( start + end ) / 2;

		value_merge_sort( start, middle );
		value_merge_sort( middle + 1, end );

		merge_by_value( start, middle, end );
	}

	_value_sorted = true;
}

// fix this later
void Profile::opt_merge_sort( std::vector<int>::size_type start, std::vector<int>::size_type end ){

	if( start < end ){

		std::vector<int>::size_type middle = ( start + end ) / 2;

		opt_merge_sort( start, middle );
		opt_merge_sort( middle + 1, end );

		merge_by_opt( start, middle, end );
	}

	_opt_sorted = true;
}

// use merge sort instead. nlgn
void Profile::sort_by_value( ){

	auto order = [ ]( Options& left, Options& right ){

		return left.get_value( ) > right.get_value( );
	};

	std::sort( alternatives.begin( ), alternatives.end( ), order );

	_value_sorted = true;
}

// use merge sort
void Profile::sort_by_opt( ){

	auto order = [ ]( Options& left, Options& right ){

		return left.get_opt( ) < right.get_opt( );
	};

	std::sort( alternatives.begin( ), alternatives.end( ), order );

	_opt_sorted = true;
}

void Profile::no_indifference( ){

	std::vector<int> values( alternatives.size( ) );

	for( std::vector<int>::size_type i = 0; i < values.size( ); ++i ){

		values[ i ] = i;
	}

	std::random_device rd;

	//std::mt19937_64 mt( rd( ) );
	std::mt19937 mt( rd( ) );

	for( std::vector<int>::size_type i = 0; i < alternatives.size( ); ++i ){

		std::uniform_int_distribution<std::vector<int>::size_type> range( 0, ( values.size( ) - 1 ) );

		auto opt = std::find( values.begin( ), values.end( ), values[ range( mt ) ] );

		std::vector<int>::size_type distance = opt - values.begin( );

		alternatives[ i ].set_value( *opt );

		values.erase( values.begin( ) + distance );
	}

	indifference = false;
}

void swap( Profile& left, Profile& right ){

	using std::swap;

	swap( left._value_sorted, right._value_sorted );
	swap( left._opt_sorted, right._opt_sorted );
	swap( left.alternatives, right.alternatives );
}

/// Non-Member Helpers

// Overloaded printing operator
std::ostream& operator<<( std::ostream& os, Profile& profile ){

    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        os << profile[ i ] << " ";
    }

    return os;
}

// Uses Binary-Search to find an option in a profile. Returns the position of a
// given OPTION in PROFILE. Works only when the profile is ordered by opt, in a
// scending order
// TODO: DEBUG THIS. SHIT IS HAPPENNING
std::vector<int>::size_type find_opt( Profile profile, Options opt ){

    std::vector<int>::size_type begin{ 0 };
    std::vector<int>::size_type middle = static_cast<std::vector<int>::size_type>( std::floor( profile.size( ) / 2 ) );
    std::vector<int>::size_type end{ 0 };

	if( profile.is_opt_sorted( ) ){

		while( profile[ middle ] != opt ){

			if( opt.get_opt( ) < profile[ middle ].get_opt( ) ){

				begin = 0;
				end = middle;

				middle = ( begin + end ) / 2;
			}

			else if( opt.get_opt( ) > profile[ middle ].get_opt( ) ){

				begin = middle;
				end = profile.size( ) - 1;

				middle = ( begin + end ) / 2;
			}

			else

				return middle;
		}
	}

	else{

		profile.sort_by_opt( );

		while( profile[ middle ] != opt ){

			if( opt.get_opt( ) < profile[ middle ].get_opt( ) ){

				begin = 0;
				end = middle;

				middle = ( begin + end ) / 2;
			}

			else if( opt.get_opt( ) > profile[ middle ].get_opt( ) ){

				begin = middle;
				end = profile.size( );

				middle = ( begin + end ) / 2;
			}

			else

				return middle;
		}
	}

    return middle;
}

/*void merge( Profile& profile, std::vector<int>::size_type start, std::vector<int>::size_type middle, std::vector<int>::size_type end ){

	std::vector<int>::size_type n1 = middle - start + 1;
	std::vector<int>::size_type n2 = end - middle;

	Profile left( n1 + 1 );
	Profile right( n2 + 1 );

	for( std::vector<int>::size_type i = 0; i < n1; ++i ){
		
		left[ i ] = profile[ start + i ];
	}

	for( std::vector<int>::size_type i = 0; i < n2; ++i ){

		right[ i ] = profile[ middle + i + 1 ];
	}

	// Sentinel - Has to be larger than any element in the array
	left[ n1 ].set_value( std::numeric_limits<int>::max( ) );
	right[ n2 ].set_value( std::numeric_limits<int>::max( ) );

	std::vector<int>::size_type i = 0;
	std::vector<int>::size_type j = 0;

	for( std::vector<int>::size_type k = start; k <= end; ++k ){

		if( left[ i ].get_value( ) <= right[ j ].get_value( ) ) {
			
			profile[ k ] = left[ i ];
			++i;
		}
		else{

			profile[ k ] = right[ j ];
			++j;
		}
	}
}

void merge_sort( Profile& profile, std::vector<int>::size_type start, std::vector<int>::size_type end ){

	if( start < end ){

		std::vector<int>::size_type middle = ( start + end ) / 2;

		merge_sort( profile, start, middle );
		merge_sort( profile, middle + 1, end );

		merge( profile, start, middle, end );
	}

	profile.sorted_by_value( true );
}*/
