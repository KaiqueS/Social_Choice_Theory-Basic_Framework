#include "population.hpp"

/// Constructors & Destructor
Population::Population( ){ population = { }; }

Population::Population( std::vector<int>::size_type size ){ population.resize( size ); }

Population::Population( Agent person ){ population.push_back( person ); }

Population::Population( const Population& copy ){ population = copy.population; }

Population::~Population( ){

	//std::cout << "Population deleted.\n";

    population.clear( );

	// Freeing the vector from the memory
	std::vector<Agent>( ).swap( population );
}

/// Setters

void Population::set_population( std::vector<Agent>& people ){ population = people; }
void Population::set_population( Agent& people ){ population.push_back( people ); }

/// Getters

/// Operators
Population& Population::operator=( const Population& copy ){

    population = copy.population;

    return *this;
}

/// Helpers

bool Population::empty( ){ return population.empty( ); }

void Population::initialize_population( Preferencematrix mtx ){

	if( population.empty( ) )

		*this = Population( mtx.size( ) );

	else{

		for( std::vector<int>::size_type i = 0; i < population.size( ); ++i ){

			population[ i ].set_id( std::to_string( i ) );
			population[ i ].set_preferences( mtx );
		}
	}
}

void Population::order_preferences( ){

    for( std::vector<int>::size_type i = 0; i < population.size( ); ++i )

        population[ i ].sort_preferences( );
}

/// Non-member Helpers

std::ostream& operator<<( std::ostream& os, Population& people ){

    for( std::vector<int>::size_type i = 0; i < people.get_population( ).size( ); ++i ){

        os << people[ i ] << " ";
    }

    return os;
}

void initialize_opts( Population& listofagents, Profile& opts ){

    std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );

    if( !listofagents[ randagt ].get_preferences( ).empty( ) ){

        opts = listofagents[ randagt ].get_preferences( ).get_alternatives( );

        for( std::vector<int>::size_type i = 0; i < opts.size( ); ++i )

            opts[ i ].set_value( 0 );
    }

    else{

        std::cerr << "Agent " << listofagents[ randagt ].get_id( ) << " has no preferences.\n";
    }
}

Profile make_social_order( Population& population ){

    Profile socialorder{ };

    initialize_opts( population, socialorder );

    population.order_preferences( );

    for( std::vector<int>::size_type i = 0; i < population.size( ); ++i ){

        for( std::vector<int>::size_type j = 0; j < population[ i ].get_preferences( ).size( ); ++j ){

            for( std::vector<int>::size_type k = 0; k < socialorder.size( ); ++k ){

                if( socialorder[ k ].get_opt( ) == population[ i ][ j ].get_opt( ) ){

                    socialorder[ k ] += ( static_cast<int>( ( socialorder.size( ) - j ) / 4 ) );
                }
            }
        }
    }

    return socialorder;
}
