#include "nodeopt.h"

/* Constructors & Destructor */

NodeOpt::NodeOpt( ){

	id = { ' ' };

	index = { -1 };
	lowlink = { -1 };
}
NodeOpt::NodeOpt( char option, int link ){

    id = option;

    lowlink = link;
}
NodeOpt::NodeOpt( const NodeOpt& copy ){

	id= copy.id;

    lowlink = copy.lowlink;
}

/* Setters */

void NodeOpt::set_id( char option ){ id = option; }

void NodeOpt::set_index( int val ){ index = val; }
void NodeOpt::set_link( int link ){ lowlink = link; }

void NodeOpt::set_onstack( bool val ){ onstack = val; }

/* Getters */

/* Operators */

NodeOpt& NodeOpt::operator=( const NodeOpt& copy ){

	id = copy.id;

    lowlink = copy.lowlink;

    return *this;
}

