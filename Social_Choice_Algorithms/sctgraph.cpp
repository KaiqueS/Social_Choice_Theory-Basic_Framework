#include "sctgraph.hpp"

/// Constructors & Destructor

// Default constructor
Graph::Graph( ){ nodes = { }; }

// Alternative parameterized constructor. Inserts a node at the
// end of NODES
Graph::Graph( SocialPrefNode node ){ nodes.push_back( node ); }

// Copy constructor
Graph::Graph( const Graph& vertices ){ nodes = vertices.nodes; }

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

// Overloaded subscript operator. Returns a SocialPrefNode at index position
SocialPrefNode& Graph::operator[ ]( const std::vector<int>::size_type index ){ return nodes[ index ]; }

/// Helpers

// Initializes a graph according to the options in an random agent's profile
void Graph::initialize_graph( Population& population ){

    std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % population.size( );

    for( std::vector<int>::size_type i = 0; i < population[ randagt ].get_preferences( ).size( ); ++i ){

        nodes.push_back( SocialPrefNode( population[ randagt ][ i ].get_opt( ), { }, { }, { }, { }, { }, { } ) );
    }
}

// Initializes a graph according to a random profile in a PreferenceMatrix
void Graph::initialize_graph( Preferencematrix& mtx ){

    if( !mtx.get_matrix( ).empty( ) )

        nodes.resize( mtx.get_matrix( ).begin( ) -> size( ) );

    // Initializes nodes' ids. Take as argument the ids from an agent's preferences
    for( std::vector<int>::size_type i = 0; i < mtx.get_matrix( ).begin( ) -> size( ); ++i )

        nodes[ i ].set_id( mtx.get_matrix( ).begin( ) -> begin( )[ static_cast<int>( i ) ].get_opt( ) );
}

/* Creates a graph GRAPH composed by nodes of alternatives. Relates those nodes according to how the alt-
 * ernatives are related to each other, i.e., for three alternatives x, y, and z, if x > y, then, one has
 * that y is in x.preferred, and x is in y.worsethan. If x == z, then x is in z.indifference and z is in
 * x.indifference */
void Graph::make_graph( Preferencematrix& mtx, Rank& rank ){

    // Checks if the vector NODES is not empty
    if( nodes.empty( ) ){

        std::cout << "Graph has no nodes! Initializing it.\n\n";

        initialize_graph( mtx );
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

    for( std::vector<int>::size_type i = 0; i < graph.get_graph( ).size( ); ++i )

        os << "[ " << graph[ i ].get_id( ) << " ]" << " ";

    return os;
}

// Prints graph
void print_graph( Graph& graph ){

    for( std::vector<int>::size_type i = 0; i < graph.get_graph( ).size( ); ++i )

        std::cout << graph[ i ];
}
