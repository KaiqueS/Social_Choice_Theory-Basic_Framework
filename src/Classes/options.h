#pragma once

#ifndef OPTIONS_H
#define OPTIONS_H

#include<iostream>
#include<vector>

template<typename Opts> class Options{

public:

	// Constructors & Destructor

	Options( );
	Options( const Opts& alts, const int& val );
	Options( const Options<Opts>& copy );

	~Options( ){ }

	// Setters
	void set_alternatives( Opts newalt );
	void set_value( int val );

	// Getters
	Opts get_alternatives( ){ return alternatives; }

	int get_value( ){ return value; }

	// Operators
	Options<Opts>& operator=( const Options<Opts>& copy );

private:

	Opts alternatives{ };

	int value{ };
};

/* Constructors & Destructor */

// Default constructor. Initializes private properties to its default values
template<typename Opts> Options<Opts>::Options( ){

	alternatives = { };

	value = { };
}

// Parameterized constructor. Initializes private properties based on the arguments passed by
template <typename Opts> Options<Opts>::Options( const Opts& alts, const int& val ){

	alternatives = alts;

	value = val;
}

// Copy constructor. Initializes private properties based on the arguments passed by
template<typename Opts> Options<Opts>::Options( const Options<Opts>& copy ){

	alternatives = copy.alternatives;

	value = copy.value;
}

/* Setters */

// Sets alternatives according to the argument passed through
template<typename Opts> void Options<Opts>::set_alternatives( Opts newalt ){ alternatives = newalt; }

// Sets values according to value passed as parameter
template<typename Opts> void Options<Opts>::set_value( int val ){ value = val; }

/* Operators */

// Overloaded assignment operator
template<typename Opts> Options<Opts>& Options<Opts>::operator=( const Options<Opts>& copy ){

	alternatives = copy.alternatives;

	value = copy.value;

	return *this;
}

template<typename Opts> bool operator==( Options<Opts>& one, Options<Opts>& two ){

	if( one.get_alternatives( ) == two.get_alternatives( ) &&
		one.get_value( ) == two.get_value( ) )

		return true;

	else

		return false;
}
template<typename Opts> bool operator!=( Options<Opts>& one, Options<Opts>& two ){

	if( one.get_alternatives( ) != two.get_alternatives( ) ||
		one.get_value( ) != two.get_value( ) ) // WRONG: should be && instead of ||

		return true;

	else

		return false;
}

#endif // OPTIONS_H
