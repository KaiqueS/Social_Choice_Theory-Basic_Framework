#include "/Projetos/SocialChoice_VS/Include/proportional_rules.hpp"

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

	winnerset = make_social_order( *matrix.begin( ), rank ); // Updated version of make_social_order
 
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

    Profile profile{ population.begin( ) -> get_preferences( ) };

    winnerset = make_social_order( profile, rank ); // Updated version of make_social_order

    for( std::vector<int>::size_type i = 0; i < winnerset.size( ); ++i ){

        if( winnerset[ i ].get_value( ) >= quotient )

            winnerset[ i ].set_status( true );

        else

            winnerset[ i ].set_status( false );
    }

    return winnerset;
}

Profile& SCT::Proportional::operator+=( Profile& profile ){

	Preferencematrix matrix = { winnerset, profile };

	Rank ranking( matrix );
	
	winnerset = SCT::Proportional::operator( )( matrix ); // MODIFIED

	return winnerset;
}

Profile& SCT::Proportional::operator+=( Preferencematrix& matrix ){

	winnerset = SCT::Proportional::operator( )( matrix );

	return winnerset;
}
