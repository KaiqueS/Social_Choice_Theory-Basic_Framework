#include "helper_functions.hpp"

/* Possible optimizations: binary search in rank_generation. Harder, better, faster, stronger.
 *						   order agent's orderings according to alternatives' values - enables
 *						   binary search
 */

/// Initialization Functions

// Generates, without repetition, all combinations of pairs of alternatives
std::vector<PairsOfOpts> pair_generation( Population& listofagents ){

    PairsOfOpts compairs{ };

    std::vector<PairsOfOpts> paircomp{ };

    std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );

    std::vector<int>::size_type listsize = listofagents.size( );
    std::vector<int>::size_type prefsize = listofagents[ static_cast<std::vector<int>::size_type>( rand( ) ) % listsize ].get_preferences( ).size( );

    // gets all possible combination of pairs, including repeated pairs
    for( std::vector<int>::size_type i = 0; i < prefsize; ++i ){

        compairs.xpref = listofagents[ randagt ][ i ];

        for( std::vector<int>::size_type j = i + 1; j < prefsize; ++j ){

            if( j != i ){

                compairs.ypref = listofagents[ randagt ][ j ];

                paircomp.push_back( compairs );
            }
        }
    }

    // returns all combinations without repetitions
    return paircomp;
}

void initialize_opts( Population& listofagents, Profile& opts ){

    std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );

    if( !listofagents[ randagt ].get_preferences( ).empty( ) ){

        opts = listofagents[ randagt ].get_preferences( ).get_alternatives( );

        for( std::vector<int>::size_type i = 0; i < opts.size( ); ++i )

            opts[ i ].set_value( 0 );
    }

    else{

        std::cerr << "Agent " << listofagents[ randagt ].get_id( ) << " has no preferences.\n";
    }
}

void initialize_opts( Rank& rank, Profile& profile ){

    // Get all possible options
    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

        profile.push_back( Options( rank[ i ].get_optx( ).get_opt( ), false, 0 ) );
        profile.push_back( Options( rank[ i ].get_opty( ).get_opt( ), false, 0 ) );
    }

    // Remove repeated options
    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        for( std::vector<int>::size_type j = 0; j < profile.size( ); ++j ){

            if( i != j ){

                if( profile[ i ].get_opt( ) == profile[ j ].get_opt( ) ){

                    profile.erase( static_cast<int>( j ) );
                }
            }
        }
    }
}

/// Printing Functions

/// Data Structures Modifying Functions

/*void circuits( Graph& graph ){


}

void johnson( Graph& graph ){


}*/

Profile make_social_order( Population& population ){

    Profile result{ };

    return result;
}

// Makes a social order from a Pairwise Rank of alternatives
Profile make_social_order( /*std::vector<Agent>& listofagt,*/ Rank& rank ){

    Profile orderedrank{ };

    initialize_opts( rank, orderedrank );

    // Check for emptyness - I really should make a exception class to handle this
    if( !orderedrank.empty( ) )

        // get every available option
        for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

            // get their respective scores, i.e., how many options they beat
            for( std::vector<int>::size_type j = 0; j < orderedrank.size( ); ++j ){

                if( rank[ i ].get_optx( ).get_opt( ) == orderedrank[ j ].get_opt( ) ){

                    if( rank[ i ].get_xval( ) > rank[ i ].get_yval( ) )

                        // ATTENTION: this + 1 at the end...
                        ++orderedrank[ j ];
                }

                else if( rank[ i ].get_opty( ).get_opt( ) == orderedrank[ j ].get_opt( ) ){

                    if( rank[ i ].get_xval( ) < rank[ i ].get_yval( ) )

                        // ATTENTION: this + 1 at the end...
                        ++orderedrank[ j ];
                }
            }
        }

    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    // order vector from greatest to smallest, according to the value
    std::sort( orderedrank.begin( ), orderedrank.end( ), order );

    return orderedrank;
}

// Makes a social order from a Social Graph of alternatives
/*Profile make_social_order( Graph& socialgraph ){

    Profile orderedrank{ };

    for( std::vector<int>::size_type i = 0; i < socialgraph.size( ); ++i ){

        std::vector<Options>::iterator aux{ };

        aux = orderedrank.begin( );

        int value = static_cast<int>( socialgraph[ i ].get_preferences( ).size( ) );

        for( std::vector<int>::size_type j = 0; j < orderedrank.size( ) && value <= orderedrank[ j ].get_value( ); ++j ){

            aux++;
        }

        Options holder( socialgraph[ i ].get_id( ), false, static_cast<int>( socialgraph[ i ].get_preferences( ).size( ) + 1 ) );

        orderedrank.insert( aux, holder );
    }

    return orderedrank;
}*/
