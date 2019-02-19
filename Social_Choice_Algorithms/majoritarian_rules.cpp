#include "majoritarian_rules.hpp"

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
