#include "pareto_principle.hpp"

/// Constructors & Destructor

SCT::Pareto_Principle::Pareto_Principle( const SCT::Pareto_Principle& copy ){

	matrix = copy.matrix;

	population = copy.population;

	rank = copy.rank;
}
SCT::Pareto_Principle::Pareto_Principle( SCT::Pareto_Principle&& copy ){

	matrix = copy.matrix;

	population = copy.population;

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

	population = copy.population;

	rank = copy.rank;

	copy.clear( );

	return  *this;
}

bool SCT::Pareto_Principle::operator( )( SCT::Procedure& procedure ){

	// Problem here: agents with no preferences
	population.order_preferences( );

	//std::cout << "Debug 1.\n";

	Options optimum{ };

	for( std::vector<int>::size_type i = 0; i < population.size( ); ++i ){

		for( std::vector<int>::size_type j = 0; j < population[ i ].get_preferences( ).size( ); ++j ){

			for( std::vector<int>::size_type k = j + 1; k < population[ i ].get_preferences( ).size( ); ++k ){

				if( population[ i ][ j ].get_value( ) == population[ i ][ k ].get_value( ) ){

					return true;
				}

				else{

					optimum = population[ i ][ j ];

					optimum.set_status( true );

					continue;
				}
			}
		}
	}

	//std::cout << "Debug 2.\n";

	if( optimum.get_opt( ) != procedure( population ).get_alternatives( ).begin( )->get_opt( ) )

		return false;

	else

		return true;
}

/// Helpers

void SCT::Pareto_Principle::clear( ){

	matrix.clear( );

	population.clear( );

	rank.clear( );
}