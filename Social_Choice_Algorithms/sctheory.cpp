#include "sctheory.hpp"

// Remember: function will be a functor, which, in turn, will return a profile of preferences, so
// one has to guarantee that the parameter function will return something that have the below nec
// essary methods, like, e.g., .size( ).

void processed_profile( Preferencematrix& matrix, SCT::Procedure& procedure ){

	for( std::vector<int>::size_type i = 0; i < matrix.size( ); ++i ){

		procedure( matrix[ i ] );
	}
}

// Check for a case where pair1 == pair2 but pair1.xval/yval != pair2.xval/yval, i.e., a case where the relation between
// optx and opty of two pairs is the same but their values are different
// Maybe it would be best if randprofile were not used, and the algorithm went to different pairs?
Rank ranking_comparison( Rank& originalrank, Rank& primerank, Preferencematrix& primemtx, SCT::Procedure& procedure ){

	// Problem here: original != prime even though original holds the same relations as prime
	while( originalrank != primerank && rank_relations( originalrank, primerank ) == false ){

		for( std::vector<int>::size_type i = 0; i < originalrank.size( ); ++i ){

			// wtf primerank is NULL my BALLS
			if( originalrank[ i ] != primerank[ i ] && relation_comparison( originalrank[ i ], primerank[ i ] ) == false ){

				// maybe i should cut this off? and use the conditional above to identify the point that need to be changed?
				std::vector<int>::size_type randprofile = static_cast<std::vector<int>::size_type>( rand( ) ) % primemtx.size( );

				std::vector<int>::size_type x = find_opt( primemtx[ randprofile ], primerank[ i ].get_optx( ) );
				std::vector<int>::size_type y = find_opt( primemtx[ randprofile ], primerank[ i ].get_opty( ) );

				//std::swap( primemtx[ indX ], primemtx[ indY ] );
				Options holder = primemtx[ randprofile ][ x ];

				primemtx[ randprofile ][ x ].set_opt( primemtx[ randprofile ][ y ].get_opt( ) );
				primemtx[ randprofile ][ y ].set_opt( holder.get_opt( ) );

				processed_profile( primemtx, procedure );

				primerank = { };

				primerank.generate_ranking( primemtx );
				primerank.order_ranking( );
			}

			else

				continue;
		}
	}

	primerank.order_ranking( );

	return primerank;
}

Rank prime_profile_generating( Preferencematrix& original, SCT::Procedure& procedure ){

	// generate a second set of individual profiles s.t. it:
	//		has the same set of alternatives
	//		has the same relations between any two alternatives
	//		is different from the initial set

	processed_profile( original, procedure );

	Preferencematrix prime{ };
	prime.set_matrix( original.get_columnsz( ), original.get_rowsz( ) );
	processed_profile( prime, procedure );

	// since ranks have the same alternatives, order each rank alphabetically, makes comparing easier
	Rank originalrank{ };
	originalrank.generate_ranking( original );
	originalrank.order_ranking( );

	Rank primerank{ };
	//primerank.generate_ranking( prime );
	primerank.generate_ranking( prime );
	primerank.order_ranking( );
	primerank = ranking_comparison( originalrank, primerank, prime, procedure );

	// This may call options == operator, which is defined only for options id's.
	// It may happen that original and prime have the same options in the same order, but
	// different values, and thus, different relations.
	// Fix this
	if( ( original == prime ) && ( rank_relations( originalrank, primerank ) == true ) ){

		return originalrank;
	}

	else if( ( original != prime ) && ( rank_relations( originalrank, primerank ) == true ) ){

		return originalrank;
	}

	else if( ( original != prime ) && ( rank_relations( originalrank, primerank ) == false ) ){

		//primerank = ranking_comparison( originalrank, primerank, original, procedure );

		//order_ranking( primerank );

		return prime_profile_generating( original, procedure );
	}

	else

		return primerank;

	// since the relation P is based on a procedure, I mean, is determined by the relation
	// expressed, integrated, to a procedure, then, form the pairs x, y according to a procedure


	// How to do so?
	// Generate a preferencematrix prime
	// Check if it is equal to the original preference matrix
	// if it is not, check if the relations between the alternatives are the same
	// if the relations are not the same, modify the prime matrix until it has the same preference relations
	// how so?
	// repeat
//	|-->	// get the first pair x, y whose relation was determined in accordance to original matrix and a procedure
//	|	// check if the relation holds in prime
//	|		// if it does not hold, go to the point that make the relation not hold, i.e., the profile that nulifies it
//	|			// exchange the position of x, y in the profile
//	|----------- // go back to the beginning
			// if it does, go to the next pair

	// apply the procedure to each individual profile, pass each profile to a row in prefmatrix
	// generate a sctrank from prefmatrix
	// compare prime rank with original rank
	// if they are not equal, modify prime rank until it holds the same relations as the ones in
	// original rank


	// should I generate a sctrank where xval, yval values are taken from the procedure?

	// Use preferencematrix

}

///

bool SCT::Pareto_Principle::operator( )( SCT::Procedure& procedure ){

	// Problem here: agents with no preferences
	population.order_preferences( );

	//std::cout << "Debug 1.\n";

	Options optimum{ };

	for( std::vector<int>::size_type i = 0; i < population.size( ); ++i ){

		for( std::vector<int>::size_type j = 0; j < population[ i ].get_preferences( ).size( ); ++j ){

			for( std::vector<int>::size_type k = j + 1; k < population[ i ].get_preferences( ).size( ); ++k ){

				if( population[ i ][ j ].get_value( ) == population[ i ][ k ].get_value( ) ){

					return true;
				}

				else{

					optimum = population[ i ][ j ];

					optimum.set_status( true );

					continue;
				}
			}
		}
	}

	//std::cout << "Debug 2.\n";

	if( optimum.get_opt( ) != procedure( population ).get_alternatives( ).begin( ) -> get_opt( ) )

		return false;

	else

		return true;
}

bool SCT::Irrelevant_Alternatives::operator( )( SCT::Procedure& procedure ){
	
	Rank originalrank{ };
	originalrank.generate_ranking( matrix );

	Preferencematrix prime{	};
	prime.set_matrix( matrix.get_rowsz( ), matrix.get_columnsz( ) );

	Rank primerank = prime_profile_generating( prime, procedure );

	if( ( originalrank == primerank ) && ( rank_relations( originalrank, primerank ) == true ) ){

		if( procedure( originalrank ) != procedure( primerank ) )

			return false;

		else

			return true;
	}

	else if( ( originalrank != primerank ) && ( rank_relations( originalrank, primerank ) == true ) ){

		if( procedure( originalrank ) == procedure( primerank ) )

			return true;

		else

			return false;
	}

	else

		return false;

	// this is all about relative positioning of alternatives. If, for any two profiles p and p', the rela
	// tive positions of its alternatives are the same, then, f( p ) and f( p' ) will keep their relative
	// positions equal

	// Try to construct two p and p' s.t. p != p' but, for any x,y in p, p', x and y have the same relative
	// positions -> It is possible, indeed, for two profiles to be different and have same relative posit
	// ions for any two alternatives

	// I'll have to make an algorithm to generate a secondary profile p' s.t. it maintains the same rela
	// tive positions of its alternatives with respect to a first profile p
}

// Find an agent that, whenever ONLY HER prefers x to y, the social order becomes xPy
// If is that the case that another person also prefers x to y, then the clause is not
// valid
// TODO: revise this
bool SCT::Non_Dictatorship::operator( )( SCT::Procedure& procedure ){


}

// TODO: use this only for the case where there are only three alternatives,
// so -> check rank and graph sizes, then check for condorcerity
bool SCT::Condorcet_Paradox::operator( )( Profile& profile ){

    int selection{ };

    Graph result{ };

    std::cout << "Which data structure do you wish to use? 1- Rank 2- Graph: ";

    std::cin >> selection;

    if( selection != 1 && selection != 2 ){

        std::cerr << "Invalid options.\n";

		// Man... this smells like shit
		return SCT::Condorcet_Paradox::operator( )( profile );
    }

    // THIS IS SHITTY AF. Use recursion instead, for god's sake.
    else{

        if( selection == 1 ){

            if( ( ( ( rank.size( ) ^ 2 ) - rank.size( ) ) / 2 ) > 3 ){

                std::cerr << "Invalid number of options. Condorcert only applies to cases where the number of options is 3. Use another rank.\n";

                return false;
            }

            else{

                Graph visited{ };

                for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

                    SocialPrefNode actualnode( graph[ i ] );

                    visited.push_back( actualnode );

                    actualnode.set_onstack( true );

                    for( long j = 0; j < static_cast<long>( actualnode.get_preferences( ).size( ) ); ++j ){

                        if( actualnode[ SocialPrefNode::preferences_index{ j } ] -> get_onstack( ) == false ){

                            actualnode[ SocialPrefNode::preferences_index{ j } ] -> set_onstack( true );

                            visited.push_back( *actualnode[ SocialPrefNode::preferences_index{ j } ] );

                            // FULL GAMBIARRA MODE ON
                            actualnode = *actualnode[ SocialPrefNode::preferences_index{ j } ];

                            j = 0;
                        }

                        else

                            continue;
                    }
                }
            }
        }

        else if( selection == 2 ){

            if( static_cast<int>( graph.size( ) ) != 3 ){

                std::cerr << "Invalid number of options. Condorcert only applies to cases where the number of options is 3. Use another rank.\n";

                return false;
            }

            else{

                Graph visited{ };

                for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

                    SocialPrefNode actualnode( graph[ i ] );

                    actualnode.set_onstack( true );

                    visited.push_back( actualnode );

                    for( long j = 0; j <static_cast<long>( actualnode.get_preferences( ).size( ) ); ++j ){

                        if( actualnode[ SocialPrefNode::preferences_index{ j } ] -> get_onstack( ) == false ){

                            actualnode[ SocialPrefNode::preferences_index{ j } ] -> set_onstack( true );

                            visited.push_back( *actualnode[ SocialPrefNode::preferences_index{ j } ] );

                            // FULL GAMBIARRA MODE ON
                            actualnode = *actualnode[ SocialPrefNode::preferences_index{ j } ];

                            --j;
                        }

                        else

                            continue;
                    }
                }

                result = visited;
            }
        }
    }

    for( std::vector<int>::size_type i = 0; i < result.size( ); ++i ){

        for( std::vector<int>::size_type j = 0; j < result.size( ); ++j ){

            if( j != i ){

                if( result[ j ].get_id( ) == result[ i ].get_id( ) ){

                    std::cout << "There is a cycle!\n";

                    return false;
                }
            }
        }
    }

    std::cout << "There are no cycles!\n";

    return true;
}

bool SCT::Single_Peakedness::operator( )( Rank& rank, Graph& graph ){

    return true;
}

// If not true: analyze the profiles of preferences, both individual and social, then search for some kind of structure,
// i.e., single peakedness degree, individual impact on social profile, etc.
// If true, search for single peakedness or known structures/feats that causes the truthness
bool SCT::Arrow_Impossibility::operator( )( SCT::Procedure& procedure ){

    // If it is the case that every conditions is satisfied, then, check the structure of the preferences for single-
    // peakedness or anything that might have made it possible for the result to hold
	bool validity{ true };

	//std::cout << "Problem line 1\n";

    // PROBLEM HERE
    if( pareto( procedure ) == false ){

        validity = false;

        std::cout << "Pareto principle violated.\n";
    }

    //std::cout << "Problem line 2\n";

    if( irrelevant( procedure ) == false ){

        validity = false;

        std::cout << "Irrelevant alternatives violated.\n";
    }

    //std::cout << "Problem line 3\n";

	// PROBLEM HERE MA BOI
    if( dictator( procedure ) == false ){

        validity = false;

        std::cout << "Nondictatorship violated.\n";
	}

	//std::cout << "Problem line 4\n";

    if( validity == true ){

        std::cout << "Everything all right.\n";

        return validity;
    }

    else{

        std::cout << "Shit!.\n";

        return validity;
    }
}
