#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\sctgraph.hpp"

/// Constructors & Destructor

// Default constructor
Graph::Graph( ){ nodes = { }; }

// Copy constructor
Graph::Graph( const Graph& vertices ){ nodes = vertices.nodes; }

// Move constructor
Graph::Graph( Graph&& copy ) noexcept{

	nodes = std::move( copy.nodes );

	copy.clear( );
}

Graph::Graph( Profile& profile ){

    initialize( profile );

    //make_graph( profile );
}

// Destructor. Clears NODES from memory
Graph::~Graph( ){

    clear( );

    std::vector<SocialPrefNode>( ).swap( nodes );
}

/// Setters

// Sets Graph's nodes to parameter vertices
void Graph::set_graph( std::vector<SocialPrefNode>& vertices ){ nodes = vertices; }

// Sets a Graph's node to parameter node into position graph[ index ]
void Graph::set_graph( SocialPrefNode node, std::vector<int>::size_type index ){

    // Checks for indexes out of NODES range
    if( index >= nodes.size( ) ){

        std::cout << "Invalid index. Please, set a value between 0 and " << nodes.size( ) -1 << ".\n";

        std::cin >> index;

        // If it is the case the index is out of NODES' range, prompt
        // for another index
        set_graph( node, index );
    }

    // Checks for indexes out of NODES range
    else if( static_cast<int>( index ) < 0 ){

        std::cout << "Invalid index. Value smaller than 0. Please set a value between 0 and " << nodes.size( ) -1 << ".\n";

        std::cin >> index;

        set_graph( node, index );
    }

    // If index is in NODES' range, set NODES[ INDEX ] to node
    else

        nodes[ index  ] = node;
}

/// Getters

/// Operators

// Overloaded copy constructor
Graph& Graph::operator=( const Graph& copy ){

	nodes = copy.nodes;

    return *this;
}

// Overloaded move assignment
Graph& Graph::operator=( Graph&& copy ) noexcept{

	nodes = std::move( copy.nodes );

	copy.clear( );

	return *this;
}

// Overloaded subscript operator. Returns a SocialPrefNode at index position
SocialPrefNode& Graph::operator[ ]( const std::vector<int>::size_type index ){ return nodes[ index ]; }

/// Helpers

// Uses a profile to create the set of nodes in SCGraph, i.e., creates a set
// of nodes and initializes its id's to the profiles options id's
void Graph::initialize( Profile profile ){

    if( !profile.empty( ) ){

        nodes.resize( profile.size( ) );

        for( std::vector<int>::size_type i = 0; i < nodes.size( ); ++i ){

            nodes[ i ].set_id( profile[ i ].get_opt( ) );
        }
    }

    else{

        std::cerr << "Empty profile. Initialization not possible!\n";
    }
}

// I need to change this. If a > b, create an directed edge from a to b, instead of creating
// an edge just because a.value > b.value, which does not imply that a > b. Transitivity 
// problems will be evident from this with cycles.
void Graph::make_graph( Preferencematrix& matrix, SCT::Procedure& rule ){

    SCT::Decision_set set{ };
    set( matrix );

    Options first{ };
    Options second{ };

    // To create an edge from a to b, I need to know wheter aPb under an aggregation procedure.
    for( auto left = 0; left < nodes.size( ); ++left ){

        for( auto right = left + 1; right < nodes.size( ); ++right ){

            first.set_opt( nodes[ left ].get_id( ) );
            second.set_opt( nodes[ right ].get_id( ) );

            if( nodes[ left ].get_id( ) == rule( first, second, matrix ).get_opt( ) ){

                nodes[ left ].set_pref( nodes[ right ] );
                nodes[ right ].set_worse( nodes[ left ] );
            }

            else{

                nodes[ right ].set_pref( nodes[ left ] );
                nodes[ left ].set_worse( nodes[ right ] );
            }
        }
    }
}

// Checks if Graph is empty. Return true if it is.
bool Graph::empty( ){

    if( nodes.empty( ) )

        return true;

    else

        return false;
}

/// Non-member helpers

// Overloaded printing operator
std::ostream& operator<<( std::ostream& os, Graph& graph ){

    os << "Graph contains the following nodes:\n\n";

    for( std::vector<int>::size_type i = 0; i < graph.get_graph( ).size( ); ++i )

        os << "[ " << graph[ i ].get_id( ) << " ]" << " ";

    os << "\n\n";

    for( std::vector<int>::size_type i = 0; i < graph.get_graph( ).size( ); ++i ){

        os << graph[ i ] << "\n";
    }

    return os;
}

// Initializes a Graph. Used in Johnson's algorithm
void initialize_single_source( Graph& graph, SocialPrefNode& node ){

    for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

        if( graph[ i ] != node ){
         
            graph[ i ].set_distance( std::numeric_limits<int>::infinity( ) );
            graph[ i ].set_pi( NULL ); // hmmmmmmm
        }

        else{

            continue;
        }
    }

    node.set_distance( 0 );
}

// Attention here: it may be better if relax were a template function
// where the template argument Arg is a function w that gives the weight
// from leftnode to rightnode
void relax( SocialPrefNode& leftnode, SocialPrefNode& rightnode, double weight ){

    if( leftnode.get_distance( ) > ( rightnode.get_distance( ) + weight ) ){

        leftnode.set_distance( rightnode.get_distance( ) + weight );

        leftnode.set_pi( &rightnode );
    }
}

bool bellman_ford( Graph& graph, double weight, SocialPrefNode& initial ){

    initialize_single_source( graph, initial );

    for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

        // This is a adaptation. See Cormen p.474, ( u, v ) in E[ G ]
        for( int j = 0; j < graph[ i ].get_preferences( ).size( ); ++j ){

            // Pay attention to second argument here. The dereferenced argument
            relax( graph[ i ], *graph[ i ][ SocialPrefNode::preferences_index{ j } ], weight ); // FIX PROBLEM HERE
        }
    }

    for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

        // This is a adaptation. See Cormen p.474, ( u, v ) in E[ G ]
        for( int j = 0; j < graph[ i ].get_preferences( ).size( ); ++j ){

            if( graph[ i ].get_distance( ) > ( graph[ i ][ SocialPrefNode::preferences_index{ j } ] -> get_distance( ) + weight ) ){

                return false;
            }

            else{

                continue;
            }
        }
    }

    return true;
}

void dijkstra( Graph& graph, int weight, SocialPrefNode& initial ){


}