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
// the relation between x and z or y and z in the social ranking
bool irrelevant_alternatives( Preferencematrix& mtx, std::vector<Agent>& people, std::vector<SocialPrefNode>& graph ){

    // generate a second profile R' of preferences
    Preferencematrix primeMtx( mtx.get_rowsz( ), mtx.get_columnsz( ) );

    std::vector<Agent> population( primeMtx.get_matrix( ).size( ) );

    initialize_agents( population, primeMtx );

    // To optmize: search for the way to falsify the axiom -> check for the case where
    // the condition is true, but the consequence is false

    // Sort agents preferences according to value, will make things here easier
    for( std::vector<int>::size_type i = 0; i < people.size( ) && population.size( ); ++i ){

        people[ i ].sort_preferences( );
        population[ i ].sort_preferences( );
    }

    // if it is the case that, for any two alternatives x and y, and for every person i
    // xRiy iff xR'iy
    for( std::vector<int>::size_type i = 0; i < people.size( ); ++i ){

        for( std::vector<int>::size_type j = 0; j < population.size( ); ++j ){

            if( people[ i ].get_preferences( ) != population[ j ].get_preferences( ) ){

                return true;
            }

            else

                continue;
        }
    }

    std::vector<PairWiseRank> rank{ rank_generation( people ) };
    std::vector<PairWiseRank> primerank{ rank_generation( population ) };

    // then, generate a social order for each profile and check if x and y are ranked equally in both profiles
    if( make_social_order( people, rank ) == make_social_order( population, rank ) )

        // If that is the case, the axiom is not being violated, return true
        return true;

    // Else, the axiom is being violated, return false
    else

        return false;
}

// Searches for a dictator
// Find an agent that, whenever ONLY HER prefers x to y, the social order becomes xPy
// If is that the case that another person also prefers x to y, then the clause is not
// valid
bool non_dictatorship( std::vector<Agent>& people, std::vector<PairWiseRank>& rank, std::vector<SocialPrefNode>& graph ){

    for( std::vector<int>::size_type i = 0; i < people.size( ); ++i )

        people[ i ].sort_preferences( );

    //const std::vector<int>::size_type numofalts = people[ static_cast<std::vector<int>::size_type>( rand( ) ) % people.size( ) ].get_preferences( ).size( );

    std::vector<Options> dictatedopts{ };

    std::vector<Agent> dictators{ };

    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

        // if only one person prefers x to y
        if( rank[ i ].get_xval( ) == 1 ){

            dictatedopts.push_back( rank[ i ].get_optx( ) );
        }

        else if( rank[ i ].get_yval( ) == 1 ){

            dictatedopts.push_back( rank[ i ].get_optx( ) );
        }
    }

    if( !dictatedopts.empty( ) ){

        for( Options opt : dictatedopts ){

            for( std::vector<int>::size_type i = 0; i < people.size( ); ++i ){

                for( std::vector<int>::size_type j = 0; j < people[ i ].get_preferences( ).size( ); ++j ){

                    for( std::vector<int>::size_type k = 0; k < people[ i ].get_preferences( ).size( ) && k != j; ++k ){

                        if( opt.get_opt( ) == people[ i ][ j ].get_opt( ) ){

                            if( people[ i ][ j ].get_value( ) > people[ i ][ k ].get_value( ) ){

                                dictators.push_back( people[ i ] );
                            }

                            else if( people[ i ][ j ].get_value( ) < people[ i ][ k ].get_value( )  ){

                                dictators.push_back( people[ i ] );
                            }
                        }
                    }
                }
            }
        }
    }

    if( dictators.size( ) > 1 ){

        std::cout << "There is more than one dictator. Axiom not violated, return true.\n";

        return true;
    }

    else if( dictators.size( ) == 1 ){

        std::cout << "There is a dictator: " << dictators.begin( ).base( ) -> get_id( ) << ". Axiom violated, return false.\n";

        return false;
    }

    else if( dictators.empty( ) ){

        std::cout << "There are not dictators. Axiom not violated, return true.\n";

        return true;
    }
        // If it is the case that, for one agent i, only i have xPiy
            // Check the social order
                // If it is the case that xPy in the social order
                    // Return false and the agent i is a dictator
                // Else, return true
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

// If not true: analyze the profiles of preferences, both individual and social, then search for some kind of structure,
// i.e., single peakedness degree, individual impact on social profile, etc.
// If true, search for single peakedness or known structures/feats that causes the truthness
bool arrow_impossibility( std::vector<Agent>& listofagents, Preferencematrix& mtx ,std::vector<PairWiseRank>& rank, std::vector<SocialPrefNode>& graph ){

    // Checks if all the below conditions are satisfied simultaneously
		// Universal/Unrestricted Domain - granted by the definition of PreferenceMatrix

    // If it is the case that every conditions is satisfied, then, check the structure of the preferences for single-
    // peakedness or anything that might have made it possible for the result to hold

    // Else, check which axiom was violated, along with the alternative or individual that made the violation possible

    if( pareto_principle( graph, rank ) && irrelevant_alternatives( mtx, listofagents, graph ) && non_dictatorship( listofagents, rank, graph ) ){

        std::cout << "Arrow fully satisfied, no axiom violated. YASSSSS!.\n";

        return true;
    }

    else{

        std::cout << "SHITE.\n";

        return false;
    }
}
