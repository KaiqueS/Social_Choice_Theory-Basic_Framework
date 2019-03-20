#include "majoritarian_rules.hpp"

/// Qualified Majority Methods

Profile SCT::Qualified_majority_rule::operator( )( Profile& profile ){

    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        if( profile[ i ].get_value( ) >= static_cast<int>( profile.size( ) / 2 ) )

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

    make_social_order( winnerset, matrix );

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

    winnerset = make_social_order( population );

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

// Working on it
Profile& SCT::Qualified_majority_rule::operator+=( Profile& rhs ){

    Preferencematrix mtx{ };

    mtx.push_back( winnerset );
    mtx.push_back( rhs );

    make_social_order( rhs, mtx );


}

Profile& SCT::Qualified_majority_rule::operator+=( Preferencematrix& rhs ){

}

Profile& SCT::Qualified_majority_rule::operator+=( Rank& rhs ){

}



/// Simple Majority Methods

Profile SCT::Simple_majority_rule::operator( )( Profile& profile ){

    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( profile.begin( ), profile.end( ), order );

    std::max_element( profile.begin( ), profile.end( ) ) -> set_value( true );

    return profile;
}

Profile SCT::Simple_majority_rule::operator( )( Preferencematrix& matrix ){

	make_social_order( winnerset, matrix );

    std::max_element( winnerset.begin( ), winnerset.end( ) ) -> set_status( true );

    return winnerset;
}

Profile& SCT::Simple_majority_rule::operator( )( Population& population ){

    winnerset = make_social_order( population );

    std::max_element( winnerset.begin( ), winnerset.end( ) ) -> set_status( true );

    return winnerset;
}

Profile& SCT::Simple_majority_rule::operator( )( Rank& rank ){

    winnerset = make_social_order( rank );

    std::max_element( winnerset.begin( ), winnerset.end( ) ) -> set_status( true );

    return winnerset;
}

Profile& SCT::Simple_majority_rule::operator+=( Profile& rhs ){


}

Profile& SCT::Simple_majority_rule::operator+=( Preferencematrix& rhs ){


}

Profile& SCT::Simple_majority_rule::operator+=( Rank& rhs ){


}
