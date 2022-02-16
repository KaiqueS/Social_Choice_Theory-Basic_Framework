#pragma once

#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\preferencematrix.hpp"

class Agent{

public:

    // Constructors & Destructor
    Agent( );
    Agent( std::string tag, Profile list ) : id( tag ), preferences( list ){ }
	Agent( const Agent& copy );
	Agent( Agent&& copy );
    ~Agent( );

    // Setters
	void set_id( std::string tag );
	
	void set_preferences( Profile& profile );
	//void set_preferences( Preferencematrix& prefmatrix );// Maybe pass a profile, instead, and take it from PrefMtx? - REMOVED: useless and WRONG

    // Getters
	std::string get_id( ) const{ return id; }

    Profile get_preferences( ) const{ return preferences; }

    // Operators
    Agent& operator=( const Agent& one );
	Agent& operator=( Agent&& one );

    Options& operator[ ]( const std::vector<int>::size_type& index ){ return preferences[ index ]; }

    // Helpers
    void sort_preferences( );

    void clear( );

private:

	std::string id{ }; // must be constant

    Profile preferences{ }; // A row of the preferencematrix class. One row for each agent
};

/// Non-member Helpers
std::ostream& operator<<( std::ostream& os, Agent& agt );

inline bool operator==( const Agent& one, const Agent& two ){

	// Modified: deleted && one.get_status( ) == two.get_status( )
	if( one.get_id( ) == two.get_id( ) )

		return true;

	else

		return false;
}
inline bool operator!=( const Agent& one, const Agent& two ){ return !operator==( one, two ); }

#endif // AGENT_H
