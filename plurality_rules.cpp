#include "/Projetos/SocialChoice_VS/Include/plurality_rules.hpp"

Profile SCT::Borda_count::operator( )( Profile& profile ){

    // winnerset.clear( );

    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( profile.begin( ), profile.end( ), order );

    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        for( std::vector<int>::size_type j = i + 1; j < profile.size( ); ++j ){

            if( profile[ j ].get_value( ) == profile[ i ].get_value( ) ){

                profile[ i ].set_value( static_cast<int>( profile.size( ) - i ) );

                profile[ j ].set_value( profile[ i ].get_value( ) );

                ++i;
            }

            else

                profile[ i ].set_value( static_cast<int>( profile.size( ) - i ) );
        }
    }

    return profile;
}

Profile SCT::Borda_count::operator( )( Preferencematrix& matrix ){

	// winnerset.clear( );

	initialize_opts( matrix, winnerset );

	winnerset.sort_by_value( );

	for( std::vector<int>::size_type i = 0; i < matrix.size( ); ++i ){

		for( std::vector<int>::size_type j = 0; j < matrix[ i ].get_alternatives( ).size( ); ++j ){

			for( std::vector<int>::size_type k = 0; k < winnerset.size( ); ++k ){

				if( matrix[ i ][ j ].get_opt( ) == winnerset[ k ].get_opt( ) ){

					// THIS IS THE SHIT
					std::vector<int>::size_type bordaranking = matrix[ i ].get_alternatives( ).size( ) - j;

					winnerset[ k ] += static_cast<int>( bordaranking );
				}
			}
		}
	}

	auto order = [ ]( Options& left, Options& right ){

		return left.get_value( ) > right.get_value( );
	};

	std::sort( winnerset.begin( ), winnerset.end( ), order );

	std::max_element( winnerset.begin( ), winnerset.end( ) )->set_status( true );

	return winnerset;
}

Profile& SCT::Borda_count::operator( )( Population& population ){

    // winnerset.clear( );

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

Profile& SCT::Borda_count::operator+=( Profile& profile ){

	Preferencematrix matrix = { winnerset, profile };

	winnerset = SCT::Borda_count::operator( )( matrix );

    return winnerset;
}

Profile& SCT::Borda_count::operator+=( Preferencematrix& matrix ){

	winnerset = SCT::Borda_count::operator( )( matrix );

	return winnerset;
}