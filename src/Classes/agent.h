#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "options.h"
#include "preferencematrix.h"

// I do not like letting the agents define the type of the preferences, this violates encapsulation
template<typename Prefs> class Agent{

public:

	// Constructors & Destructor
	Agent( );
	Agent( std::vector<Options<Prefs>> list, std::string name );
	Agent( const Agent& copy );

	~Agent( ){ std::cout << "Agent " << id << " destructed.\n\n"; }

	// Setters
	void set_preferences( Preferencematrix<Prefs>& prefmatrix );

	void set_id( std::string name ){ id = name; }

	// Getters
	std::vector<Options<Prefs>> get_preferences( ){ return preferences; }

	std::string get_id( ){ return id; }

	void print_prefs( );
	void check_indifference( );

	// Operators
	Agent& operator=( const Agent<Prefs>& one );

	Options<Prefs>& operator[ ]( const int& index ){ return preferences[ index ]; }

private:

	// A row of the preferencematrix class. One row for each agent
	std::vector<Options<Prefs>> preferences;

	std::string id{ }; // must be constant
};

/* Constructors */

// Default Constructor
template<typename Prefs> Agent<Prefs>::Agent( ){

	preferences = { };

	id = { };
}

// Parameterized Constructor
template<typename Prefs> Agent<Prefs>::Agent( std::vector<Options<Prefs>> list, std::string name ){

	preferences = list;

	id = name;
}

// Copy constructor
template<typename Prefs> Agent<Prefs>::Agent( const Agent& copy ){

	preferences = copy.preferences;

	id = copy.id;
}

/* Setters */

// Sets agent's preferences. Takes a random row from PrefMatrix and set it to be the agent's preferences.
// Deletes the used row at the end: Avoid repeated preferences for different agents
template<typename Prefs> void Agent<Prefs>::set_preferences( Preferencematrix<Prefs>& prefmatrix ){

	int randindex = std::rand( ) % prefmatrix.get_matrix( ).size( );

	preferences = prefmatrix.get_matrix( )[ randindex ];

	prefmatrix.delete_row( randindex );
}

/* Getters */

// Prints preferences
template<typename Prefs> void Agent<Prefs>::print_prefs( ){

	std::cout << "Agent " << this -> get_id( ) << " preferences: ";

	for( int i = 0; i < preferences.size( ); ++i ){

		std::cout << "( " << preferences[ i ].get_alternatives( ) << " , "
				  << preferences[ i ].get_value( ) << " ) ";
	}

	std::cout << "\n";
}

// Checks if two different preferences have the same value. If they do, the agent is
// indifferent between then.
// TODO: Repetition ongoing: double printing, when i != j and j != i, even though the preferences are the same
template<typename Prefs> void Agent<Prefs>::check_indifference( ){

	for( int i = 0; i < preferences.size( ); ++i ){

		for( int j = 0; j < preferences.size( ); ++j ){

			if( i != j && preferences[ i ].get_value( ) == preferences[ j ].get_value( ) ){

				std::cout << "Agent " << this -> get_id( ) << " is indifferent between preferences " << i
						  << "- ( " << preferences[ i ].get_alternatives( ) << ", " << preferences[ i ].get_value( )
						  << " ) and " << j << "- ( " << preferences[ j ].get_alternatives( ) << ", "
						  << preferences[ j ].get_value( ) << " )\n";
			}
		}
	}
}

/* Operators */

// Overloaded assignment operator.
template<typename Prefs> Agent<Prefs>& Agent<Prefs>::operator=( const Agent<Prefs>& one ){

	id = one.id;

	preferences = one.preferences;

	return *this;
}

// Comparing agents
template<typename Prefs> bool operator==( Agent<Prefs>& one, Agent<Prefs>& two ){

	// Modified: deleted && one.get_status( ) == two.get_status( )
	if( one.get_id( ) == two.get_id( ) )

		return true;

	else

		return false;
}
template<typename Prefs> bool operator!=( Agent<Prefs>& one, Agent<Prefs>& two ){

	if( one.get_id( ) != two.get_id( ) )

		return true;

	else

		return false;
}
#endif // AGENT_H
