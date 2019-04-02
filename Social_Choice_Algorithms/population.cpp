#include "population.hpp"

/// Constructors & Destructor

// Default constructor. Initializes the vector POPULATION of agents to its default values
Population::Population( ){ population = { }; }

// Alternative parameterized constructor. Resizes and initializes every agent in POPULATI
// ON to its default values
Population::Population( std::vector<int>::size_type size ){

    population.resize( size );
}

// Alternative parameterized constructor. Inserts an agent into POPULATION
Population::Population( Agent person ){ population.push_back( person ); }

// Copy constructor
Population::Population( const Population& copy ){ population = copy.population; }

// Destructor. Clears the vector POPULATION of memory
Population::~Population( ){

	//std::cout << "Population deleted.\n";

    population.clear( );

	// Freeing the vector from the memory
	std::vector<Agent>( ).swap( population );
}

/// Setters

// Assigns POPULATION to PEOPLE
void Population::set_population( std::vector<Agent>& people ){ population = people; }

// Inserts a new agent to the end of the vector POPULATION
void Population::set_population( Agent& people ){ population.push_back( people ); }

/// Getters

/// Operators

// Overloaded assignment operator
Population& Population::operator=( Population copy ){

	std::swap( *this, copy );

    return *this;
}

/// Helpers

// Helper method. Allows for treating the Population Class as a container.
// Return true when the vector POPULATION is empty
bool Population::empty( ){ return population.empty( ); }

// Initializes every agent's profile in POPULATION to a row in MTX
// TODO: chech if the number of rows in MTX = num of Agents in POP
// ULATION
void Population::initialize_population( Preferencematrix mtx ){

    // If POPULATION happens to be empty
    if( population.empty( ) ){

        // Then resize it
		population.resize( mtx.size( ) );

		return initialize_population( mtx );
	}

    // Else
	else{

		for( std::vector<int>::size_type i = 0; i < population.size( ); ++i ){

            // Assign an id to every agent in POPULATION
			population[ i ].set_id( std::to_string( i ) );

            // Assign a profile, taken here as a row in the PreferenceMatrix
            // MTX, to every agent
			population[ i ].set_preferences( mtx );
		}
	}
}

// Sorts the preferences of every agent in POPULATION in descending order
void Population::order_preferences( ){

    for( std::vector<int>::size_type i = 0; i < population.size( ); ++i )

        population[ i ].sort_preferences( );
}

/// Non-member Helpers

// Overloaded printing operator
std::ostream& operator<<( std::ostream& os, Population& people ){

    for( std::vector<int>::size_type i = 0; i < people.get_population( ).size( ); ++i ){

        os << people[ i ] << " ";
    }

    return os;
}

// Initializes a profile OPTS of preferences. Just a helper function
// used to fill a Profile of options
void initialize_opts( Population& listofagents, Profile& opts ){

    std::random_device rd;

    //std::mt19937_64 mt( rd( ) );
    std::mt19937 mt( rd( ) );

    std::uniform_int_distribution<std::vector<int>::size_type> index( 0, ( listofagents.size( ) - 1 ) );

    // Select a random agent from POPULATION
    //std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );

    // If the agent's profile of preferences is not empty
    if( /*!listofagents[ randagt ].get_preferences( ).empty( )*/ !listofagents[ index( mt ) ].get_preferences( ).empty( ) ){

        // Set OPTS to the agent's profile
        //opts = listofagents[ randagt ].get_preferences( );
        opts = listofagents[ index( mt ) ].get_preferences( );

        for( std::vector<int>::size_type i = 0; i < opts.size( ); ++i )

            // Sets the value of every option in OPTS to 0.
            // One only wants the alternatives, not its values!
            opts[ i ].set_value( 0 );
    }

    // Else, if the profile of the random agent is empty, print a warning message
    else{

        //std::cerr << "Agent " << listofagents[ randagt ].get_id( ) << " has no preferences.\n";
        std::cerr << "Agent " << listofagents[ index( mt ) ].get_id( ) << " has no preferences.\n";
    }
}

// Returns a generic social ordering of options, i.e., sorted profile. The ordering is based solely
// in how many votes each option got in a given POPULATION
Profile make_social_order( Population& population ){

    // Instantiates the resulting profile
    Profile socialorder{ };

    // Gets every alternatives that will be ranked
    initialize_opts( population, socialorder );

    // Orders the preferences of every agent in POPULATION.
    // Makes easier ranking options
    population.order_preferences( );

    // For every agent in POPULATION
    for( std::vector<int>::size_type i = 0; i < population.size( ); ++i ){

        // For every option in every agent PROFILE
        for( std::vector<int>::size_type j = 0; j < population[ i ].get_preferences( ).size( ); ++j ){

            // Searches, in SOCIALORDER, for every option in every agent's profile i
            for( std::vector<int>::size_type k = 0; k < socialorder.size( ); ++k ){

                // If it is the case that an option in SOCIALORDER is the same as an option
                // in an agent's profile
                if( socialorder[ k ].get_opt( ) == population[ i ][ j ].get_opt( ) ){

                    // Then, increment SOCIALORDER[ k ]'s value
                    // WTF: where did this 4 come from? Should not it be POPULATION.SIZE instead?
                    // TODO: debug this
                    socialorder[ k ] += ( static_cast<int>( ( socialorder.size( ) - j ) / 4 ) );
                }
            }
        }
    }

    return socialorder;
}
