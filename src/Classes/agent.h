#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "options.h"
#include "preferencematrix.h"

// I do not like letting the agents define the type of the preferences, this violates encapsulation - when removing templates
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

	std::vector<Prefs> get_indifference( );

	std::string get_id( ){ return id; }

	// Operators
	Agent& operator=( const Agent<Prefs>& one );

	Options<Prefs>& operator[ ]( const int& index ){ return preferences[ index ]; }

	// Helpers

	void print_prefs( );
	void print_indifference( );

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
// Deletes the used row at the end: Avoids repeated preferences for different agents
template<typename Prefs> void Agent<Prefs>::set_preferences( Preferencematrix<Prefs>& prefmatrix ){

	int randindex = std::rand( ) % prefmatrix.get_matrix( ).size( );

	preferences = prefmatrix.get_matrix( )[ randindex ];

	prefmatrix.delete_row( randindex );
}

/* Getters */

// Checks if two different preferences have the same value. If they do, the agent is
// indifferent between then.
// TODO: Repetition ongoing: double printing, when i != j and j != i, even though the preferences are the same - DONE
template<typename Prefs> std::vector<Prefs> Agent<Prefs>::get_indifference( ){

	std::vector<Prefs> indiff{ };

	// Get all pairs ( x, y ), where votes( x ) == votes( y )
	for( std::vector<int>::size_type i = 0; i < preferences.size( ); ++i ){

		for( std::vector<int>::size_type j = 0; j < preferences.size( ); ++j ){

			if( i != j && preferences[ i ].get_value( ) == preferences[ j ].get_value( ) ){

				indiff.push_back( preferences[ i ].get_alternatives( ) );
				indiff.push_back( preferences[ j ].get_alternatives( ) );
			}
		}
	}

	// Removes repeated values
	for( std::vector<int>::size_type i = 0; i < indiff.size( ); ++i ){

		for( std::vector<int>::size_type j = 0; j < indiff.size( ); ++j ){

			if( i != j ){

				if( indiff[ i ] == indiff[ j ] ){

					indiff.erase( indiff.begin( ) + i );

					i = 0;
					j = 0;
				}
			}
		}
	}

	return indiff;
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

/* Helpers */

// Prints all preferences of an agent
template<typename Prefs> void Agent<Prefs>::print_prefs( ){

	std::cout << "Agent " << id << " preferences: ";

	for( std::vector<int>::size_type i = 0; i < preferences.size( ); ++i ){

		std::cout << "( " << preferences[ i ].get_alternatives( ) << " , "
				  << preferences[ i ].get_value( ) << " ) ";
	}

	std::cout << "\n";
}

// Prints options that have the same value
template<typename Prefs> void Agent<Prefs>::print_indifference( ){

	std::cout << "Agent " << id << " is indifferent between alternatives ";

	for( std::vector<int>::size_type i = 0; i < get_indifference( ).size( ); ++i ){

		std::cout << "[ " << get_indifference( )[ i ] << " ] ";
	}
}

#endif // AGENT_H
