#include "profile.hpp"

/// Constructors & Destructor

// Default constructor. Initializes ALTERNATIVES to its default value
Profile::Profile( ){ alternatives = { }; }

// Alternative parameterized constructor. Resizes ALTERNATIVES to size
Profile::Profile( std::vector<int>::size_type size ){ alternatives.resize( size ); }

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

bool Profile::is_ordered( ){

    if( _opt_sorted == true )

        return true;

    else

        return false;
}

/// Operators

// Overloaded assignment operator
Profile& Profile::operator=( const Profile& copy ){

    alternatives = copy.alternatives;

    return *this;
}

// Overloaded comparison operator. Compares two profiles.
// Returns true if they are equal
bool Profile::operator==( const Profile& rhs ){

    if( alternatives == rhs.alternatives )

        return true;

    else

        return false;
}

// Overloaded difference operator. Compares two profiles.
// Returns true if they are different.
bool Profile::operator!=( const Profile& rhs ){

    if( alternatives != rhs.alternatives )

        return true;

    else

        return false;
}

/// Helpers

// Checks if a profile is empty. If it is, return true.
bool Profile::empty( ){

    if( alternatives.empty( ) )

        return true;

    else

        return false;
}

void Profile::erase( const std::vector<int>::size_type index  ){

    alternatives.erase( std::remove( alternatives.begin( ), alternatives.end( ), index ), alternatives.end( ) );
}

void Profile::clear( ){

    alternatives.clear( );

    std::vector<Options>( ).swap( alternatives );
}

// user merge sort instead. nlgn
void Profile::sort_by_value( ){

	auto order = [ ]( Options& left, Options& right ){

		return left.get_value( ) > right.get_value( );
	};

	std::sort( alternatives.begin( ), alternatives.end( ), order );

	_value_sorted = true;
}

void Profile::sort_by_opt( ){

	auto order = [ ]( Options& left, Options& right ){

		return left.get_opt( ) > right.get_opt( );
	};

	std::sort( alternatives.begin( ), alternatives.end( ), order );

	_opt_sorted = true;
}

/// Non-Member Helpers

// Overloaded printing operator
std::ostream& operator<<( std::ostream& os, Profile& profile ){

    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        os << profile[ i ] << " ";
    }

    return os;
}

// Overloaded comparison operator. Compares the alternatives
// of two profiles. Returns true if the are all equal
bool operator==( const Profile& lhs, const Profile& rhs ){

    Profile left = lhs;
    Profile right = rhs;

    left.sort_by_opt( );
    right.sort_by_opt( );

    if( left.get_alternatives( ) == right.get_alternatives( ) )

        return true;

    else

        return false;
}

// Only works when profile is ordered by opt, not by value
std::vector<int>::size_type find_opt( Profile profile, Options& opt ){

    std::vector<int>::size_type begin{ 0 };
    std::vector<int>::size_type middle = static_cast<std::vector<int>::size_type>( std::floor( profile.size( ) / 2 ) );
    std::vector<int>::size_type end{ 0 };

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

    return middle;
}
