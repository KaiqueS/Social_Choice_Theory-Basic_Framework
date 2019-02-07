#include "helper_functions.hpp"

/* Possible optimizations: binary search in rank_generation. Harder, better, faster, stronger.
 *						   order agent's orderings according to alternatives' values - enables
 *						   binary search
 */

/*void circuits( Graph& graph ){


}

void johnson( Graph& graph ){


}*/

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
