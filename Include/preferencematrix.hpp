#pragma once

#ifndef PREFERENCEMATRIX_H
#define PREFERENCEMATRIX_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
//#include <ctime>
//#include <map>
#include <string>
#include <fstream>
//#include <Python.h>
#include "profile.hpp"

// A Matrix of Preferences. This matrix is created from a vector of vectors of Options.
// The outermost vector represents the rows, while the innermost vector represents the
// collumns
class Preferencematrix{

public:

	// Constructors & Destructor
	Preferencematrix( );
	Preferencematrix( std::vector<int>::size_type row, std::vector<int>::size_type col, std::vector<Profile> mtx ) : rowsize( row ), columnsize( col ), matrix( mtx ){ }
	Preferencematrix( std::initializer_list<Profile> init ) : matrix( std::move( init ) ){ rowsize = matrix.size( );
																						   columnsize = matrix.begin( ) -> size( ); }
    Preferencematrix( std::vector<int>::size_type row, std::vector<int>::size_type col );
    Preferencematrix( const Preferencematrix& copymatrix );
	Preferencematrix( Preferencematrix&& copymatrix );
	~Preferencematrix( );

	// Setters
    void set_rowsz( std::vector<int>::size_type row );
    void set_columnsz( std::vector<int>::size_type col );

    void set_matrix( std::vector<int>::size_type rowsz, std::vector<int>::size_type colsz );
    void set_matrix( std::vector<Profile> mtx ){ matrix = mtx; }

	// Getters
    std::vector<int>::size_type get_rowsz( ) const{ return rowsize; }
    std::vector<int>::size_type get_columnsz( ) const{ return columnsize; }

	std::vector<Profile> get_matrix( ) const{ return matrix; } // Return a reference instead? - And risk allowing access to a member field? NO WAY

	// Operators
    Profile& operator[ ]( const std::vector<int>::size_type& position ){ return matrix[ position ]; } // TODO: add range checking

	Preferencematrix& operator=( const Preferencematrix& copy );
	Preferencematrix& operator=( Preferencematrix&& copy );

	// Helpers
	std::vector<Profile, std::allocator<Profile>>::iterator begin( ){ return matrix.begin( ); }
	std::vector<Profile, std::allocator<Profile>>::iterator end( ){ return matrix.end( ); } // TODO: return one-beyond-last-element - this is right

	std::vector<int>::size_type size( ) const{ return matrix.size( ); }

	bool empty( );

	void erase_row( const std::vector<int>::size_type index );
	void push_back( Profile& profile ){ matrix.push_back( profile ); }
	void clear( );

	void merge_sort_by_value( );

	void read_dataset( std::string file_name );

private:

	// Remember to update size whenever a method that changes it is called
    std::vector<int>::size_type rowsize{ };
	std::vector<int>::size_type columnsize{ };

    std::vector<Profile> matrix{ };
};

// Non-member helpers
std::ostream& operator<<( std::ostream& os, Preferencematrix& matrix );


// Two PreferenceMatrix'es are equal iff for every 0 <= i <= matrix.size, we have that
// left[ i ] == right[ i ]. I.e., they must hold the same Profiles on the same position, 
// which, in turn, must be equal to each other.
inline bool operator==( const Preferencematrix& left, const Preferencematrix& right ){

	if( left.size( ) != right.size( ) ){

		return false;
	}

	else{

		for( auto i = 0; i < left.size( ); ++i ){

			if( left.get_matrix( )[ i ] != right.get_matrix( )[ i ] ){

				return false;
			}

			else{

				continue;
			}
		}

		return true;
	}

	
}
inline bool operator!=( const Preferencematrix& left, const Preferencematrix& right ){ return !operator==( left, right ); }

// MODIFIED: used to get two arguments ( Profile& profile, PreferenceMatrix& matrix )
// Check for every instance that NOW gets only MATRIX as argument
//Profile make_social_order( Preferencematrix& matrix ); - Deprecated. Complete NONSENSE

void initialize_opts( Preferencematrix& matrix, Profile& profile );

const std::vector<std::string> alpha( );

std::vector<std::string> generate_alphabet( int remainder );

#endif // PREFERENCEMATRIX_H
