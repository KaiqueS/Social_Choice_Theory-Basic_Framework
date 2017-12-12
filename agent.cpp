#include "agent.h"

//Class functions

// Default Constructor
Agent::Agent( ){

	preferences = {};

	id = "";

	status = false;
}

// Returns agent n status
bool Agent::get_status( ){

	// if married

		// check to whom

		// cout the agent is married with w

		// return agent is married

	// else

		// return single
}


// Will be deleted after set_ordering is done. Reason: Similar purpose. Double code.
void Agent::set_preferences( std::vector<Agent> list  ){

	preferences = list;
}

// Receives a list of available agents. Randomly selects an element from the list.
// Puts selected element into preference.
// TODO: Check for double inputs of the same element, i.e., randomly select an
// unique element
void Agent::set_ordering( std::vector<Agent> list ){

	for( int i = 0; i < list.size( ); ++i ){

		int randindex = rand( ) % list.size( );

		preferences.push_back( list[ randindex ] );

		list.erase( list.begin( ) + randindex );
	}
}

// Self-explained
void Agent::operator=( Agent one ){

	this -> set_id( one.get_id() );

	this -> set_status( one.get_status( ) );

	//this -> set_ordering( one.get_preferences() );
}

// Sets status according to if agent n is married or free
const void Agent::set_status( bool status ){

	// check if the agent is married

		// if married

			// status = married

		// else

			// keep single
}

// Self-explained
const void Agent::set_id( std::string name ){ id = name; }

//Struct functions

// Will be deleted. void set_pairs does the same thing
void PairOfAgents::set_agents( Agent one, Agent two ){

	this -> one = one;

	this -> two = two;
}

//Member functions

std::ostream& operator<<( std::ostream& os, Agent& one ){

	return os << one.get_id();
}

bool operator==( Agent& one, Agent& two ){

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

// Sets pairs of agents
void set_pairs( std::vector<Agent> agents, std::vector<PairOfAgents>& list ){

	list[ 0 ].one = agents[ 0 ];

	list[ 0 ].two = agents[ 1 ];
}
