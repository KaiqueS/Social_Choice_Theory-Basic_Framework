#include "profile.hpp"

/// Constructors & Destructor

Profile::Profile( ){ alternatives = { }; }
Profile::Profile( std::vector<int>::size_type size ){ alternatives.resize( size ); }
Profile::Profile( std::vector<Options> alts ){ alternatives = alts; }
Profile::Profile( Options opt ){ alternatives.push_back( opt ); }
Profile::Profile( const Profile& copy ){ alternatives = copy.alternatives; }
Profile::~Profile( ){

    //std::cout << "Clearing profile of alternatives.\n";

	clear( );

	std::vector<Options>( ).swap( alternatives );
}

/// Setters

void Profile::set_alternatives( std::vector<Options>& alts ){ alternatives = alts; }
void Profile::set_alternatives( Options& opt ){ alternatives.push_back( opt ); }

/// Getters

/// Operators

Profile& Profile::operator=( const Profile& copy ){

    alternatives = copy.alternatives;

    return *this;
}

bool Profile::operator==( const Profile& rhs ){

    if( alternatives == rhs.alternatives )

        return true;

    else

        return false;
}

bool Profile::operator!=( const Profile& rhs ){

    if( alternatives == rhs.alternatives )

        return false;

    else

        return true;
}

/// Helpers

bool Profile::empty( ){

    if( alternatives.empty( ) )

        return true;

    else

        return false;
}

std::ostream& operator<<( std::ostream& os, Profile& profile ){

    for( std::vector<int>::size_type i = 0; i < profile.get_alternatives( ).size( ); ++i ){

        os << profile[ i ] << " ";
    }

    return os;
}

bool operator==( const Profile& lhs, const Profile& rhs ){

    Profile newlhs = lhs;
    Profile newrhs = rhs;

    if( newlhs.get_alternatives( ) == newrhs.get_alternatives( ) )

        return true;

    else

        return false;
}
