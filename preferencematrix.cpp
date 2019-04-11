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

    std::random_device rd;

    //std::mt19937_64 mt( rd( ) );
    std::mt19937 mt( rd( ) );

    std::uniform_int_distribution<std::vector<int>::size_type> column( 0, ( colsz - 1 ) );

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

        // change to is alphabetical
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

            //int val = rand( ) % static_cast<int>( colsz );
            int val = static_cast<int>( column( mt ) );

			matrix[ i ][ j ].set_value( val );
		}
	}
}

/// Getters

/// Operators

// Overloaded assignment operator
Preferencematrix& Preferencematrix::operator=( Preferencematrix copy ){

	std::swap( *this, copy );

	return *this;
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
    //std::vector<int>::size_type colsz = matrix[ static_cast<std::vector<int>::size_type>( rand( ) ) % rowsz ].size( );
    std::vector<int>::size_type colsz = matrix.begin( ) -> get_alternatives( ).size( );

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

// MODIFIED: used to get two arguments ( Profile& profile, PreferenceMatrix& matrix )
Profile make_social_order( Preferencematrix& matrix ){

    Profile profile;

    initialize_opts( matrix, profile );

    if( matrix.empty( ) ){

        initialize_opts( matrix, profile );

        make_social_order( matrix );
    }

    else{

        for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i )

            profile[ i ].set_value( 0 );

        // For every profile in MATRIX
        for( std::vector<int>::size_type i = 0; i < matrix.size( ); ++i ){

            // For every option in every matrix PROFILE
            for( std::vector<int>::size_type j = 0; j < matrix[ i ].get_alternatives( ).size( ); ++j ){

                // Searches, in SOCIALORDER, for every option in every matrix's profile i
                for( std::vector<int>::size_type k = 0; k < profile.size( ); ++k ){

                    // If it is the case that an option in SOCIALORDER is the same as an option
                    // in an matrix's profile
                    if( profile[ k ].get_opt( ) == matrix[ i ][ j ].get_opt( ) ){

                        // Then, increment SOCIALORDER[ k ]'s value
                        // WTF: where did this 4 come from? Should not it be POPULATION.SIZE instead?
                        // TODO: debug this
                        profile[ k ] += ( static_cast<int>( ( profile.size( ) - j ) ) );
                    }
                }
            }
        }
    }

    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i )

        // THIS IS BULLSHIT. Fix it later
        profile[ i ].set_value( static_cast<int>( static_cast<std::vector<int>::size_type>( profile[ i ].get_value( ) ) / profile.size( ) ) );

    return profile;
}

void initialize_opts( Preferencematrix& matrix, Profile& profile ){

	// Hmmmmm.... potential bullshit behavior here
	profile = *matrix.begin( );

    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        profile[ i ].set_value( 0 );
    }
}
