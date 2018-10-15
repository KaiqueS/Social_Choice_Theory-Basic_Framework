#pragma once

#ifndef PREFERENCEMATRIX_H
#define PREFERENCEMATRIX_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include "options.h"

// A Matrix of Preferences. This matrix is created from a vector of vectors of Options.
// The outermost vector represents the rows, while the innermost vector represents the
// collumns
template<typename PrefCol> class Preferencematrix{

public:

	// Constructors & Destructor
	Preferencematrix( );

	Preferencematrix( const std::vector<std::vector<Options<PrefCol>>>& copymatrix );

	~Preferencematrix( ){ std::cout << "Matrix destructed.\n\n"; }

	// Setters
	void set_matrix( int rowsz, int colsz );

	// Getters
	std::vector<std::vector<Options<PrefCol>>> get_matrix( ){ return matrix; }

	// Operators
	std::vector<Options<PrefCol>>& operator[ ]( const int& position ){ return matrix[ position ]; }

	Preferencematrix& operator=( const Preferencematrix& copy );

	// Helpers
	void delete_row( int rowindex );

	void print_mtx( );

private:

	std::vector<std::vector<Options<PrefCol>>> matrix{ };
};

/* Constructors */

// Default Constructor. Initializes private members to its default values
template<typename PrefCol> Preferencematrix<PrefCol>::Preferencematrix( ){ matrix = { }; }

// Copy Constructor. Initializes values according to parameters
template<typename PrefCol> Preferencematrix<PrefCol>::Preferencematrix( const std::vector<std::vector<Options<PrefCol>>>& copymatrix ){ matrix = copymatrix; }

/* Setters*/

// Set a matrix of RowSZ x ColSZ dimensions. Sets a random value to each alternative
template<typename PrefCol> void Preferencematrix<PrefCol>::set_matrix( int rowsz, int colsz ){

	std::vector<Options<PrefCol>> setofalts( colsz );

	// Sets alternatives' id's
	for( std::vector<int>::size_type i = 0; i < setofalts.size( ); ++i ){

		std::string subs = std::to_string( i );

		char const* pchar = subs.c_str( );

		setofalts[ i ].set_alternatives( *pchar );
	}

	// Sets alternatives' values
	for( int i = 0; i < rowsz; ++i ){

		auto randvalind = std::default_random_engine{ };

		std::shuffle( setofalts.begin( ), setofalts.end( ), randvalind );

		matrix.push_back( setofalts );

		for( int j = 0; j < colsz; ++j ){

			int val = rand( ) % colsz;

			matrix[ i ][ j ].set_value( val );
		}
	}
}

/* Getters */

// Prints the matrix
template<typename PrefCol> void Preferencematrix<PrefCol>::print_mtx( ){

	std::cout << "Preference Matrix\n\n" << "\t\t\tOptions/Alternatives Columns\n\n";

	for( std::vector<int>::size_type i = 0; i < matrix.size( ); ++i ){

		std::cout << "Row vector id number: " << i << "| ";

		for( std::vector<int>::size_type j = 0; j < matrix[ i ].size( ); ++j ){

			std::cout << "( " << matrix[ i ][ j ].get_alternatives( )
					  << ", " << matrix[ i ][ j ].get_value( ) << " ) ";
		}

		std::cout << "\n";
	}
}

/* Operators */

// Overloaded assignment operator
template<typename PrefCol> Preferencematrix<PrefCol>& Preferencematrix<PrefCol>::operator=( const Preferencematrix& copy ){

	matrix = copy.matrix;

	return *this;
}

template<typename PrefCol> bool operator==( Preferencematrix<PrefCol>& one, Preferencematrix<PrefCol>& two ){

	if( one.get_matrix( ) == two.get_matrix( ) )

		return true;

	else

		return false;
}
template<typename PrefCol> bool operator!=( Preferencematrix<PrefCol>& one, Preferencematrix<PrefCol>& two ){

	if( one.get_matrix( ) != two.get_matrix( ) )

		return true;

	else

		return false;
}

/* Helpers */

// Deletes an specific row. Used in Agent.h class
template<typename PrefCol> void Preferencematrix<PrefCol>::delete_row( int rowindex ){

	matrix.erase( matrix.begin( ) + rowindex );
}

#endif // PREFERENCEMATRIX_H
