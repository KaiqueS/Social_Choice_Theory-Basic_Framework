#include "cycle.h"

/* Constructors & Destructor */

Cycle::Cycle( ){

    id = '0';

    path = { };
}
Cycle::Cycle( std::string name, std::vector<std::string> way ){

    id = name;

    path = way;
}
Cycle::Cycle( const Cycle& copy ){

    id = copy.id;

    path = copy.path;
}

/* Setters */

void Cycle::set_id( std::string name ){ id = name; }

void Cycle::set_path( std::vector<std::string> way ){ path = way; }
void Cycle::set_path( std::string way ){ path.push_back( way ); }

/* Getters */

/* Operators */

Cycle& Cycle::operator=( const Cycle& copy ){

    id = copy.id;

    path = copy.path;

    return *this;
}

std::string& Cycle::operator[ ]( const std::vector<int>::size_type& index ){ return path[ index ]; }

template<typename Prefs> std::ostream& operator<<( std::ostream& os, Cycle& path ){

    os << path.get_id( ) << ": ";

    for( std::vector<int>::size_type i = 0; i < path.get_path( ).size( ); ++i )

        os << path.get_path( )[ i ] << " ";

    os << "\n";

    return os;
}

