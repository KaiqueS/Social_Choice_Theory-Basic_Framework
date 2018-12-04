#pragma once

#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "options.h"
#include "preferencematrix.h"

// Changes: modified set_preferences -> Removed passing by reference

class Agent{

public:

    // Constructors & Destructor
    Agent( );
    Agent( std::vector<Options> list, std::string tag );
    Agent( const Agent& copy );

    ~Agent( ){ std::cout << "Agent " << id << " destructed.\n\n"; }

    // Setters
    void set_preferences( Preferencematrix& prefmatrix );

    void set_id( std::string tag );

    // Getters
    std::vector<Options> get_preferences( ){ return preferences; }

    std::vector<Options> get_sorted_preferences( );

    std::string get_id( ){ return id; }

    // Operators
    Agent& operator=( const Agent& one );

    Options& operator[ ]( const std::vector<int>::size_type& index ){ return preferences[ index ]; }

    // Helpers
    void print_rank( );

private:

    // A row of the preferencematrix class. One row for each agent
    std::vector<Options> preferences{ };

    std::string id{ }; // must be constant
};

std::ostream& operator<<( std::ostream& os, Agent& agt );

#endif // AGENT_H
