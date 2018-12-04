#include "helper_functions.cpp"
#include "aggregation_rules.cpp"

// Checks if the pareto principle is violated or not - Working(?) - TODO: Check for transitivity problems
// TODO: overload pareto principle so that it only deals with graph or rank, but not both
bool pareto_principle( std::vector<SocialPrefNode>& graph ,std::vector<PairWiseRank>& rank ){

    // Ordered social rank. Decreasing order
    std::vector<Options> socialorder = make_social_order( graph );

    Options pareto{ };

    bool validity{ true };

    // Reads PairWiseRank. Since it considers how each pair is being ranked on every individual
    // profile of preferences WITHOUT being a social order, one can proceed as follows:
    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

        // Get an option in rank
        // TODO: implement something to make it possible for optx or opty to be selected randomly
        Options opt( rank[ i ].get_optx( ).get_opt( ), 0  );

        // Get every option in rank
        for( PairWiseRank pair : rank ){

            // Check if opt is equal to one of the alternatives in pair
            if( opt.get_opt( ) == pair.get_optx( ).get_opt( ) ){

                // If it is, then check if opt beats its adversary
                if( pair.get_xval( ) > pair.get_yval( ) ){

                    // If it beats, then increment the value of opt
                    ++opt;
                }
            }

            else if( opt.get_opt( ) == pair.get_opty( ).get_opt( ) ){

                if( pair.get_xval( ) < pair.get_yval( ) ){

                    ++opt;
                }
            }
        }

        // If it is the case that opt is UNANIMOUSLY select by the agents
        if( opt.get_value( ) == static_cast<int>( socialorder.size( ) ) - 1 ){

            // Make pareto = opt
            pareto = opt;
        }

        // PROBLEM HERE: Think about some way of using this else to report relevant message
        else{

            //pareto = Options( "NULL", -1 );

            continue;
        }
    }

    // Now, the second part: If there is a pareto option
    if( pareto.get_opt( ) != "NULL" ){

        // Get the first element of socialorder. Remember, this vector ir ordered from the most to
        // the least preferred alternative
        std::vector<Options, std::allocator<Options>>::iterator index = socialorder.begin( );

        // If it is the case that pareto equals the first element of socialorder
        if( pareto.get_opt( ) == index.base( ) -> get_opt( ) ){

            // Then the axiom is not being violated
            validity = true;
        }

        // Else, it is being violated
        else if( pareto.get_opt( ) != index.base( ) -> get_opt( ) ){

            validity = false;
        }
    }

    // Returns final validity
    return validity;
}

// Checks if , for any x, y, and z, the relation between x and y is modified by
// the relation between x and z in the social ranking
bool irrelevant_alternatives( Preferencematrix& mtx, std::vector<Agent>& people, std::vector<SocialPrefNode>& graph ){

    bool validity{ true };

    // generate a second profile R' of preferences
    Preferencematrix primeMtx( mtx.get_rowsz( ), mtx.get_columnsz( ) );

    std::vector<Agent> population( primeMtx.get_matrix( ).size( ) );

    initialize_agents( population, primeMtx );

    // if it is the case that, for any two alternatives x and y, and for every person i
    // xRiy iff xR'iy
        // then, generate a social order for each profile and check if x and y are ranked
        // in the same way with respect to each other
            // make_social_order( mtx )
            // make_social_order( primemtx )
            // check if both orderings are the same


    return validity;
}

// Searches for a dictator
bool non_dictatorship( std::vector<Agent>& people, std::vector<SocialPrefNode>& graph ){

    // if there is a dictator
        // return false, and the dictator

    // else
        // return true, the social ordering is ok

    return true;
}

void condorcet_paradox( std::vector<PairWiseRank>& rank, std::vector<SocialPrefNode>& graph ){

    Options winner = majority_rule( graph );

    // Check for cycles
    // std::vector<Cycle<Prefs>> paths = check_cycle( graph );
        // If there are no cycles, Use outdegree as a mean to determine if a node is the Condorcet winner
        // Else, use another method

    // for( int i = 0; i < paths.size( ); ++i ) std::cout << paths[ i ];

    std::cout << winner.get_opt( ) << " is the winner.\n";
}

void arrow_impossibility( std::vector<Agent>& listofagents, Preferencematrix& mtx ,std::vector<PairWiseRank>& rank, std::vector<SocialPrefNode>& graph ){

    // Checks if all the below conditions are satisfied simultaneously
		// Universal/Unrestricted Domain - granted by the definition of PreferenceMatrix

        // Pareto Principle
        pareto_principle( graph, rank );

        // Independence of Irrelevant Alternatives
        irrelevant_alternatives( mtx, listofagents, graph );

        // Non-dictatorship
        non_dictatorship( listofagents, graph );
}
