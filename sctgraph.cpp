#include "sctgraph.hpp"

/// Constructors & Destructor

// Default constructor
Graph::Graph( ){ nodes = { }; }

// Alternative parameterized constructor. Inserts a node at the
// end of NODES
Graph::Graph( SocialPrefNode node ){ nodes.push_back( node ); }

// Copy constructor
Graph::Graph( const Graph& vertices ){ nodes = vertices.nodes; }

// Move constructor
Graph::Graph( Graph&& copy ){

	nodes = std::move( copy.nodes );

	copy.clear( );
}

// Initializer constructor
Graph::Graph( Rank& rank ){ make_graph( rank ); }

// Destructor. Clears NODES from memory
Graph::~Graph( ){

    clear( );

    std::vector<SocialPrefNode>( ).swap( nodes );
}

/// Setters

// Sets Graph's nodes to parameter vertices
void Graph::set_graph( std::vector<SocialPrefNode> vertices ){ nodes = vertices; }

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

// Pushes back node into nodes
void Graph::set_graph( SocialPrefNode node ){ nodes.push_back( node ); }

/// Getters

/// Operators

// Overloaded copy constructor
Graph& Graph::operator=( const Graph& copy ){

	nodes = copy.nodes;

    return *this;
}

// Overloaded move assignment
Graph& Graph::operator=( Graph&& copy ){

	nodes = std::move( copy.nodes );

	copy.clear( );

	return *this;
}

// Overloaded subscript operator. Returns a SocialPrefNode at index position
SocialPrefNode& Graph::operator[ ]( const std::vector<int>::size_type index ){ return nodes[ index ]; }

/// Helpers

// Initializes a graph according to the options in an random agent's profile
void Graph::initialize_graph( Population& population ){

    /*std::random_device rd;

    //std::mt19937_64 mt( rd( ) );
    std::mt19937 mt( rd( ) );

    std::uniform_int_distribution<std::vector<int>::size_type> randagt( 0, ( population.size( ) - 1 ) );

    //std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % population.size( );

    for( std::vector<int>::size_type i = 0; i < population[ randagt( mt ) ].get_preferences( ).size( ); ++i ){

        nodes.push_back( SocialPrefNode( population[ randagt( mt ) ][ i ].get_opt( ), { }, { }, { }, { }, { }, { } ) );
    }*/

    if( !population.empty( ) ){

        if( !nodes.begin( ) -> get_preferences( ).empty( ) ){

            nodes.resize( population.begin( ) -> get_preferences( ).size( ) );
        }
    }

    for( std::vector<int>::size_type i = 0; i < nodes.size( ); ++i ){

        nodes[ i ].set_id( population.begin( ) -> get_preferences( )[ i ].get_opt( ) );
    }
}

// Initializes a graph according to a random profile in a PreferenceMatrix
void Graph::initialize_graph( Preferencematrix& mtx ){

    if( !mtx.empty( ) )

        nodes.resize( mtx.get_matrix( ).begin( ) -> size( ) );

    // Initializes nodes' ids. Take as argument the ids from an agent's preferences
    for( std::vector<int>::size_type i = 0; i < mtx.get_matrix( ).begin( ) -> size( ); ++i )

        nodes[ i ].set_id( mtx.get_matrix( ).begin( ) -> begin( )[ static_cast<int>( i ) ].get_opt( ) );
}

// Creates a graph according to the result of an aggregation procedure. Profile passed
// as argument must be the result of an aggregation
void Graph::make_graph( Profile& profile ){

    // Create an exception for this condition
    if( nodes.empty( ) ){

        std::cerr << "\n\nGraph has no nodes!\n\n";
    }

    else{

        for( std::vector<int>::size_type i = 0; i < nodes.size( ); ++i ){

            for( std::vector<int>::size_type j = 0; j < nodes.size( ); ++j ){

                if( i != j ){

                    std::vector<Options>::iterator left = std::find( profile.begin( ), profile.end( ), Options( nodes[ i ].get_id( ) ) );
                    std::vector<Options>::iterator right = std::find( profile.begin( ), profile.end( ), Options( nodes[ j ].get_id( ) ) );

                    if( left -> get_value( ) > right -> get_value( ) ){

                        nodes[ i ].set_pref( nodes[ j ] );
                    }

                    else if( left -> get_value( ) < right -> get_value( ) ){

                        nodes[ i ].set_worse( nodes[ j ] );
                    }

                    else if( left -> get_value( ) == right -> get_value( ) ){

                        nodes[ i ].set_indiff( nodes[ j ] );
                    }
                }

                else{

                    continue;
                }
            }
        }
    }
}

/* Creates a graph GRAPH composed by nodes of alternatives. Relates those nodes according to how the alt-
 * ernatives are related to each other, i.e., for three alternatives x, y, and z, if x > y, then, one has
 * that y is in x.preferred, and x is in y.worsethan. If x == z, then x is in z.indifference and z is in
 * x.indifference */
// Update this. Use the other overload as example
void Graph::make_graph( Rank& rank ){

    // Checks if the vector NODES is not empty
    // Create an exception for this condition
    if( nodes.empty( ) ){

        std::cerr << "\n\nGraph has no nodes!\n\n";
    }

    else{

        // Checks how alternatives are related. Links them accordingly to their relation
        for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

            for( std::vector<int>::size_type j = 0; j < nodes.size( ); ++j ){

                // if x > y
                if( rank[ i ].get_xval( ) > rank[ i ].get_yval( ) ){

                    // If graph[ j ] == x, set preferredto = y, i.e., x is preferred to y
                    if( nodes[ j ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) ){

                        for( std::vector<int>::size_type k = 0; k < nodes.size( ); ++k ){

                            if( nodes[ k ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) )

                                nodes[ j ].set_pref( nodes[ k ] );
                        }
                    }

                    // Else if nodes[ j ] == y, set worse = x, i.e., y is worse than x
                    else if( nodes[ j ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) ){

                        for( std::vector<int>::size_type k = 0; k < nodes.size( ); ++k ){

                            if( nodes[ k ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) )

                                nodes[ j ].set_worse( nodes[ k ] );
                        }
                    }
                }

                // if x < y
                else if( rank[ i ].get_xval( ) < rank[ i ].get_yval( ) ){

                    // If nodes[ j ] == x, set worsethan = y
                    if( nodes[ j ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) ){

                        for( std::vector<int>::size_type k = 0; k < nodes.size( ); ++k ){

                            if( nodes[ k ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) )

                                nodes[ j ].set_worse( nodes[ k ] );
                        }
                    }

                    // Else if graph[ j ] == y, set preferences = y
                    else if( nodes[ j ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) ){

                        for( std::vector<int>::size_type k = 0; k < nodes.size( ); ++k ){

                            if( nodes[ k ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) )

                                nodes[ j ].set_pref( nodes[ k ] );
                        }
                    }
                }

                // if x == y
                else if( rank[ i ].get_xval( ) == rank[ i ].get_yval( ) ){

                    // If graph[ j ] == x, set indiff = y
                    if( nodes[ j ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) ){

                        for( std::vector<int>::size_type k = 0; k < nodes.size( ); ++k ){

                            if( nodes[ k ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) ){

                                nodes[ k ].set_indiff( nodes[ j ] );
                            }
                        }
                    }

                    // Else if graph[ j ] == y, set indiff = x
                    else if( nodes[ j ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) ){

                        for( std::vector<int>::size_type k = 0; k < nodes.size( ); ++k ){

                            if( nodes[ k ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) ){

                                nodes[ k ].set_indiff( nodes[ j ] );
                            }
                        }
                    }
                }
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