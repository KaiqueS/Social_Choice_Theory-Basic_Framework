#pragma once

#ifndef PREFERENCEMATRIX_H
#define PREFERENCEMATRIX_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <profile.hpp>

// A Matrix of Preferences. This matrix is created from a vector of vectors of Options.
// The outermost vector represents the rows, while the innermost vector represents the
// collumns
class Preferencematrix{

public:

	// Constructors & Destructor
	Preferencematrix( );
    Preferencematrix( std::vector<int>::size_type row, std::vector<int>::size_type col );
    Preferencematrix( std::vector<int>::size_type row, std::vector<int>::size_type col, std::vector<Profile> mtx );
    Preferencematrix( const Preferencematrix& copymatrix );

	~Preferencematrix( );

	// Setters
    void set_rowsz( std::vector<int>::size_type row );
    void set_columnsz( std::vector<int>::size_type col );

    void set_matrix( std::vector<int>::size_type rowsz, std::vector<int>::size_type colsz );

	// Getters
    std::vector<int>::size_type get_rowsz( ){ return rowsize; }
    std::vector<int>::size_type get_columnsz( ){ return columnsize; }

    // Return a reference instead?
	std::vector<Profile> get_matrix( ){ return matrix; }

	// Operators
    Profile& operator[ ]( const std::vector<int>::size_type& position ){ return matrix[ position ]; }

	Preferencematrix& operator=( const Preferencematrix& copy );

	bool operator==( const Preferencematrix& rhs ) const;

	// Helpers
	std::vector<int>::size_type size( ){ return matrix.size( ); }

	std::vector<Profile, std::allocator<Profile>>::iterator begin( ){ return matrix.begin( ); }
	std::vector<Profile, std::allocator<Profile>>::iterator end( ){ return matrix.end( ); }

	void delete_row( int rowindex );

	void push_back( Profile& profile ){ matrix.push_back( profile ); }

	void clear( ){ matrix.clear( ); }

private:

	// Remember to update size whenever a method that changes it is called
    std::vector<int>::size_type rowsize{ };
	std::vector<int>::size_type columnsize{ };

    std::vector<Profile> matrix{ };
};

std::ostream& operator<<( std::ostream& os, Preferencematrix& matrix );

#endif // PREFERENCEMATRIX_H
