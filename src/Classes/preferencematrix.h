#pragma once

#ifndef PREFERENCEMATRIX_H
#define PREFERENCEMATRIX_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include "Classes/options.h"

// A Matrix of Preferences. This matrix is created from a vector of vectors of Options.
// The outermost vector represents the rows, while the innermost vector represents the
// collumns
class Preferencematrix{

public:

	// Constructors & Destructor
	Preferencematrix( );

	Preferencematrix( const std::vector<std::vector<Options>>& copymatrix );

	~Preferencematrix( ){ std::cout << "Matrix destructed.\n\n"; }

	// Setters
	void set_matrix( std::vector<int>::size_type rowsz, std::vector<int>::size_type colsz );

	// Getters
	std::vector<std::vector<Options>> get_matrix( ){ return matrix; }

	// Operators
	std::vector<Options>& operator[ ]( const std::vector<int>::size_type& position ){ return matrix[ position ]; }

	Preferencematrix& operator=( const Preferencematrix& copy );

	bool operator==( const Preferencematrix& rhs ) const;

	// Helpers
	void delete_row( int rowindex );

private:

	std::vector<std::vector<Options>> matrix{ };
};

std::ostream& operator<<( std::ostream& os, Preferencematrix& matrix );

#endif // PREFERENCEMATRIX_H
