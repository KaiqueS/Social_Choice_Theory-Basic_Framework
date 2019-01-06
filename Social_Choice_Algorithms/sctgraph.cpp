#include "sctgraph.hpp"

/// Constructors & Destructor

// Default constructor
Graph::Graph( ){

    nodes = { };
}

// Parameterized constructor
Graph::Graph( std::vector<SocialPrefNode> vertices ){

    nodes = vertices;
}

// Copy constructor
Graph::Graph( const Graph& vertices ){

    nodes = vertices.nodes;
}

/// Setters

// Sets Graph's nodes to parameter vertices
void Graph::set_graph( std::vector<SocialPrefNode> vertices ){ nodes = vertices; }

// Sets a Graph's node to parameter node into position graph[ index ]
void Graph::set_graph( SocialPrefNode node, std::vector<int>::size_type index ){

    if( index >= nodes.size( ) ){

        std::cout << "Invalid index. Please, set a value between 0 and " << nodes.size( ) -1 << ".\n";

        std::cin >> index;

        set_graph( node, index );
    }

    else if( static_cast<int>( index ) < 0 ){

        std::cout << "Invalid index. Value smaller than 0. Please set a value between 0 and " << nodes.size( ) -1 << ".\n";

        std::cin >> index;

        set_graph( node, index );
    }

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

// Overloaded subscript operator
SocialPrefNode& Graph::operator[ ]( const std::vector<int>::size_type index ){ return nodes[ index ]; }

// Overloaded printing operator
std::ostream& operator<<( std::ostream& os, Graph& graph ){

    for( std::vector<int>::size_type i = 0; i < graph.get_graph( ).size( ); ++i )

        os << "[ " << graph[ i ].get_id( ) << " ]" << " ";

    return os;
}

/// Helpers

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

void print_graph( Graph& graph ){

    for( std::vector<int>::size_type i = 0; i < graph.get_graph( ).size( ); ++i )

        std::cout << graph[ i ];
}
