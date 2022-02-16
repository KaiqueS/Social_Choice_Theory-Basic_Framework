#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\majoritarian_rules.hpp"

/// Qualified Majority Methods

// Constructors

// Operators
Profile SCT::Qualified_majority_rule::operator( )( Preferencematrix& matrix ){

	SCT::Decision_set set{ };
	set( matrix );

	for( auto perfil : set.get_decisors( ) ){

		if( !winnerset.empty( ) ){

			if( perfil.winner.get_value( ) > ( matrix.size( ) / 2 ) ){

				winnerset.push_back( perfil.winner );
				
				if( perfil.pair.xpref == perfil.winner ){

					winnerset.push_back( perfil.pair.ypref );
				}

				else{

					winnerset.push_back( perfil.pair.ypref );
				}
			}
		}

		// FINISH THIS
		else{

			Options* left = std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.xpref );
			Options* right = std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.ypref );
		}
	}

	return winnerset;
}



// Hum... remember to modify the operator( ) behavior for matrixes and populations.
// This is not right
Profile& SCT::Qualified_majority_rule::operator+=( Profile& rhs ){

	return winnerset;
}

Profile& SCT::Qualified_majority_rule::operator+=( Preferencematrix& rhs ){

	return winnerset;
}

/// Simple Majority Methods

// Constructors

// Operators
Profile SCT::Simple_majority_rule::operator( )( Preferencematrix& matrix ){

	return winnerset;
}



Profile& SCT::Simple_majority_rule::operator+=( Profile& rhs ){

	return winnerset;
}

Profile& SCT::Simple_majority_rule::operator+=( Preferencematrix& rhs ){

	return winnerset;
}

/// Two_round Simple majority Methods - NEEDS TESTING

// Constructors

// Operators

Profile SCT::Two_rounds::operator( )( Preferencematrix& matrix ){

	return winnerset;
}

Profile& SCT::Two_rounds::operator+=( Profile &rhs ){

	return winnerset;
}
Profile& SCT::Two_rounds::operator+=( Preferencematrix &rhs ){

	return winnerset;
}
