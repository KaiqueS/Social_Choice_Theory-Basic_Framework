#include "agent.h"

//Class functions

Agent::Agent( ){

	preferences = {};

	id = "";

	status = false;
}

bool Agent::get_status( ){

	// if married

		// check to whom

		// cout the agent is married with w

		// return agent is married

	// else

		// return single
}

void Agent::set_ordering( Agent options ){

	preferences.push_back( options );
}

void Agent::operator=( Agent one ){

	this -> set_id( one.get_id() );

	this -> set_status( one.get_status( ) );

	//this -> set_ordering( one.get_preferences() );
}

const void Agent::set_status( bool status ){

	// check if the agent is married

		// if married

			// status = married

		// else

			// keep single
}
const void Agent::set_id( std::string name ){ id = name; }

//Struct functions

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

void set_pairs( std::vector<Agent> agents, std::vector<PairOfAgents>& list ){

	list[ 0 ].one = agents[ 0 ];

	list[ 0 ].two = agents[ 1 ];
}
