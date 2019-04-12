#include "majoritarian_rules.hpp"

/// Qualified Majority Methods

// Constructors

// Operators
Profile SCT::Qualified_majority_rule::operator( )( Profile& profile ){

    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        if( profile[ i ].get_value( ) >= static_cast<int>( std::ceil( profile.size( ) / 2 ) ) )

            profile[ i ].set_status( true );

        else

            profile[ i ].set_status( false );
    }

    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( profile.begin( ), profile.end( ), order );

    return profile;
}

Profile SCT::Qualified_majority_rule::operator( )( Preferencematrix& matrix ){

    winnerset.clear( );

    Rank rank( matrix );

    winnerset = make_social_order( rank );

    for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

        if( winnerset[ i ].get_value( ) >= static_cast<int>( winnerset.size( ) / 2 ) )

            winnerset[ i ].set_status( true );

        else

            winnerset[ i ].set_status( false );
    }

    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( winnerset.begin( ), winnerset.end( ), order );

    return winnerset;
}

Profile& SCT::Qualified_majority_rule::operator( )( Population& population ){

    Rank rank( population );

    winnerset = make_social_order( rank );

    for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

        if( winnerset[ i ].get_value( ) >= static_cast<int>( winnerset.size( ) / 2 ) )

            winnerset[ i ].set_status( true );

        else

            winnerset[ i ].set_status( false );
    }

    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( winnerset.begin( ), winnerset.end( ), order );

    return winnerset;
}

Profile& SCT::Qualified_majority_rule::operator( )( Rank& rank ){

    winnerset = make_social_order( rank );

    for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

        if( winnerset[ i ].get_value( ) > static_cast<int>( winnerset.size( ) / 2 ) )

            winnerset[ i ].set_status( true );

        else

            winnerset[ i ].set_status( false );
    }

    return winnerset;
}

// Hum... remember to modify the operator( ) behavior for matrixes and populations.
// This is not right
Profile& SCT::Qualified_majority_rule::operator+=( Profile& rhs ){

	Preferencematrix matrix = { winnerset, rhs };

	winnerset = SCT::Qualified_majority_rule::operator( )( matrix );

    return winnerset;
}

Profile& SCT::Qualified_majority_rule::operator+=( Preferencematrix& rhs ){

	winnerset = SCT::Qualified_majority_rule::operator( )( rhs );

	return winnerset;
}

Profile& SCT::Qualified_majority_rule::operator+=( Rank& rhs ){

	winnerset = SCT::Qualified_majority_rule::operator( )( rhs );

	return winnerset;
}

/// Simple Majority Methods

// Constructors

// Operators
Profile SCT::Simple_majority_rule::operator( )( Profile& profile ){

    /*auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( profile.begin( ), profile.end( ), order );*/

    profile.value_merge_sort( 0, profile.size( ) - 1 );

    std::max_element( profile.begin( ), profile.end( ) ) -> set_value( true );

	for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

		if( ( winnerset[ i ] != *winnerset.begin( ) ) && ( winnerset[ i ].get_value( ) == winnerset.begin( )->get_value( ) ) ){

			winnerset[ i ].set_status( true );
		}

		else

			continue;
	}

    return profile;
}

Profile SCT::Simple_majority_rule::operator( )( Preferencematrix& matrix ){

	winnerset.clear( );

	Rank rank( matrix );

	winnerset = make_social_order( rank );

    std::max_element( winnerset.begin( ), winnerset.end( ) ) -> set_status( true );

	for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

		if( ( winnerset[ i ] != *winnerset.begin( ) ) && ( winnerset[ i ].get_value( ) == winnerset.begin( )->get_value( ) ) ){

			winnerset[ i ].set_status( true );
		}

		else

			continue;
	}

    return winnerset;
}

Profile& SCT::Simple_majority_rule::operator( )( Population& population ){

    winnerset.clear( );

    Rank rank( population );

    winnerset = make_social_order( rank );

    // Problem here
    std::max_element( winnerset.begin( ), winnerset.end( ) ) -> set_status( true );

	for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

		if( ( winnerset[ i ] != *winnerset.begin( ) ) && ( winnerset[ i ].get_value( ) == winnerset.begin( )->get_value( ) ) ){

			winnerset[ i ].set_status( true );
		}

		else

			continue;
	}

    return winnerset;
}

Profile& SCT::Simple_majority_rule::operator( )( Rank& rank ){

    winnerset.clear( );

    winnerset = make_social_order( rank );

    std::max_element( winnerset.begin( ), winnerset.end( ) ) -> set_status( true );

	for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

		if( ( winnerset[ i ] != *winnerset.begin( ) ) && ( winnerset[ i ].get_value( ) == winnerset.begin( )->get_value( ) ) ){

			winnerset[ i ].set_status( true );
		}

		else

			continue;
	}

    return winnerset;
}

Profile& SCT::Simple_majority_rule::operator+=( Profile& rhs ){

	Preferencematrix matrix = { winnerset, rhs };

	winnerset = SCT::Simple_majority_rule::operator( )( matrix );

	return winnerset;
}

Profile& SCT::Simple_majority_rule::operator+=( Preferencematrix& rhs ){

	winnerset = SCT::Simple_majority_rule::operator( )( rhs );

	return winnerset;
}

Profile& SCT::Simple_majority_rule::operator+=( Rank& rhs ){

	winnerset = SCT::Simple_majority_rule::operator( )( rhs );

	return winnerset;
}
