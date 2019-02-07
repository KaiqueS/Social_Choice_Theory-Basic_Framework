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
    Profile get_preferences( ){ return preferences; }

    std::string get_id( ){ return id; }

    // Operators
    Agent& operator=( const Agent& one );

    Options& operator[ ]( const std::vector<int>::size_type& index ){ return preferences[ index ]; }

    // Helpers
    void sort_preferences( );

private:

    // A row of the preferencematrix class. One row for each agent
    Profile preferences{ };

    std::string id{ }; // must be constant
};

std::ostream& operator<<( std::ostream& os, Agent& agt );

#endif // AGENT_H
