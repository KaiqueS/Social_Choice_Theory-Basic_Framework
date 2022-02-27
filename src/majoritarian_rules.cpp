#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\majoritarian_rules.hpp"

/// Qualified Majority Methods

// Constructors

// Operators

// Assuming that profiles are ordered lexicographically
Profile SCT::Qualified_majority_rule::operator( )( Preferencematrix& matrix ){

	SCT::Decision_set set{ };
	set( matrix );

	// Talvez jogar o if empty pra fora e usar o for só no else
	// if empty, read a pair and insert it, recursion. Recursion
	// is not a good idea, though, because it would require the
	// reconstruction of set, which is costly.

	auto is_in_profile = [ ]( Profile& perfil, Options& opt ){

		for( auto i = 0; i < perfil.size( ); ++i ){

			if( perfil[ i ] == opt ){

				return true;
			}
		}

		return false;
	};

	winnerset = *matrix.begin( );

	for( auto perfil : set.get_decisors( ) ){

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

		// Problem: the algorithm only starts ordering after the last ( a, x ), for x != a
		// is read. I.e., it does not order any ( a, x ) in perfil. I.e., the ordering starts
		// at ( b, c ) always, i.e., after all ( a, x ) were read

		// Two possible cases:
			
			// both are in winnerset
			if( is_in_profile( winnerset, perfil.pair.xpref ) &&
				is_in_profile( winnerset, perfil.pair.ypref ) ){

				// If x is the winner, but x is located AFTER y in winnerset, swap
				// INSTEAD OF SWAPPING, INSERT IN BETWEEN! I.e., insert winner 
				// before loser
				if( perfil.pair.xpref == perfil.winner &&
					std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.xpref ) >
					std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.ypref ) ){

					std::vector<Options>::size_type position_y{ };

					/*for( auto i = 0; i < winnerset.size( ); ++i ){

						if( winnerset[ i ] == perfil.pair.ypref ){

							position_y = i;
						}
					}*/

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

					//std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.xpref ) -> operator=( perfil.pair.ypref );
					//winnerset[ position_y ] = perfil.pair.xpref;
				}

				else if( perfil.pair.ypref == perfil.winner &&
						 std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.ypref ) >
						 std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.xpref ) ){

					std::vector<int>::size_type position_x{ };

					/*for( auto i = 0; i < winnerset.size( ); ++i ){

						if( winnerset[ i ] == perfil.pair.xpref ){

							position_x = i;
						}
					}*/

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

					//std::find( winnerset.begin( ), winnerset.end( ), perfil.pair.ypref ) -> operator=( perfil.pair.xpref );
					//winnerset[ position_x ] = perfil.pair.ypref;
				}
			}

			// one is not in winnerset
			else{

				// which must be ypref, by the structure of decision_set
				winnerset.push_back( perfil.pair.ypref );
			}
		}
	}

	// if the ordering is transitive
	return winnerset;

	// else
	// return an exception or empty profile? Maybe exception. Since arrow consider only transitive profiles
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
