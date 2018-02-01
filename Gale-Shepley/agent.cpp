#include "agent.h"

//Class functions

// Default Constructor
Agent::Agent( ){

	preferences = {};

	id = "";

	status = false;
}

// Reads a list of available agents. Randomly selects an element from the list.
// Puts selected element into preference.
void Agent::set_ordering( std::vector<Agent> list ){

	// Checks if the agent itself is not being put in its own list
	for( int i = 0; i < list.size( ); ++i )

		if( list[ i ].get_id( ) == id )

			list.erase( list.begin( ) + i );

	while( list.size( ) > 0 ){

		// Selects a random agent
		int randindex = rand( ) % list.size( );

		// Checks if it is of another sex, puts in preferences vector
		if( list[ randindex ].get_sex( ) != sex  )

			preferences.push_back( list[ randindex ] );

		// Erases from vector: end-loop checking; avoids errors when randindex is the same
		// on next loop iteration
		list.erase( list.begin( ) + randindex );
	}
}

// Included sex = one.get_sex( )
void Agent::operator=( Agent one ){

	id = one.get_id( );

	sex = one.get_sex( );

	status = one.get_status( );

	preferences = one.get_preferences();
}

// Argument: vector or agent?
void Agent::updt_ordr_sts( Agent substitute ){

	for( int i = 0; i < preferences.size( ); ++i )

		if( preferences[ i ] == substitute  )

			preferences[ i ].set_status( substitute.get_status( ) );

}

const void Agent::set_status( bool stat ){

	// True = married, False = free
	status = stat;
}

// Self-explained. Find some way to automatize this
const void Agent::set_id( std::string name ){ id = name; }

//Non-member functions

// Overloaded <<: gets agent's id
std::ostream& operator<<( std::ostream& os, Agent& one ){

	return os << one.get_id();
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

	if( one.get_id( ) == two.get_id( ) )

		return false;

	else

		return true;
}

// Prints pairs
std::ostream& operator<<( std::ostream& os, PairOfAgents& list ){

	return os << list.one.get_id( ) << ' ' << list.two.get_id( );
}
