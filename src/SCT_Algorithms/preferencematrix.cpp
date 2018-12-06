#include "Classes/preferencematrix.h"

/* Constructors */

// Default Constructor. Initializes private members to its default values
Preferencematrix::Preferencematrix( ){ matrix = { }; }

// Copy Constructor. Initializes values according to parameters
Preferencematrix::Preferencematrix( const std::vector<std::vector<Options>>& copymatrix ){ matrix = copymatrix; }

/* Setters*/

// Set a matrix of RowSZ x ColSZ dimensions. Sets a random value to each alternative
// TODO: Problem generating options' ids
void Preferencematrix::set_matrix( std::vector<int>::size_type rowsz, std::vector<int>::size_type colsz ){

	std::vector<Options> setofalts( colsz );

	int aux=0;

	// Sets alternatives' id's
	for( std::vector<int>::size_type i = 0; i < setofalts.size( ); ++i ){

		setofalts[ i ].set_opt( "opt " + std::to_string( aux ) );

		++aux;
	}

	// Sets alternatives' values
	for( std::vector<int>::size_type i = 0; i < rowsz; ++i ){

		matrix.push_back( setofalts );

		for( std::vector<int>::size_type j = 0; j < colsz; ++j ){

            int val = rand( ) % static_cast<int>( colsz );

			matrix[ i ][ j ].set_value( val );
		}
	}
}

/* Getters */

/* Operators */

// Overloaded assignment operator
Preferencematrix& Preferencematrix::operator=( const Preferencematrix& copy ){

	matrix = copy.matrix;

	return *this;
}

bool Preferencematrix::operator==( const Preferencematrix& rhs ) const{

	if( matrix == rhs.matrix )

		return true;

	else

		return false;
}

std::ostream& operator<<( std::ostream& os, Preferencematrix& matrix ){

    os << "Preference Matrix\n\n" << "\t\t\tOptions/Alternatives Columns\n\n";

    for( std::vector<int>::size_type i = 0; i < matrix.get_matrix( ).size( ); ++i ){

        os << "Row vector id number: " << i << "| ";

        for( std::vector<int>::size_type j = 0; j < matrix[ i ].size( ); ++j ){

            os << "( " << matrix[ i ][ j ].get_opt( )
               << ", " << matrix[ i ][ j ].get_value( ) << " ) ";
        }

        os << "\n";
    }

    return os;
}

/* Helpers */

// Deletes an specific row. Used in Agent.h class
void Preferencematrix::delete_row( int rowindex ){

	matrix.erase( matrix.begin( ) + rowindex );
}
