#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\pareto_principle.hpp"

/// Constructors & Destructor

SCT::Pareto_Principle::Pareto_Principle( const SCT::Pareto_Principle& copy ){

	matrix = copy.matrix;

	rank = copy.rank;
}
SCT::Pareto_Principle::Pareto_Principle( SCT::Pareto_Principle&& copy ){

	matrix = copy.matrix;

	rank = copy.rank;

	copy.clear( );
}

SCT::Pareto_Principle::~Pareto_Principle( ){ clear( ); }

/// Setters

/// Getters

/// Operators

SCT::Pareto_Principle& SCT::Pareto_Principle::operator=( SCT::Pareto_Principle copy ){

	swap( *this, copy );
	return  *this;
}
SCT::Pareto_Principle& SCT::Pareto_Principle::operator=( SCT::Pareto_Principle&& copy ){

	matrix = copy.matrix;

	rank = copy.rank;

	copy.clear( );

	return  *this;
}

bool SCT::Pareto_Principle::operator( )( SCT::Procedure& procedure ){

	//std::cout << "Debug 1.\n";

	Options optimum{ };

	for( std::vector<int>::size_type i = 0; i < matrix.size( ); ++i ){

		for( std::vector<int>::size_type j = 0; j < matrix[ i ].size( ); ++j ){

			for( std::vector<int>::size_type k = j + 1; k < matrix[ i ].size( ); ++k ){

				if( matrix[ i ][ j ].get_value( ) == matrix[ i ][ k ].get_value( ) ){

					return true;
				}

				else{

					optimum = matrix[ i ][ j ];

					optimum.set_status( true );

					continue;
				}
			}
		}
	}

	//std::cout << "Debug 2.\n";

	if( optimum.get_opt( ) != procedure( matrix ).get_alternatives( ).begin( )->get_opt( ) )

		return false;

	else

		return true;
}

/// Helpers

void SCT::Pareto_Principle::clear( ){

	matrix.clear( );
	rank.clear( );
}