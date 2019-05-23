#include "sctheory.hpp"

// Remember: function will be a functor, which, in turn, will return a profile of preferences, so
// one has to guarantee that the parameter function will return something that have the below nec
// essary methods, like, e.g., .size( ).

// Rankings must contain the same alternatives in the same order!
// Still needs more fine tuning - 14x14 new upper bound. ALMOST THERE, THOUGH
Preferencematrix generate_prime_profile( Preferencematrix& originalmatrix ){

	// Make this sort in descending order
	originalmatrix.merge_sort_by_value( );

	Rank originalrank( originalmatrix );
	originalrank.order_ranking( );

	Preferencematrix primematrix( originalmatrix.get_rowsz( ), originalmatrix.get_columnsz( ) );
	primematrix.merge_sort_by_value( );

	Rank primerank( primematrix );
	primerank.order_ranking( );

	for( std::vector<int>::size_type i = 0; i < originalrank.size( ); ++i ){

		if( ( ( originalrank[ i ].get_xval( ) > originalrank[ i ].get_yval( ) ) == true ) &&
			( ( primerank[ i ].get_xval( ) > primerank[ i ].get_yval( ) ) == false ) ){

			std::vector<int>::size_type distance{ primematrix.begin( )->size( ) };
			std::vector<int>::size_type prof{ 0 };

			std::vector<int>::size_type xindex{ };
			std::vector<int>::size_type yindex{ };

			// Find the profile with the smallest profiles which holds the relation with the least distance between x and y
			for( std::vector<int>::size_type j = 0; j < primematrix.size( ); ++j ){

				std::vector<Options, std::allocator<Options>>::iterator x = std::find( primematrix[ j ].begin( ), primematrix[ j ].end( ), originalrank[ i ].get_optx( ) );
				std::vector<Options, std::allocator<Options>>::iterator y = std::find( primematrix[ j ].begin( ), primematrix[ j ].end( ), originalrank[ i ].get_opty( ) );

				if( y->get_value( ) > x->get_value( ) ){

					if( static_cast< std::vector<int>::size_type >( std::abs( x - y ) ) < distance ){

						xindex = static_cast< std::vector<int>::size_type >( x - primematrix[ j ].begin( ) );
						yindex = static_cast< std::vector<int>::size_type >( y - primematrix[ j ].begin( ) );

						distance = static_cast< std::vector<int>::size_type >( std::abs( x - y ) );

						prof = j;
					}
				}
			}

			if( distance == 1 ){

				std::string holder{ primematrix[ prof ][ xindex ].get_opt( ) };

				primematrix[ prof ][ xindex ].set_opt( primematrix[ prof ][ yindex ].get_opt( ) );
				primematrix[ prof ][ yindex ].set_opt( holder );
				// should i merge sort this again? - nah, it sorts by value, swapping position will not alter ranking

				primerank.clear( );
				primerank.generate_ranking( primematrix );
				// should i order ranking here?

				i = -1;
			}

			// Else, if there are k elements between x and y, put y at x and move x and its subsequents elements one place to the right
			else if( distance > 1 ){

				for( std::vector<int>::size_type k = std::min( xindex, yindex ); k <= std::max( xindex, yindex ); ++k ){

					std::string holder{ primematrix[ prof ][ k ].get_opt( ) };

					primematrix[ prof ][ k ].set_opt( primematrix[ prof ][ yindex ].get_opt( ) );
					primematrix[ prof ][ yindex ].set_opt( holder );
				}

				primerank.clear( );
				primerank.generate_ranking( primematrix );

				i = -1;
			}
		}

		else if( ( ( originalrank[ i ].get_yval( ) > originalrank[ i ].get_xval( ) ) == true ) &&
			( ( primerank[ i ].get_yval( ) > primerank[ i ].get_xval( ) ) == false ) ){

			std::vector<int>::size_type distance{ primematrix.begin( )->size( ) };
			std::vector<int>::size_type prof{ 0 };

			std::vector<int>::size_type xindex{ };
			std::vector<int>::size_type yindex{ };

					// Find the profile with the smallest profiles which holds the relation with the least distance between x and y
				for( std::vector<int>::size_type j = 0; j < primematrix.size( ); ++j ){

					std::vector<Options, std::allocator<Options>>::iterator x = std::find( primematrix[ j ].begin( ), primematrix[ j ].end( ), originalrank[ i ].get_optx( ) );
					std::vector<Options, std::allocator<Options>>::iterator y = std::find( primematrix[ j ].begin( ), primematrix[ j ].end( ), originalrank[ i ].get_opty( ) );

					if( x->get_value( ) > y->get_value( ) ){

						if( static_cast< std::vector<int>::size_type >( std::abs( x - y ) ) < distance ){

							xindex = static_cast< std::vector<int>::size_type >( x - primematrix[ j ].begin( ) );
							yindex = static_cast< std::vector<int>::size_type >( y - primematrix[ j ].begin( ) );

							distance = static_cast< std::vector<int>::size_type >( std::abs( x - y ) );

							prof = j;
						}
					}
				}

				if( distance == 1 ){

					std::string holder{ primematrix[ prof ][ xindex ].get_opt( ) };

					primematrix[ prof ][ xindex ].set_opt( primematrix[ prof ][ yindex ].get_opt( ) );
					primematrix[ prof ][ yindex ].set_opt( holder );

					primerank.clear( );
					primerank.generate_ranking( primematrix );

					i = -1;
				}

				// Else, if there are k elements between x and y, put y at x and move x and its subsequents elements one place to the right
				else if( distance > 1 ){

					for( std::vector<int>::size_type k = std::min( xindex, yindex ); k <= std::max( xindex, yindex ); ++k ){

						std::string holder{ primematrix[ prof ][ k ].get_opt( ) };

						primematrix[ prof ][ k ].set_opt( primematrix[ prof ][ yindex ].get_opt( ) );
						primematrix[ prof ][ yindex ].set_opt( holder );
					}

					primerank.clear( );
					primerank.generate_ranking( primematrix );

					i = -1;
				}
			}
	
		else if( ( ( originalrank[ i ].get_yval( ) == originalrank[ i ].get_xval( ) ) == true ) &&
		( ( primerank[ i ].get_yval( ) == primerank[ i ].get_xval( ) ) == false ) ){

			// should not this be if xval > yval?
			//if( primerank[ i ].get_optx( ) > primerank[ i ].get_opty( ) )
			if( primerank[ i ].get_xval( ) > primerank[ i ].get_yval( ) ){

				std::vector<int>::size_type distance{ primematrix.begin( )->size( ) };
				std::vector<int>::size_type prof{ 0 };

				std::vector<int>::size_type xindex{ };
				std::vector<int>::size_type yindex{ };

				// Find the profile with the smallest profiles which holds the relation with the least distance between x and y
				for( std::vector<int>::size_type j = 0; j < primematrix.size( ); ++j ){

					std::vector<Options, std::allocator<Options>>::iterator x = std::find( primematrix[ j ].begin( ), primematrix[ j ].end( ), originalrank[ i ].get_optx( ) );
					std::vector<Options, std::allocator<Options>>::iterator y = std::find( primematrix[ j ].begin( ), primematrix[ j ].end( ), originalrank[ i ].get_opty( ) );

					if( x->get_value( ) > y->get_value( ) ){

						if( static_cast< std::vector<int>::size_type >( std::abs( x - y ) ) < distance ){

							xindex = static_cast< std::vector<int>::size_type >( x - primematrix[ j ].begin( ) );
							yindex = static_cast< std::vector<int>::size_type >( y - primematrix[ j ].begin( ) );

							distance = static_cast< std::vector<int>::size_type >( std::abs( x - y ) );

							prof = j;
						}
					}
				}

				if( distance == 1 ){

					std::string holder{ primematrix[ prof ][ xindex ].get_opt( ) };

					primematrix[ prof ][ xindex ].set_opt( primematrix[ prof ][ yindex ].get_opt( ) );
					primematrix[ prof ][ yindex ].set_opt( holder );

					primerank.clear( );
					primerank.generate_ranking( primematrix );

					i = -1;
				}

				// Else, if there are k elements between x and y, put y at x and move x and its subsequents elements one place to the right
				else if( distance > 1 ){

					// problem here: xindex can be greater than yindex. This loop will not be executed - DEADLOCK - SOLVED
					// second issue: is the move being done correctly? Is the program correctly reassigning options' names? - NOPE
					for( std::vector<int>::size_type k = std::min( xindex, yindex ); k <= std::max( xindex, yindex ); ++k ){

						std::string holder{ primematrix[ prof ][ k ].get_opt( ) };

						primematrix[ prof ][ k ].set_opt( primematrix[ prof ][ yindex ].get_opt( ) );
						primematrix[ prof ][ yindex ].set_opt( holder );
					}

					primerank.clear( );
					primerank.generate_ranking( primematrix );

					i = -1;
				}
			}

			//else if( primerank[ i ].get_optx( ) > primerank[ i ].get_opty( ) )
			else if( primerank[ i ].get_yval( ) > primerank[ i ].get_xval( ) ){

				std::vector<int>::size_type distance{ primematrix.begin( )->size( ) };
				std::vector<int>::size_type prof{ 0 };

				std::vector<int>::size_type xindex{ };
				std::vector<int>::size_type yindex{ };

				// Find the profile with the smallest profiles which holds the relation with the least distance between x and y
				for( std::vector<int>::size_type j = 0; j < primematrix.size( ); ++j ){

					std::vector<Options, std::allocator<Options>>::iterator x = std::find( primematrix[ j ].begin( ), primematrix[ j ].end( ), originalrank[ i ].get_optx( ) );
					std::vector<Options, std::allocator<Options>>::iterator y = std::find( primematrix[ j ].begin( ), primematrix[ j ].end( ), originalrank[ i ].get_opty( ) );

					if( y->get_value( ) > x->get_value( ) ){

						if( static_cast< std::vector<int>::size_type >( std::abs( x - y ) ) < distance ){

							xindex = static_cast< std::vector<int>::size_type >( x - primematrix[ j ].begin( ) );
							yindex = static_cast< std::vector<int>::size_type >( y - primematrix[ j ].begin( ) );

							distance = static_cast< std::vector<int>::size_type >( std::abs( x - y ) );

							prof = j;
						}
					}
				}

				if( distance == 1 ){

					std::string holder{ primematrix[ prof ][ xindex ].get_opt( ) };

					primematrix[ prof ][ xindex ].set_opt( primematrix[ prof ][ yindex ].get_opt( ) );
					primematrix[ prof ][ yindex ].set_opt( holder );

					primerank.clear( );
					primerank.generate_ranking( primematrix );

					i = -1;
				}

				// Else, if there are k elements between x and y, put y at x and move x and its subsequents elements one place to the right
				else if( distance > 1 ){

					for( std::vector<int>::size_type k = std::min( xindex, yindex ); k <= std::max( xindex, yindex ); ++k ){

						std::string holder{ primematrix[ prof ][ k ].get_opt( ) };

						primematrix[ prof ][ k ].set_opt( primematrix[ prof ][ yindex ].get_opt( ) );
						primematrix[ prof ][ yindex ].set_opt( holder );
					}

					primerank.clear( );
					primerank.generate_ranking( primematrix );

					i = -1;
				}
			}
		}
	}

	return primematrix;
}

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

// This is all about relative positioning of alternatives. If, for any two profiles p and p', the rela
// tive positions of its alternatives are the same, then, f( p ) and f( p' ) must keep their relative
// positions equal
bool SCT::Irrelevant_Alternatives::operator( )( SCT::Procedure& procedure ){

	// Sorting here will enforce correctness on the matrix comparison conditional, i.e., they will
	// only be equal when its alternatives appear in the same order
	matrix.merge_sort_by_value( );

	Rank original( matrix );
	original.order_ranking( );

	Preferencematrix primematrix = generate_prime_profile( matrix );
	primematrix.merge_sort_by_value( );

	Rank primerank( primematrix );
	primerank.order_ranking( );
	
	if( matrix != primematrix ){

		if( rank_relations( original, primerank ) == true ){

			Profile winnerset = procedure( original );
			winnerset.sort_by_value( );

			Profile primeset = procedure( primerank );
			primeset.sort_by_value( );

			// Especial attention here. What one wants from this? Not the same values, but same ORDER, i.e.,
			// for i from 0 to set.size, winnerset[ i ] == primeset[ i ]. DEBUG THIS
			if( winnerset == primeset ){

				return true;
			}

			else{

				return false;
			}
		}

		else{

			std::cerr << "Ma boi, you really have a problem here.\n";
		}
	}

	else if( matrix == primematrix ){

		return true;
	}
}

// Finds an agent that, whenever ONLY HER prefers x to y, the social order becomes xPy
// If is that the case that another person also prefers x to y, then the clause is not
// valid. Inform which agent is the dictator!
// To do so, define operator+= first
bool SCT::Non_Dictatorship::operator( )( SCT::Procedure& procedure ){



	return false;
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

			// is this supposed to mean n * ( n - 1 ) / 2? Damn, boi, this is shitty
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

	//std::cout << "Problem line 1\n";

	if( pareto( procedure ) == true ){

		if( irrelevant( procedure ) == true ){

			// then, according to arrow, non dictator must be false, i.e., there must be a dictator
			if( dictator( procedure ) == false ){

				// theorem complete and etc.
				return true;
			}

			else{

				return false;
			}
		}
	}
}
