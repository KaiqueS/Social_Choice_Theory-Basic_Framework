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
Profile::~Profile( ){

    //std::cout << "Clearing profile of alternatives.\n";

	clear( );

	std::vector<Options>( ).swap( alternatives );
}

/// Setters

// Sets ALTERNATIVES to alts
void Profile::set_alternatives( std::vector<Options>& alts ){ alternatives = alts; }

// Inserts opt at the end of ALTERNATIVES
void Profile::set_alternatives( Options& opt ){ alternatives.push_back( opt ); }

/// Getters

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

    if( alternatives == rhs.alternatives )

        return false;

    else

        return true;
}

/// Helpers

// Checks if a profile is empty. If it is, return true.
bool Profile::empty( ){

    if( alternatives.empty( ) )

        return true;

    else

        return false;
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

    Profile newlhs = lhs;
    Profile newrhs = rhs;

    if( newlhs.get_alternatives( ) == newrhs.get_alternatives( ) )

        return true;

    else

        return false;
}
