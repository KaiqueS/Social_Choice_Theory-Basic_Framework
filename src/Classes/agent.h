#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <QDataStream>
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

	void setPreferences(const std::vector<Options<Prefs> >& value);

	// Getters
	std::vector<Options<Prefs>> get_preferences( ){ return preferences; }

    std::vector<Options<Prefs>> get_sorted_preferences( );

	std::string get_id( ){ return id; }

	// Operators

	Agent& operator=( const Agent<Prefs>& one );

	Options<Prefs>& operator[ ]( const int& index ){ return preferences[ index ]; }

	// Helpers

    void print_prefs( );
    void print_rank( );


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
template<typename Prefs> std::vector<Options<Prefs>> Agent<Prefs>::get_sorted_preferences( ){

    //Returns a vector of options sorted by the value
    std::vector<Options<Prefs>> indiff{ };

	for( std::vector<int>::size_type i = 0; i < preferences.size( ); ++i ){

		std::vector<Options<char>>::iterator aux;

		aux = indiff.begin( );

		int iValue = preferences[ i ].get_value( );

		for( std::vector<int>::size_type j = 0; j < indiff.size( ) &&

			iValue <= indiff[ j ].get_value( ); ++j ){

			++aux;
        }

		indiff.insert( aux, preferences[ i ] );
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
template<typename Prefs> void Agent<Prefs>::print_rank( ){

    //Print the rank of preferences
	std::cout << "Agent " << id << " Rank alternatives: ";

	int aux = get_sorted_preferences( ).begin( ) -> get_value( );

	std::cout << "[ ";

	for( std::vector<int>::size_type i = 0; i < get_sorted_preferences( ).size( ); ++i ){

		if( get_sorted_preferences( )[ i ].get_value( ) != aux ){

			std::cout << "] > [ ";

			aux = get_sorted_preferences( )[ i ].get_value( );
        }

		std::cout << get_sorted_preferences( )[ i ].get_alternatives( ) << " ";
    }

	std::cout << "] ";
}

template<typename Prefs> void Agent<Prefs>::setPreferences(const std::vector<Options<Prefs> >& value){preferences = value;}

#endif // AGENT_H
