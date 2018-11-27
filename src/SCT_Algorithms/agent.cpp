#include "Classes/agent.h"

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

// Checks if two different preferences have the same value. If they do, the agent is
// indifferent between then.
std::vector<Options> Agent::get_sorted_preferences( ){

    //Returns a vector of options sorted by the value
    std::vector<Options> indiff{ };

    for( std::vector<int>::size_type i = 0; i < preferences.size( ); ++i ){

        std::vector<Options>::iterator aux{ };

        aux = indiff.begin( );

        int iValue = preferences[ i ].get_value( );

        for( std::vector<int>::size_type j = 0; j < indiff.size( ) && iValue <= indiff[ j ].get_value( ); ++j ){

            aux++;
        }

        indiff.insert( aux, preferences[ i ] );
    }

    return indiff;
}

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

// Prints options that have the same value
void Agent::print_rank( ){

    //Prints the rank of preferences
    std::cout << "Agent " << id << " Rank alternatives \t";

    int aux = get_sorted_preferences( )[0].get_value();

    std::cout << "[ ";

    for( std::vector<int>::size_type i = 0; i < get_sorted_preferences( ).size( ); ++i ){

        if( get_sorted_preferences( )[ i ].get_value( ) != aux){

            std::cout << "] > [ ";

            aux = get_sorted_preferences( )[ i ].get_value( );
        }

        std::cout << get_sorted_preferences( )[ i ].get_opt( ) << " ";
    }

    std::cout << "] ";
}

std::ostream& operator<<( std::ostream& os, Agent& agt ){

    os << agt.get_id( ) << " preferences: ";

    for( Options opt : agt.get_preferences( ) )

        os << "( " << opt << " )";

    return os;
}
