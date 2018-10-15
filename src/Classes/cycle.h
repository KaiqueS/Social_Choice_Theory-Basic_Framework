#pragma once

#ifndef CYCLE_H
#define CYCLE_H

#include <vector>
#include <iostream>

template<typename Prefs> class Cycle{

public:

	// Constructors & Destructor
	Cycle( );
	Cycle( char name, std::vector<Prefs> way );
	Cycle( const Cycle& copy );

	~Cycle( ){ }

	// Setters
	void set_id( char name );

	void set_path( std::vector<Prefs> way );
	void set_path( Prefs way );

	// Getters
	char get_id( ){ return id; }

	std::vector<Prefs> get_path( ){ return path; }

	// Operators
	Cycle& operator=( const Cycle& copy );

	Cycle& operator[ ]( const int index );

private:

	char id{ };

	std::vector<Prefs> path{ };
};

/* Constructors & Destructor */

template<typename Prefs> Cycle<Prefs>::Cycle( ){

	id = '0';

	path = { };
}
template<typename Prefs> Cycle<Prefs>::Cycle( char name, std::vector<Prefs> way ){

	id = name;

	path = way;
}
template<typename Prefs> Cycle<Prefs>::Cycle( const Cycle& copy ){

	id = copy.id;

	path = copy.path;
}

/* Setters */

template<typename Prefs> void Cycle<Prefs>::set_id( char name ){ id = name; }

template<typename Prefs> void Cycle<Prefs>::set_path( std::vector<Prefs> way ){ path = way; }
template<typename Prefs> void Cycle<Prefs>::set_path( Prefs way ){ path.push_back( way ); }

/* Getters */

/* Operators */

template<typename Prefs> Cycle<Prefs>& Cycle<Prefs>::operator=( const Cycle& copy ){

	id = copy.id;

	path = copy.path;

	return *this;
}

template<typename Prefs> Cycle<Prefs>& Cycle<Prefs>::operator[ ]( const int index ){ return path[ index ]; }

template<typename Prefs> std::ostream& operator<<( std::ostream& os, Cycle<Prefs>& path ){

	os << path.get_id( ) << ": ";

	for( int i = 0; i < path.get_path( ).size( ); ++i )

		os << path.get_path( )[ i ] << " ";

	os << "\n";

	return os;
}

#endif // CYCLE_H
