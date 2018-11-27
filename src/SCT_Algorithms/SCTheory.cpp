#include "helper_functions.cpp"
#include "aggregation_rules.cpp"

// Checks if the pareto principle is violated or not - Working(?) - TODO: Check for transitivity problems
bool pareto_principle( std::vector<SocialPrefNode>& graph ,std::vector<PairWiseRank>& rank ){

    // Ordered social rank. Decreasing order
    std::vector<Options> socialorder = make_social_order( graph );

    bool validity{ true };

    // check how every pair x, y of alternatives are ranked for every profile i
    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

        // if x > y, for every profile i: TODO -> WRONG - check for TOTAL number of votes
        if( rank[ i ].get_xval( ) == static_cast<int>( graph.size( ) ) ){

            // check every element in an decreasing ordered social order
            for( std::vector<int>::size_type j = 0; j < socialorder.size( ); ++j ){

                // if x == an element of the social order
                if( rank[ i ].get_optx( ).get_opt( ) == socialorder[ j ].get_opt( ) ){

                    // if, for every profile i, it is true that x is unanimously preferred
                    if( rank[ i ].get_xval( ) == ( static_cast<int>( socialorder.size( ) ) ) ){

                        // compare x against every alternative k in social order
                        for( std::vector<int>::size_type k = 0; k < socialorder.size( ); ++k ){

                            // prevents comparing x with itself
                            if( j != k ){

                                // checks if x beats every alternative k in social order
                                if( socialorder[ j ].get_value( ) > socialorder[ k ].get_value( ) ){

                                    // if social order[ k ] is the last element of social order
                                    // return true
                                    validity = true;
                                }

                                else

                                    return false;
                            }
                        }
                    }
                }
            }
        }

        else if( rank[ i ].get_yval( ) == static_cast<int>( graph.size( ) ) ){

            for( std::vector<int>::size_type j = 0; j < socialorder.size( ); ++j ){

                if( rank[ i ].get_opty( ).get_opt( ) == socialorder[ j ].get_opt( ) ){

                    if( rank[ i ].get_yval( ) == ( static_cast<int>( socialorder.size( ) ) ) ){

                        for( std::vector<int>::size_type k = 0; k < socialorder.size( ); ++k ){

                            if( j != k ){

                                // Problem here: this return true for the first pair of values that
                                // satisfies the condition. The problem is, this should returb true
                                // only it is guaranteed that j beats EVERY OTHER ALTERNATIVES k in
                                // socialorder.
                                if( socialorder[ j ].get_value( ) > socialorder[ k ].get_value( )  ){

                                    validity = true;
                                }

                                else

                                    return false;
                            }
                        }
                    }
                }
            }
        }
    }

    return validity;
}

// Checks if , for any x, y, and z, the relation between x and y is modified by
// the relation between x and z in the social ranking
bool irrelevant_alternatives( std::vector<Agent> people, std::vector<SocialPrefNode>& graph ){

    // generate a second profile R' of preferences
    // if it is the case that, for any two alternatives x and y, and for every person i
    // xRiy iff xR'iy
        // then, generate a social order for each profile and check if x and y are ranked
        // in the same way with respect to each other

    return true;
}

// Searches for a dictator
bool non_dictatorship( std::vector<Agent> people, std::vector<SocialPrefNode>& graph ){

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

void arrow_impossibility( std::vector<Agent>& listofagents, std::vector<PairWiseRank>& rank, std::vector<SocialPrefNode>& graph ){

    // Checks if all the below conditions are satisfied simultaneously
        // Universal/Unrestricted Domain - granted by the definition of PreferenceMatrix

        // Pareto Principle
        pareto_principle( graph, rank );

        // Independence of Irrelevant Alternatives
        irrelevant_alternatives( listofagents, graph );

        // Non-dictatorship
        non_dictatorship( listofagents, graph );
}
