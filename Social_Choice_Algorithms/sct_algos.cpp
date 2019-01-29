#include "sct_algos.hpp"

// TODO: put different rules into different heades. ATTENTION

/// Majority Rules

// Should the vector be filled with only the elements that satisfy the condition?
/*Profile& sct::Qualified_majority_rule::operator( )( Graph& graph ){

    std::deque<SocialPrefNode> list{ };

    for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

		if( graph[ i ].get_preferences( ).size( ) > ( graph.size( ) / 2 ) ){

			graph[ i ].set_onstack( true );

            list.push_front( graph[ i ] );
		}

		else{

			graph[ i ].set_onstack( false );

            list.push_back( graph[ i ] );
		}
    }

    for( std::vector<int>::size_type i = 0; i < list.size( ); ++i ){

		winnerset.push_back( Options( list[ i ].get_id( ), list[ i ].get_onstack( ), static_cast<int>( list[ i ].get_preferences( ).size( ) ) ) );
    }

	return winnerset;
}
*/

Profile& sct::Qualified_majority_rule::operator( )( Rank& rank ){

    winnerset = make_social_order( rank );

    for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

        if( winnerset[ i ].get_value( ) > static_cast<int>( winnerset.size( ) / 2 ) )

            winnerset[ i ].set_status( true );

        else

            winnerset[ i ].set_status( false );
    }

    return winnerset;
}

/// Counting Rules

Profile& sct::Borda_count::operator( )( Population& population ){

    initialize_opts( population, winnerset );

    population.order_preferences( );

    for( std::vector<int>::size_type i = 0; i < population.size( ); ++i ){

        for( std::vector<int>::size_type j = 0; j < population[ i ].get_preferences( ).size( ); ++j ){

            for( std::vector<int>::size_type k = 0; k < winnerset.size( ); ++k ){

                if( population[ i ][ j ].get_opt( ) == winnerset[ k ].get_opt( ) ){

                    // THIS IS THE SHIT
                    std::vector<int>::size_type bordaranking = population[ i ].get_preferences( ).size( ) - j;

                    winnerset[ k ] += static_cast<int>( bordaranking );
                }
            }
        }
    }

    std::max_element( winnerset.begin( ), winnerset.end( ) ) -> set_status( true );

    // TODO: make graph according to borda count before returning graph

    return winnerset;
}

Profile& sct::Borda_count::operator( )( Rank& rank ){


}

// DEPRECATED
/*auto sct::qualified_majority( Graph& graph ) -> std::string{

    auto order = [ ]( SocialPrefNode& left, SocialPrefNode& right ){

        return left.get_preferences( ).size( ) > right.get_preferences( ).size( );
    };

    std::sort( graph.begin( ), graph.end( ), order );

    auto result = [ &graph ]( ){

        if( graph.begin( ) -> get_preferences( ).size( ) > ( graph.size( ) / 2 ) ){

            return graph.begin( ) -> get_id( );
        }

        else

            return std::string( "null" );
    };

    std::string res = result.operator( )( ).data( );

    return res;
}*/
