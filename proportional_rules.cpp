#include "proportional_rules.hpp"

Profile SCT::Proportional::operator( )( Profile& profile ){

    int quotient{ };

    std::cout << "Enter a quotient between 1 and " << profile.size( ) << ": ";

    std::cin >> quotient;

    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        if( profile[ i ].get_value( ) >= quotient )

            profile[ i ].set_status( true );

        else

            profile[ i ].set_status( false );
    }

    return winnerset;
}

Profile SCT::Proportional::operator( )( Preferencematrix& matrix ){

	int quotient{ 0 };

	std::cout << "Enter a quotient between 1 and " << matrix.begin( )-> get_alternatives( ).size( ) << ": ";

	std::cin >> quotient;

	Rank rank( matrix );

	winnerset = make_social_order( rank );

	for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

		if( winnerset[ i ].get_value( ) >= quotient )

			winnerset[ i ].set_status( true );

		else

			winnerset[ i ].set_status( false );
	}

	return winnerset;
}

Profile& SCT::Proportional::operator( )( Population& population ){

    int quotient{ 0 };

    std::cout << "Enter a quotient between 1 and " << population.begin( ) -> get_preferences( ).size( ) << ": ";

    std::cin >> quotient;

    Rank rank( population );

    winnerset = make_social_order( rank );

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

// Debug this later
Profile& SCT::Proportional::operator+=( Profile& profile ){

	Preferencematrix matrix = { winnerset, profile };

	Rank ranking( matrix );
	
	winnerset = SCT::Proportional::operator( )( ranking );

	return winnerset;
}

Profile& SCT::Proportional::operator+=( Preferencematrix& matrix ){

	winnerset = SCT::Proportional::operator( )( matrix );

	return winnerset;
}

Profile& SCT::Proportional::operator+=( Rank& rank ){

	winnerset = SCT::Proportional::operator( )( rank );

	return winnerset;
}
