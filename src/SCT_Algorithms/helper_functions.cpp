#include "Classes/helper_functions.h"


/* Possible optimizations: binary search in rank_generation. Harder, better, faster, stronger.
 *						   order agent's orderings according to alternatives' values - enables
 *						   binary search
 */

/* Initialization Functions */

void Helper_functions::initialize_graph( std::vector<Agent>& listofagents, std::vector<SocialPrefNode>& graph ){

	int castsize = static_cast<int>( listofagents.size( ) );

	int randagt =  rand( ) % castsize;

	std::vector<int>::size_type index = static_cast<std::vector<int>::size_type>( randagt );

	std::vector<SocialPrefNode> copy( listofagents[ index ].get_preferences( ).size( ) );

	graph = copy;

	// Initializes nodes' ids. Take as argument the ids from an agent
	for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i )

		graph[ i ].set_id( listofagents[ index ].get_preferences( )[ i ].get_opt( ) );
}

void Helper_functions::initialize_opts( std::vector<Agent>& listofagents, std::vector<Options>& opts ){

    std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );

    if( !listofagents[ randagt ].get_preferences( ).empty( ) )

        opts = listofagents[ randagt ].get_preferences( );

    else{

        std::cerr << "Agent " << listofagents[ randagt ].get_id( ) << " has no preferences.\n";
    }
}

/* Printing Functions */

void Helper_functions::print_graph( std::vector<SocialPrefNode>& graph ){

    for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

        std::cout << graph[ i ];
    }
}

/* Data Structures Modifying Functions */

void Helper_functions::strong_connect( SocialPrefNode& v, std::vector<SocialPrefNode>& s, int& index ){

	v.set_index( index );
	v.set_lowlink( index );

	++index;

	s.push_back( v );

	v.set_onstack( true );

	for( SocialPrefNode* w : v.get_preferences( ) ){

		if( w -> get_index( ) == -1 ){

			strong_connect( *w, s, index );

			v.set_lowlink( std::min( v.get_lowlink( ), w -> get_lowlink( ) ) );
		}

		else if( w -> get_onstack( ) == true ){

			v.set_lowlink( std::min( v.get_lowlink( ), w -> get_lowlink( ) ) );
		}
	}

	if( v.get_lowlink( ) == v.get_index( ) ){

		for( SocialPrefNode w : s ){

			//shit happening here
            do{

                std::cout << "Error line 0.\n\n";

                // HERE
				w = s[ s.size( ) - 1 ];

                std::cout << "Error line 1.\n\n";

                s.pop_back( );

                std::cout << "Error line 2.\n\n";

				w.set_onstack( false );

                std::cout << "Error line 3.\n\n";
            }

            while( w.get_id( ) != v.get_id( ) && !s.empty( ) );
		}
	}
}

std::vector<SocialPrefNode> Helper_functions::tarjan( std::vector<SocialPrefNode>& graph ){

	int index = 0;

	std::vector<SocialPrefNode> s{ };

	for( SocialPrefNode v : graph ){

		if( v.get_index( ) == -1 ){

			strong_connect( v, s, index );
		}
	}

    if( !s.empty( ) )

        return s;

    else{

        s.push_back( SocialPrefNode( "Null", 0, 0, false, { }, { }, { } ) );

        return s;
    }
}

// Checkes for cycles in graph GRAPH - Isso aqui tá claramente dando boxta
std::vector<Cycle> Helper_functions::check_cycle( std::vector<SocialPrefNode>& graph ){

    // Start by following the path of a given node
    // stores each node of path in a vector
    // when a repeated node appers
        // flush the vector, but hold the existing node
        // do something etc i do not know

    std::vector<Cycle> paths( graph.size( ) );

    for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

        paths[ i ].set_id( graph[ i ].get_id( ) );
    }

    for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

        for( std::vector<int>::size_type j = 0; j < paths.size( ) ; ++j ){

            if( graph[ i ].get_id( ) == paths[ j ].get_id( )  ){

                for( std::vector<int>::size_type k = 0; k < graph[ i ].get_preferences( ).size( ); ++k ){

                    paths[ j ].set_path( graph[ i ].get_preferences( )[ k ] -> get_id( ) );
                }
            }
        }
    }

    // Tarjan algorithm - DFS
        // Get a random node in path, add it to path
            // Get a random value from preferences, add it to path
                // Do this until a repeated node is reached


	int index = 0;

    std::vector<char> way{ };

    return paths;
}

// Makes a social order from a Pairwise Rank of alternatives
std::vector<Options> Helper_functions::make_social_order( std::vector<Agent>& listofagt, std::vector<PairWiseRank>& rank ){

    std::vector<Options> orderedrank{ };

    initialize_opts( listofagt, orderedrank );

    // Check for emptyness - I really should make a exception class to handle this
    if( !orderedrank.empty( ) )

        // get every available option
        for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

            // get their respective scores, i.e., how many options they beat
            for( std::vector<int>::size_type j = 0; j < orderedrank.size( ); ++j ){

                if( rank[ i ].get_optx( ).get_opt( ) == orderedrank[ j ].get_opt( ) ){

                    if( rank[ i ].get_xval( ) > rank[ i ].get_yval( ) )

                        orderedrank[ j ].set_value( orderedrank[ j ].get_value( ) + 1 );
                }

                else if( rank[ i ].get_opty( ).get_opt( ) == orderedrank[ j ].get_opt( ) ){

                    if( rank[ i ].get_xval( ) < rank[ i ].get_yval( ) )

                        orderedrank[ j ].set_value( orderedrank[ j ].get_value( ) + 1 );
                }
            }
        }

    auto comparison = [ ]( Options& left, Options& right ){ return left.get_value( ) > right.get_value( ); };

    // order vector from greatest to smallest, according to the value
    std::sort( orderedrank.begin( ), orderedrank.end( ), comparison );

    return orderedrank;
}

// Makes a social order from a Social Graph of alternatives
std::vector<Options> Helper_functions::make_social_order( std::vector<SocialPrefNode>& socialgraph ){

    std::vector<Options> orderedrank{ };

    for( std::vector<int>::size_type i = 0; i < socialgraph.size( ); ++i ){

        std::vector<Options>::iterator aux{ };

        aux = orderedrank.begin( );

        int value = static_cast<int>( socialgraph[ i ].get_preferences( ).size( ) );

        for( std::vector<int>::size_type j = 0; j < orderedrank.size( ) && value <= orderedrank[ j ].get_value( ); ++j ){

            aux++;
        }

        Options holder( socialgraph[ i ].get_id( ), static_cast<int>( socialgraph[ i ].get_preferences( ).size( ) + 1 ) );

        orderedrank.insert( aux, holder );
    }

    return orderedrank;
}

// Generates, without repetition, all combinations of pairs of alternatives
std::vector<PairsOfOpts> Helper_functions::pair_generation( std::vector<Agent>& listofagents ){

    PairsOfOpts compairs;

    std::vector<PairsOfOpts> paircomp{ };

    std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );

    // gets all possible combination of pairs, including repeated pairs
    for( std::vector<int>::size_type i = 0; i < listofagents[ randagt ].get_preferences( ).size( ); ++i ){

        compairs.xpref = listofagents[ randagt ].get_preferences( )[ i ];

        for( std::vector<int>::size_type j = i + 1; j < listofagents[ randagt ].get_preferences( ).size( ); ++j ){

            if( j != i ){

                compairs.ypref = listofagents[ randagt ].get_preferences( )[ j ];

                paircomp.push_back( compairs );
            }
        }
    }

    // returns all combinations without repetitions
    return paircomp;
}

/* Ranks alternatives. The ranking has a form of a vector of quintuples ( x, y, xval, yval, ival ), where
 * x and y are the alternatives, and the vals represent how many agents prefer one over the other. ival
 * represents indifference. The ranking operates in accord to how agents ranks pairs of alternatives */
std::vector<PairWiseRank> Helper_functions::rank_generation( std::vector<Agent>& listofagents ){

    // Holder for a pair of options
    PairsOfOpts compairs{ };

    std::vector<PairsOfOpts> ordering = pair_generation( listofagents );

    // quintuples ( x, y, xval, yval, ival ) and then map occurrences into val
    PairWiseRank paircomp{ };

    std::vector<PairWiseRank> ranking{ };

    // Checks how a pair ( x, y ) is ranked for each agent
    for( std::vector<int>::size_type i = 0; i < ordering.size( ); ++i ){

        // Holds both alternatives that will be checked
        compairs.xpref = ordering[ i ].xpref;
        compairs.ypref = ordering[ i ].ypref;

        for( std::vector<int>::size_type j = 0; j < listofagents.size( ); ++j ){

            for( std::vector<int>::size_type k = 0; k < listofagents[ j ].get_preferences( ).size( ); ++ k ){

                // Search for x in agent's preferences
				if( listofagents[ j ].get_preferences( )[ k ].get_opt( ) == compairs.xpref.get_opt( ) ){

                    paircomp.set_optx( listofagents[ j ].get_preferences( )[ k ] );

				}

                // Search for y in agent's preferences
                if( listofagents[ j ].get_preferences( )[ k ].get_opt( ) == compairs.ypref.get_opt( ) )

                    paircomp.set_opty( listofagents[ j ].get_preferences( )[ k ] );
            }

            // Compares x and y values. If x > y, increment xval
            if( paircomp.get_optx( ).get_value( ) > paircomp.get_opty( ).get_value( ) )

                paircomp.incrementx( );

            // Else, if x < y, increment yval
            else if( paircomp.get_optx( ).get_value( ) < paircomp.get_opty( ).get_value( ) )

                paircomp.incrementy( );

            // Else, if x == y, increment ival
            else if( paircomp.get_optx( ).get_value( ) == paircomp.get_opty( ).get_value( ) )

                paircomp.incrementi( );
        }

        // Stores the ranked tuple
        ranking.push_back( paircomp );

        // Resets the tuple for a new ranking
        paircomp = { };
	}


    // returns a vector of quintuples
    return ranking;
}

/* Creates a graph GRAPH composed by nodes of alternatives. Relates those nodes according to how the alt-
 * ernatives are related to each other, i.e., for three alternatives x, y, and z, if x > y, then, one has
 * that y is in x.preferred, and x is in y.worsethan. If x == z, then x is in z.indifference and z is in
 * x.indifference */
void Helper_functions::make_graph( std::vector<Agent>& listofagents, std::vector<PairWiseRank>& rank, std::vector<SocialPrefNode>& graph ){

	if( graph.empty( ) ){

        std::cout << "Graph has no nodes! Initializing it.\n\n";

		initialize_graph( listofagents, graph );
	}

	int randagt = rand( ) % listofagents.size( );
	//int randindx = rand( ) % listofagents[ randagt ].get_preferences( ).size( );

	// Initializes nodes' ids. Take as argument the ids from an agent
	for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

		graph[ i ].set_id( listofagents[ randagt ].get_preferences( )[ i ].get_opt() );
	}
	// Checks how alternatives are related. Links them accordingly to their relation
	for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

		for( std::vector<int>::size_type j = 0; j < graph.size( ); ++j ){


			// if x > y
			if( rank[ i ].get_xval( ) > rank[ i ].get_yval( ) ){

				// If graph[ j ] == x, set preferredto = y, i.e., x is preferred to y
				if( graph[ j ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) ){

					for( std::vector<int>::size_type k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) )

							graph[ j ].set_pref( graph[ k ] );
					}
				}

				// Else if graph[ j ] == y, set worse = x, i.e., y is worse than x
				else if( graph[ j ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) ){

					for( std::vector<int>::size_type k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) )

							graph[ j ].set_worse( graph[ k ] );
					}
				}
			}

			// if x < y
			else if( rank[ i ].get_xval( ) < rank[ i ].get_yval( ) ){

				// If graph[ j ] == x, set worsethan = y
				if( graph[ j ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) ){

					for( std::vector<int>::size_type k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) )

							graph[ j ].set_worse( graph[ k ] );
					}
				}

			// Else if scgraph[ j ] == y, set preferences = y
			else if( graph[ j ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) ){

				for( std::vector<int>::size_type k = 0; k < graph.size( ); ++k ){

					if( graph[ k ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) )

						graph[ j ].set_pref( graph[ k ] );
				}
			}
		}

			// if x == y
			else if( rank[ i ].get_xval( ) == rank[ i ].get_yval( ) ){

				// If scgraph[ j ] == x, set indiff = y
				if( graph[ j ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) ){

					for( std::vector<int>::size_type k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) ){

							graph[ k ].set_indiff( graph[ j ] );
						}
					}
				}

				// Else if scgraph[ j ] == y, set indiff = x
				else if( graph[ j ].get_id( ) == rank[ i ].get_opty( ).get_opt( ) ){

					for( std::vector<int>::size_type k = 0; k < graph.size( ); ++k ){

						if( graph[ k ].get_id( ) == rank[ i ].get_optx( ).get_opt( ) ){

							graph[ k ].set_indiff( graph[ j ] );
						}
					}
				}
			}
		}
	}

}

// Hamiltonian Paths for each node in GRAPH
Cycle Helper_functions::make_paths( std::vector<SocialPrefNode> graph ){ // returns a vector of cycles

    Cycle pathway{ };

    while( graph.size( ) != 0 ){

        auto comparison = [ ]( SocialPrefNode& left, SocialPrefNode& right ){

            return left.get_preferences( ).size( ) < right.get_preferences( ).size( );
        };

        auto max = std::max_element( graph.begin( ), graph.end( ), comparison );

        pathway.set_path( max -> get_id( ) );

        // Remove max from graph to get a new, and different, max value
        for( std::vector<int>::size_type j = 0; j < graph.size( ); ++j ){

            if( max -> get_id( ) == graph[ j ].get_id( ) ){

                graph.erase( graph.begin( ) + static_cast<int>( j ) );
            }
        }
    }
    // Get hamiltonian path
    return pathway;
}


