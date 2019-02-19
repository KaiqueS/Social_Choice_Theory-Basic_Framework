#include "proportional_rules.hpp"

Profile& SCT::Proportional::operator( )( Population& population ){

    int quotient{ 0 };

    std::cout << "Enter a quotient between 1 and " << population.begin( ) -> get_preferences( ).size( ) << ": ";

    std::cin >> quotient;

    winnerset = make_social_order( population );

    for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

        if( winnerset[ i ].get_value( ) >= quotient )

            winnerset[ i ].set_status( true );

        else

            winnerset[ i ].set_status( false );
    }

    return winnerset;
}

Profile& SCT::Proportional::operator( )( Rank& rank ){

    int quotient{ 0 };

    winnerset = make_social_order( rank );

    std::cout << "Enter a quotient between 1 and " << winnerset.size( ) << ": ";

    std::cin >> quotient;

    for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

        if( winnerset[ i ].get_value( ) >= quotient ){

            winnerset[ i ].set_status( true );
        }

        else

            winnerset[ i ].set_status( false );
    }

    return winnerset;
}
