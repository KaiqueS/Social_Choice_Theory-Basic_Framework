#include "preferencematrix.hpp"

/// Constructors

// Default Constructor. Initializes private members to its default values
Preferencematrix::Preferencematrix( ){

    rowsize = { };
    columnsize = { };

    matrix = { };
}

// Parameterize constructor. Sets a matrix of ROW x COL dimensions
Preferencematrix::Preferencematrix( std::vector<int>::size_type row, std::vector<int>::size_type col ){

    rowsize = row;
    columnsize = col;

    set_matrix( row, col );
}

// Copy Constructor. Initializes values according to parameters
Preferencematrix::Preferencematrix( const Preferencematrix& copymatrix ){

    rowsize = copymatrix.rowsize;
    columnsize = copymatrix.columnsize;

    matrix = copymatrix.matrix;
}

// Destructor. Clears the vector MATRIX from memory
Preferencematrix::~Preferencematrix( ){ clear( ); }

/// Setters

// Sets ROWSIZE to row - TODO: modify this
void Preferencematrix::set_rowsz( std::vector<int>::size_type row ){ rowsize = row; }

// Sets COLUMNSIZE to col - TODO: modify this
void Preferencematrix::set_columnsz( std::vector<int>::size_type col ){ columnsize = col; }

// Set a matrix of RowSZ x ColSZ dimensions. Sets a random value to each alternative, where this
// value ranges from 0 to colsz
// TODO: Problem generating options' ids
void Preferencematrix::set_matrix( std::vector<int>::size_type rowsz, std::vector<int>::size_type colsz ){

    // Initializes ROWSIZE and COLUMNSIZE to rowsz and colsz
    rowsize = rowsz;
    columnsize = colsz;

    // Generates a profile of colsz size. Every option in this profile is initialized
    // to its default values
    Profile setofalts( colsz );

    // Workaroung below. Begin
	int aux{ 30 };

    // Maps int into chars, store in a stack, assign it to a string
	// Sets alternatives' id's
	for( std::vector<int>::size_type i = 0; i < setofalts.size( ); ++i ){

        while( !isalnum( aux ) )

			++aux;

        char id = static_cast<char>( aux );

        setofalts[ i ].set_opt( std::to_string( id ) );

		++aux;
	}
    // Workaround above. End

	// Sets alternatives' values
	for( std::vector<int>::size_type i = 0; i < rowsz; ++i ){

		matrix.push_back( setofalts );

		for( std::vector<int>::size_type j = 0; j < colsz; ++j ){

            int val = rand( ) % static_cast<int>( colsz );

			matrix[ i ][ j ].set_value( val );
		}
	}
}

/// Getters

/// Operators

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

/// Helpers

// Deletes an specific row. Used in Agent.h class - TODO: erase-remove idiom
void Preferencematrix::erase_row( const std::vector<int>::size_type index ){ matrix.erase( std::remove( matrix.begin( ), matrix.end( ), index ), matrix.end( ) ); }

bool Preferencematrix::empty( ){

    if( matrix.empty( ) )

        return true;

    else

        return false;
}

void Preferencematrix::clear( ){

    matrix.clear( );

    std::vector<Profile>( ).swap( matrix );
}

/// Non-member helpers

// Prints PreferenceMatrix
std::ostream& operator<<( std::ostream& os, Preferencematrix& matrix ){

    // Gets the number of profiles
    std::vector<int>::size_type rowsz = matrix.get_matrix( ).size( );

    // Gets the number of options in each profile
    std::vector<int>::size_type colsz = matrix[ static_cast<std::vector<int>::size_type>( rand( ) ) % rowsz ].size( );

    os << "Preference Matrix\n\n" << "\t\t\tOptions/Alternatives Columns\n\n";

    for( std::vector<int>::size_type i = 0; i < rowsz; ++i ){

        os << "Row vector id number: " << i << "| ";

        for( std::vector<int>::size_type j = 0; j < colsz; ++j ){

            os << "( " << matrix[ i ][ j ].get_opt( )
               << ", " << matrix[ i ][ j ].get_value( ) << " ) ";
        }

        os << "\n";
    }

    return os;
}

Profile make_social_order( Profile& profile, Preferencematrix& matrix ){

    // Instantiates the resulting profile
    Profile socialorder{ };

    if( matrix.empty( ) ){

        initialize_opts( matrix, profile );
    }

    else{

        // For every profile in MATRIX
        for( std::vector<int>::size_type i = 0; i < matrix.size( ); ++i ){

            // For every option in every matrix PROFILE
            for( std::vector<int>::size_type j = 0; j < matrix[ i ].get_alternatives( ).size( ); ++j ){

                // Searches, in SOCIALORDER, for every option in every matrix's profile i
                for( std::vector<int>::size_type k = 0; k < socialorder.size( ); ++k ){

                    // If it is the case that an option in SOCIALORDER is the same as an option
                    // in an matrix's profile
                    if( socialorder[ k ].get_opt( ) == matrix[ i ][ j ].get_opt( ) ){

                        // Then, increment SOCIALORDER[ k ]'s value
                        // WTF: where did this 4 come from? Should not it be POPULATION.SIZE instead?
                        // TODO: debug this
                        socialorder[ k ] += ( static_cast<int>( ( socialorder.size( ) - j ) / 4 ) );
                    }
                }
            }
        }
    }

    return socialorder;
}

bool operator!=( Preferencematrix& left, Preferencematrix& right ){

    if( left.get_matrix( ) != right.get_matrix( ) )

        return true;

    else

        return false;
}

void initialize_opts( Preferencematrix& matrix, Profile& profile ){

	std::cout << "Is the error here?./n";

	profile = *matrix.begin( );

	std::cout << "Is the error here?./n";

    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        profile[ i ].set_value( 0 );
    }
}
