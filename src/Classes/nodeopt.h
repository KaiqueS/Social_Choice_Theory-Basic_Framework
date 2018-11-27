#pragma once

#ifndef NODEOPT_H
#define NODEOPT_H

#include "Classes/options.h"

class NodeOpt{

public:

    // Constructors & Destructor
    NodeOpt( );
	NodeOpt( char option, int link );
    NodeOpt( const NodeOpt& copy );

    ~NodeOpt( ){ }

    // Setters
	void set_id( char option );

	void set_index( int val );
    void set_link( int link );

    void set_onstack( bool val );

    // Getters
	char get_opt( ){ return id; }

	int get_index( ){ return index; }
    int get_link( ){ return lowlink; }

    bool get_onstack( ){ return onstack; }

    // Operators
    NodeOpt& operator=( const NodeOpt& copy );

private:

	char id{ };

	int index{ -1 };
	int lowlink{ -1 };

    bool onstack{ };
};

#endif // NODEOPT_H
