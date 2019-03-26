#pragma once

#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "preferencematrix.hpp"

class Agent{

public:

    // Constructors & Destructor
    Agent( );
    Agent( Profile list, std::string tag ) : preferences( list ), id( tag ){ }
    Agent( const Agent& copy );
    ~Agent( );

    // Setters
    // Maybe pass a profile, instead, and take it from PrefMtx?
    void set_preferences( Preferencematrix& prefmatrix );

    void set_id( std::string tag );

    // Getters
    Profile get_preferences( ) const{ return preferences; }

    std::string get_id( ) const{ return id; }

    // Operators
    Agent& operator=( Agent one );

    Options& operator[ ]( const std::vector<int>::size_type& index ){ return preferences[ index ]; }

    // Helpers
    void sort_preferences( );

private:

    // A row of the preferencematrix class. One row for each agent
    Profile preferences{ };

    std::string id{ }; // must be constant
};

std::ostream& operator<<( std::ostream& os, Agent& agt );

inline bool operator==( const Agent& one, const Agent& two ){

	// Modified: deleted && one.get_status( ) == two.get_status( )
	if( one.get_id( ) == two.get_id( ) )

		return true;

	else

		return false;
}

inline bool operator!=( const Agent& one, const Agent& two ){

	return !operator==( one, two );
}

#endif // AGENT_H
