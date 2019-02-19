#include "plurality_rules.hpp"

Profile& SCT::Borda_count::operator( )( Population& population ){

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

    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( winnerset.begin( ), winnerset.end( ), order );

    std::max_element( winnerset.begin( ), winnerset.end( ) ) -> set_status( true );

    // TODO: make graph according to borda count before returning graph

    return winnerset;
}

Profile& SCT::Borda_count::operator( )( Rank& rank ){

    winnerset = make_social_order( rank );

    for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

        winnerset[ i ].set_value( 0 );
    }

    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

        for( std::vector<int>::size_type j = 0; j < winnerset.size( ); ++j ){

            if( winnerset[ j ].get_opt( ) == rank[ i ].get_optx( ).get_opt( ) ){

                winnerset[ j ] += rank[ i ].get_xval( );
            }

            else if( winnerset[ j ].get_opt( ) == rank[ i ].get_opty( ).get_opt( ) ){

                winnerset[ j ] += rank[ i ].get_yval( );
            }
        }
    }

    return winnerset;
}