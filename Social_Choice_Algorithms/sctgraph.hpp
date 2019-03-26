#pragma once

#ifndef SCTGRAPH_H
#define SCTGRAPH_H

#include "socialprefnode.hpp"
#include "population.hpp"
#include "sctrank.hpp"
#include "preferencematrix.hpp"

class Graph{

public:

    // Constructors & Destructor
    Graph( );
    Graph( SocialPrefNode node );
    Graph( std::vector<SocialPrefNode> vertices ) : nodes( vertices ){ }
	Graph( std::initializer_list<SocialPrefNode> init ) : nodes( std::move( init ) ){ }
    Graph( const Graph& copy );

    ~Graph( );

    // Setters
    void set_graph( std::vector<SocialPrefNode> vertices );
    void set_graph( SocialPrefNode node, std::vector<int>::size_type index );
    void set_graph( SocialPrefNode node );

    // Getters
    std::vector<SocialPrefNode> get_graph( ) const{ return nodes; }

    // Operators
    Graph& operator=( Graph copy );

    SocialPrefNode& operator[ ]( const std::vector<int>::size_type index );

    // Helpers
    void initialize_graph( Population& population );
    void initialize_graph( Preferencematrix& mtx );
    void make_graph( Preferencematrix& mtx, Rank& rank );
    void push_back( SocialPrefNode& node ){ nodes.push_back( node ); }
    void clear( ){ nodes.clear( ); }

    std::vector<int>::size_type size( ){ return nodes.size( ); }

    std::vector<SocialPrefNode, std::allocator<SocialPrefNode>>::iterator begin( ){ return nodes.begin( ); }
    std::vector<SocialPrefNode, std::allocator<SocialPrefNode>>::iterator end( ){ return nodes.end( ); }

	bool empty( );

private:

    std::vector<SocialPrefNode> nodes{ };
};

// Non-member helpers
std::ostream& operator<<( std::ostream& os, Graph& graph );

inline bool operator==( const Graph& left, const Graph& right ){

	if( left.get_graph( ) == right.get_graph( ) )

		return true;

	else

		return false;
}
inline bool operator!=( const Graph& left, const Graph& right ){ return !operator==( left, right ); }

void print_graph( Graph& graph );

#endif // SCTGRAPH_H
