#pragma once

#ifndef SCTGRAPH_H
#define SCTGRAPH_H

#include "socialprefnode.hpp"
#include "sctrank.hpp"
#include "preferencematrix.hpp"
#include "procedure.hpp"

// A graph should always be initialized BEFORE the edges are created
// How should graphs be made? From profiles resulting of aggregating procedures and from ranks!

class Graph{

public:

    // Constructors & Destructor
    Graph( );
    Graph( std::vector<SocialPrefNode> vertices ) : nodes( vertices ){ }
	Graph( std::initializer_list<SocialPrefNode> init ) : nodes( std::move( init ) ){ }
    Graph( const Graph& copy );
	Graph( Graph&& copy ) noexcept;
    Graph( Profile& profile );
    ~Graph( );

    // Setters
    void set_graph( std::vector<SocialPrefNode>& vertices );
    void set_graph( SocialPrefNode node, std::vector<int>::size_type index );
    // void set_graph( SocialPrefNode node ); - REMOVED -> double of .push_back()

    // Getters
    std::vector<SocialPrefNode> get_graph( ) const{ return nodes; }

    // Operators
    Graph& operator=( const Graph& copy );
	Graph& operator=( Graph&& copy ) noexcept;

    SocialPrefNode& operator[ ]( const std::vector<int>::size_type index );

    // Helpers
    void initialize( Profile profile );
    void make_graph( Preferencematrix& matrix, SCT::Procedure& rule ); // ALWAYS make a graph with a profile resulting from a procedure
    void push_back( SocialPrefNode& node ){ nodes.push_back( node ); }
    void clear( ){ nodes.clear( ); }

    std::vector<int>::size_type size( ) const{ return nodes.size( ); }

    std::vector<SocialPrefNode, std::allocator<SocialPrefNode>>::iterator begin( ){ return nodes.begin( ); }
    std::vector<SocialPrefNode, std::allocator<SocialPrefNode>>::iterator end( ){ return nodes.end( ); } // TODO: return one-beyond-last-element - This already does that

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

void initialize_single_source( Graph& graph, SocialPrefNode& source );

void relax( SocialPrefNode& leftnode, SocialPrefNode& rightnode, double weight );

bool bellman_ford( Graph& graph, double weight, SocialPrefNode& initial );

void dijkstra( Graph& graph, int weight, SocialPrefNode& initial );

// Implement Min-Heapify( p.112 ) and Extract-Min( p. 119 ). After, do Dijkstra( p.479 )

#endif // SCTGRAPH_H
