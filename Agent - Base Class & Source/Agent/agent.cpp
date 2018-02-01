#include "agent.h"

/// Constructors

// Default Constructor
Agent::Agent( ){

	preferences = {};

	id = "";
}

Agent::Agent( std::vector<Agent> list, std::string name ){

	preferences = list;

	id = name;
}

/// Setters

// Reads a list of available agents. Randomly selects an element from the list.
// Puts selected element into preference.

// Need to fix: For vector Agent elements to hold push back value
//				For Agent one preferences
void Agent::set_ordering( std::vector<Agent>& list ){

	std::vector<Agent> vetor = list;

	while( vetor.size( ) > 0 ){

		// Selects a random agent
		int randindex = rand( ) % vetor.size( );

		if( *this != vetor[ randindex ] )

			preferences.push_back( vetor[ randindex ] );

		// Erases from vector: end-loop checking; avoids errors when randindex is the same
		// on next loop iteration
		vetor.erase( vetor.begin( ) + randindex );
	}
}

/// Getters


/// Operators

Agent& Agent::operator=( Agent one ){

	id = one.get_id( );

	preferences = one.get_preferences();

	return *this;
}

// Overloaded <<: gets agent's id
std::ostream& operator<<( std::ostream& os, Agent one ){

	return os << one.get_id();
}

// Add operator<< to print preferences

// Comparing agents
bool operator==( Agent& one, Agent& two ){

	// Modified: deleted && one.get_status( ) == two.get_status( )
	if( one.get_id( ) == two.get_id( ) )

		return true;

	else

		return false;
}
bool operator!=( Agent& one, Agent& two ){

	if( one.get_id( ) == two.get_id( ) )

		return false;

	else

		return true;
}

// Prints pairs
std::ostream& operator<<( std::ostream& os, PairOfAgents& list ){

	return os << list.one.get_id( ) << ' ' << list.two.get_id( );
}
