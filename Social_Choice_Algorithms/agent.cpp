#include "agent.h"

/* Constructors */

// Default Constructor
Agent::Agent( ){

    preferences = { };

    id = { };
}

// Parameterized Constructor
Agent::Agent( std::vector<Options> list, std::string name ){

    preferences = list;

    id = name;
}

// Copy constructor
Agent::Agent( const Agent& copy ){

    preferences = copy.preferences;

    id = copy.id;
}

/* Setters */

// Sets agent's preferences. Takes a random row from PrefMatrix and set it to be the agent's preferences.
// Deletes the used row at the end: Avoids repeated preferences for different agents
void Agent::set_preferences( Preferencematrix& prefmatrix ){

    std::vector<int>::size_type randindex = static_cast<std::vector<int>::size_type>( rand( ) ) % prefmatrix.get_matrix( ).size( );

    preferences = prefmatrix.get_matrix( )[ randindex ];

    prefmatrix.delete_row( static_cast<int>( randindex ) );
}

void Agent::set_id( std::string tag ){ id = tag; }

/* Getters */

/* Operators */

// Overloaded assignment operator.
Agent& Agent::operator=( const Agent& one ){

    id = one.id;

    preferences = one.preferences;

    return *this;
}

// Comparing agents
bool operator==( Agent& one, Agent& two ){

    // Modified: deleted && one.get_status( ) == two.get_status( )
    if( one.get_id( ) == two.get_id( ) )

        return true;

    else

        return false;
}
bool operator!=( Agent& one, Agent& two ){

    if( one.get_id( ) != two.get_id( ) )

        return true;

    else

        return false;
}

/* Helpers */

// Sorts an agent's preferences in decreasing order, according to an option's value
void Agent::sort_preferences( ){

    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( preferences.begin( ), preferences.end( ), order );
}

// Prints options that have the same value
void Agent::print_rank( ){

    //Prints the rank of preferences
    std::cout << "Agent " << id << " Rank alternatives \t";

    sort_preferences( );

    int aux = preferences.begin( ).base( ) -> get_value( );

    std::cout << "[ ";

    for( std::vector<int>::size_type i = 0; i < preferences.size( ); ++i ){

        if( preferences[ i ].get_value( ) != aux){

            std::cout << "] > [ ";

            aux = preferences[ i ].get_value( );
        }

        std::cout << preferences[ i ].get_opt( ) << " ";
    }

    std::cout << "] ";
}

std::ostream& operator<<( std::ostream& os, Agent& agt ){

    os << agt.get_id( ) << " preferences: ";

    for( Options opt : agt.get_preferences( ) )

        os << "( " << opt << " )";

    return os;
}
