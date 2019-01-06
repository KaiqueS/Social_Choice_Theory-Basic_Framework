#pragma once

#ifndef SCTGRAPH_H
#define SCTGRAPH_H

#include "socialprefnode.hpp"
#include "agent.hpp"
#include "sctrank.hpp"
#include "preferencematrix.hpp"

class Graph{

public:

    // Constructors & Destructor
    Graph( );
    Graph( std::vector<SocialPrefNode> vertices );
    Graph( const Graph& copy );

    ~Graph( ){ }

    // Setters
    void set_graph( std::vector<SocialPrefNode> vertices );
    void set_graph( SocialPrefNode node, std::vector<int>::size_type index );
    void set_graph( SocialPrefNode node );

    // Getters
    std::vector<SocialPrefNode> get_graph( ){ return nodes; }

    std::vector<int>::size_type size( ){ return nodes.size( ); }

    // Operators
    Graph& operator=( const Graph& copy );

    SocialPrefNode& operator[ ]( const std::vector<int>::size_type index );

    // Helpers
    void initialize_graph( Preferencematrix& mtx );

    void make_graph( Preferencematrix& mtx, Rank& rank );

private:

    std::vector<SocialPrefNode> nodes{ };
};

std::ostream& operator<<( std::ostream& os, Graph& graph );

void print_graph( Graph& graph );

#endif // SCTGRAPH_H
