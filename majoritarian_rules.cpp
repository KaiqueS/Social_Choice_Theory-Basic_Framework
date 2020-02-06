#include "/Projetos/SocialChoice_VS/Include/majoritarian_rules.hpp"

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

    //check wether or not matrix is empty

    winnerset = make_social_order( *matrix.begin( ), rank ); // Check make_social_order()

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

    Profile prof = population.begin( ) -> get_preferences( ); // Updated this for new definition of make_social_order

    winnerset = make_social_order( prof, rank );

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

	winnerset = make_social_order( *matrix.begin( ), rank );

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

    Profile profile{ population.begin( ) -> get_preferences( ) }; // Updated version of make_social_order

    winnerset = make_social_order( profile, rank );

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

Profile& SCT::Simple_majority_rule::operator+=( Profile& rhs ){

	Preferencematrix matrix = { winnerset, rhs };

	winnerset = SCT::Simple_majority_rule::operator( )( matrix );

	return winnerset;
}

Profile& SCT::Simple_majority_rule::operator+=( Preferencematrix& rhs ){

	winnerset = SCT::Simple_majority_rule::operator( )( rhs );

	return winnerset;
}

/// Two_round Simple majority Methods - NEEDS TESTING

// Constructors

// Operators
Profile SCT::Two_rounds::operator( )( Profile& profile ){

    profile.sort_by_value( );

    std::cout << "The two most voted alternatives are: " << profile[ 0 ] << " and " << profile[ 1 ]
              << ".\n";

    if( profile[ 0 ] > profile[ 1 ] ){

        profile[ 0 ].set_status( true );

        std::cout << "The winner is " << profile[ 0 ] << ".\n";

        for( std::vector<int>::size_type i = 1; i < profile.size( ); ++i ){

            profile[ i ].set_status( false );
        }
    }

    else if( profile[ 0 ] == profile[ 1 ] ){

        profile[ 0 ].set_status( true );
        profile[ 1 ].set_status( true );

        std::cout << profile[ 0 ] << " and " << profile[ 1 ] << " are tied!\n";

        for( std::vector<int>::size_type i = 2; i < profile.size( ); ++i ){

            profile[ i ].set_status( false );
        }
    }

    return profile;
}
Profile SCT::Two_rounds::operator( )( Preferencematrix& matrix ){

    // Takes the two most voted alternatives
    // Generates a ranking that considers only those two alternatives
    // Checks the winner with qualified majority
    Rank ranking( matrix );

    winnerset = make_social_order( *matrix.begin( ), ranking ); // Updated version of make_social_order

    return SCT::Two_rounds( ).operator( )( winnerset );
}
Profile& SCT::Two_rounds::operator( )( Population& population ){

    Rank ranking( population );

    Profile profile{ population.begin( ) -> get_preferences( ) };

    winnerset = make_social_order( profile, ranking ); // Updated version of make_social_order
    winnerset = SCT::Two_rounds( ).operator( )( winnerset );

    return winnerset;
}

Profile& SCT::Two_rounds::operator+=( Profile &rhs ){

    return winnerset;
}
Profile& SCT::Two_rounds::operator+=( Preferencematrix &rhs ){

    return winnerset;
}
