#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\majoritarian_rules.hpp"

/// Qualified Majority Methods

// Constructors

// Operators

// If the number of Profiles in which a beats b > ( number of alternatives / 2 ),
// then a beats b, i.e., aPb. If there is a cycle, winnerset order will NECESSARILY
// be WRONG! This is not an implementation problem, since majority rule is NOT
// guaranteed to be acyclic! Thus, the implementation is CORRECT.

// What happens when we have an even number of profiles s.t. a == b????????
Profile SCT::Qualified_majority_rule::operator( )( Preferencematrix& matrix ){

	SCT::Decision_set set{ };
	set( matrix );

	auto is_in_profile = [ ]( Profile& perfil, Options& opt ){

		for( auto i = 0; i < perfil.size( ); ++i ){

			if( perfil[ i ] == opt ){

				return true;
			}
		}

		return false;
	};

	winnerset = *matrix.begin( );

	// Assuming that profiles are ordered lexicographically
	for( auto perfil : set.get_decisors( ) ){

		// This is unnecessary. REMOVE
		if( winnerset.empty( ) ){

			if( perfil.winner.get_value( ) > ( matrix.size( ) / 2 ) ){

				winnerset.push_back( perfil.winner );
				
				if( perfil.pair.xpref == perfil.winner ){

					winnerset.push_back( perfil.pair.ypref );
				}

				else{

					winnerset.push_back( perfil.pair.xpref );
				}
			}
		}

		// This part relies largely on the structure of decision_sets.
		else{

		// Two possible cases:
			
			// both are in winnerset
			if( is_in_profile( winnerset, perfil.pair.xpref ) &&
				is_in_profile( winnerset, perfil.pair.ypref ) ){

				// If x is the winner, but x is located AFTER y in winnerset,
				// INSERT IN BETWEEN! I.e., insert winner before loser
				if( perfil.pair.xpref == perfil.winner &&
					std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.xpref ) >
					std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.ypref ) ){

					std::vector<Options>::size_type position_y{ };
					std::vector<Options>::size_type position_x{ };

					for( auto i = 0; i < winnerset.size( ); ++i ){

						if( winnerset[ i ] == perfil.pair.ypref ){

							position_y = i;
						}

						else if( winnerset[ i ] == perfil.pair.xpref ){

							position_x = i;
						}
					}

					std::vector<Options>::iterator iterate_y = std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.ypref );

					winnerset.insert( iterate_y, perfil.pair.xpref );
					winnerset.erase( position_x + 1 );
				}

				else if( perfil.pair.ypref == perfil.winner &&
						 std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.ypref ) >
						 std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.xpref ) ){

					std::vector<int>::size_type position_x{ };
					std::vector<Options>::size_type position_y{ };

					for( auto i = 0; i < winnerset.size( ); ++i ){

						if( winnerset[ i ] == perfil.pair.ypref ){

							position_y = i;
						}

						else if( winnerset[ i ] == perfil.pair.xpref ){

							position_x = i;
						}
					}

					std::vector<Options>::iterator iterate_x = std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.xpref );

					winnerset.insert( iterate_x, perfil.pair.ypref );
					winnerset.erase( position_y + 1 );
				}
			}

			// one is not in winnerset
			else{

				// which must be ypref, by the structure of decision_set
				winnerset.push_back( perfil.pair.ypref );
			}
		}
	}

	score( matrix );

	return winnerset;
}

// Returns the majority winner from a pair ( left, right )
Options SCT::Qualified_majority_rule::operator( )( Options& left, Options& right, Preferencematrix& matrix ){

	SCT::Decision_set set{ };
	set( matrix );

	for( auto element : set.get_decisors( ) ){

		if( ( element.pair.xpref == left && element.pair.ypref == right ) ||
			( element.pair.ypref == left && element.pair.xpref == right ) ){

			if( element.elements.size( ) > ( matrix.size( ) / 2 ) ){

				return element.winner;
			}

			else{

				continue;
			}
		}

		else{

			continue;
		}
	}
}

void SCT::Qualified_majority_rule::score( Preferencematrix& matrix ){

	SCT:Decision_set set{ };
	set( matrix );

	for( std::vector<Options>::size_type i = 0; i < winnerset.size( ); ++i ){

		winnerset[ i ].set_value( 0 );
	}

	for( auto decisor : set.get_decisors( ) ){

		// how many alternatives does x beat?
		for( std::vector<Options>::size_type i = 0; i < winnerset.size( ); ++i ){

			if( winnerset[ i ] == decisor.winner ){

				winnerset[ i ]++;
			}

			else{
				
				continue;
			}
		}
	}
}

/// Simple Majority Methods

// Constructors

// Operators
Profile SCT::Simple_majority_rule::operator( )( Preferencematrix& matrix ){

	return winnerset;
}

/// Two_round Simple majority Methods - NEEDS TESTING

// Constructors

// Operators

Profile SCT::Two_rounds::operator( )( Preferencematrix& matrix ){

	return winnerset;
}
