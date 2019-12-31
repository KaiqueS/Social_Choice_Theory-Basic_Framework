#include "sctrank.hpp"
//include "listofpairs.hpp"
//#include "pairsofopts.hpp" -> Used to cause multiple definition problem if not included here

/// Constructors & Destructor

// Default constructor
Rank::Rank( ){ ranking = { }; }

Rank::Rank( Population& population ){

    generate_ranking( population );
    order_ranking( );
}

Rank::Rank( Preferencematrix& matrix ){

    generate_ranking( matrix );
    order_ranking( );
}

// Copy constructor
Rank::Rank( const Rank& copy ){ ranking = copy.ranking; }

// Move constructor
Rank::Rank( Rank&& rank ){

	ranking = std::move( rank.ranking );

	rank.clear( );
}

// Destructor. Clears RANKING from memory
Rank::~Rank( ){ clear( ); }

/// Setters

// Inserts a PairWiseRank at the end of RANKING
void Rank::set_rank( PairWiseRank pair ){

    ranking.push_back( pair );

    // Added this later
    order_ranking( );
}

// Sets RANKING to order
void Rank::set_rank( std::vector<PairWiseRank> order ){

    ranking = order;

    // Added this later
    order_ranking( );
}

// Test this later - DEBUG THIS
// The purpose here is to be able to check a profile's transitivity
void Rank::generate_ranking( Profile& profile ){

	// Holder for a pair of options
	PairsOfOpts compairs{ };

	// Generates all possible combinations of pairs, without repetitions
	//std::vector<PairsOfOpts> ordering = pair_generation( mtx );
	//ListOfPairs ordering = ListOfPairs( ).pair_generation( mtx );
	//ListOfPairs ordering( mtx );
	ListOfPairs ordering{ };

	ordering.pair_generation( profile );

	// quintuples ( x, y, xval, yval, ival ) and then map occurrences into val
	PairWiseRank paircomp{ };

	//std::vector<PairWiseRank> ranking{ };

	// Number of all possible combinations of pairs, without repetitions
	std::vector<int>::size_type ordersize = ordering.size( );

	// Number of profiles
	std::vector<int>::size_type listsize = profile.size( );

	// Number of options in each profile
	std::vector<int>::size_type prefsize = profile.size( );

	// Checks how a pair ( x, y ) is ranked for each agent
	for( std::vector<int>::size_type i = 0; i < ordersize; ++i ){

		// Holds both alternatives that will be checked
		compairs.xpref = ordering[ i ].xpref;
		compairs.ypref = ordering[ i ].ypref;

		for( std::vector<int>::size_type j = 0; j < listsize; ++j ){

			for( std::vector<int>::size_type k = 0; k < prefsize; ++k ){

				// Search for x in agent's preferences
				if( profile[ j ].get_opt( ) == compairs.xpref.get_opt( ) )

					paircomp.set_optx( profile[ k ] );

				// Search for y in agent's preferences -> ADDED: else
				else if( profile[ j ].get_opt( ) == compairs.ypref.get_opt( ) )

					paircomp.set_opty( profile[ k ] );
			}

			// Compares x and y values. If x > y, increment xval
			if( paircomp.get_optx( ).get_value( ) > paircomp.get_opty( ).get_value( ) )

				paircomp.incrementx( );

			// Else, if x < y, increment yval
			else if( paircomp.get_optx( ).get_value( ) < paircomp.get_opty( ).get_value( ) )

				paircomp.incrementy( );

			// Else, if x == y, increment ival
			else if( paircomp.get_optx( ).get_value( ) == paircomp.get_opty( ).get_value( ) )

				paircomp.incrementi( );
		}

		// Stores the ranked tuple
		ranking.push_back( paircomp );

		// Resets the tuple for a new ranking
		// paircomp = { };
		paircomp = PairWiseRank( );
	}

	// Added this later
	order_ranking( );
}

/* Ranks alternatives. The ranking has a form of quintuples ( x, y, xval, yval, ival ), where
 * x and y are the alternatives, and the vals represent how many agents prefer one over the
 * other. E.g.: xval > yval means that x is preferred to y
 */
void Rank::generate_ranking( Population& listofagents ){

    // Holder for a pair of options
    PairsOfOpts compairs{ };

    // Generates all possible combinations of pairs, without repetitions
    //std::vector<PairsOfOpts> ordering = pair_generation( listofagents );
    //ListOfPairs ordering = ListOfPairs( ).pair_generation( listofagents );
    ListOfPairs ordering{ };

    ordering.pair_generation( listofagents );

    // quintuples ( x, y, xval, yval, ival ) and then map occurrences into val
    PairWiseRank paircomp{ };

    //std::vector<PairWiseRank> ranking{ };

    // Number of all possible combinations of pairs, without repetitions
    std::vector<int>::size_type ordersize = ordering.size( );

    // Number of profiles
    std::vector<int>::size_type listsize = listofagents.size( );

    // Number of options in each profile
    //std::vector<int>::size_type prefsize = listofagents[ static_cast<std::vector<int>::size_type>( rand( ) ) % listsize ].get_preferences( ).size( );
    std::vector<int>::size_type prefsize = listofagents.begin( ) -> get_preferences( ).size( );

    // Checks how a pair ( x, y ) is ranked for each agent
    for( std::vector<int>::size_type i = 0; i < ordersize; ++i ){

        // Holds both alternatives that will be checked
        compairs.xpref = ordering[ i ].xpref;
        compairs.ypref = ordering[ i ].ypref;

        for( std::vector<int>::size_type j = 0; j < listsize; ++j ){

            for( std::vector<int>::size_type k = 0; k < prefsize; ++k ){

                // Search for x in agent's preferences
                if( listofagents[ j ][ k ].get_opt( ) == compairs.xpref.get_opt( ) )

                    paircomp.set_optx( listofagents[ j ][ k ] );

                // Search for y in agent's preferences -> ADDED: else
                else if( listofagents[ j ][ k ].get_opt( ) == compairs.ypref.get_opt( ) )

                    paircomp.set_opty( listofagents[ j ][ k ] );
            }

            // Compares x and y values. If x > y, increment xval
            if( paircomp.get_optx( ).get_value( ) > paircomp.get_opty( ).get_value( ) )

                paircomp.incrementx( );

            // Else, if x < y, increment yval
            else if( paircomp.get_optx( ).get_value( ) < paircomp.get_opty( ).get_value( ) )

                paircomp.incrementy( );

            // Else, if x == y, increment ival
            else if( paircomp.get_optx( ).get_value( ) == paircomp.get_opty( ).get_value( ) )

                paircomp.incrementi( );
        }

        // Stores the ranked tuple
        ranking.push_back( paircomp );

        // Resets the tuple for a new ranking
        paircomp = { };
    }

    // Added this later
    order_ranking( );
}

void Rank::generate_ranking( Preferencematrix& mtx ){

    // Holder for a pair of options
    PairsOfOpts compairs{ };

    // Generates all possible combinations of pairs, without repetitions
    //std::vector<PairsOfOpts> ordering = pair_generation( mtx );
    //ListOfPairs ordering = ListOfPairs( ).pair_generation( mtx );
    //ListOfPairs ordering( mtx );
    ListOfPairs ordering{ };

    ordering.pair_generation( mtx );

    // quintuples ( x, y, xval, yval, ival ) and then map occurrences into val
    PairWiseRank paircomp{ };

    //std::vector<PairWiseRank> ranking{ };

    // Number of all possible combinations of pairs, without repetitions
    std::vector<int>::size_type ordersize = ordering.size( );

    // Number of profiles
    std::vector<int>::size_type listsize = mtx.size( );

    // Number of options in each profile. Remember: profiles have the same size
    std::vector<int>::size_type prefsize = mtx.begin( ) -> get_alternatives( ).size( );

    // Checks how a pair ( x, y ) is ranked for each agent
    for( std::vector<int>::size_type i = 0; i < ordersize; ++i ){

        // Holds both alternatives that will be checked
        compairs.xpref = ordering[ i ].xpref;
        compairs.ypref = ordering[ i ].ypref;

        for( std::vector<int>::size_type j = 0; j < listsize; ++j ){

            for( std::vector<int>::size_type k = 0; k < prefsize; ++k ){

                // Search for x in agent's preferences
                if( mtx[ j ][ k ].get_opt( ) == compairs.xpref.get_opt( ) )

                    paircomp.set_optx( mtx[ j ][ k ] );

                // Search for y in agent's preferences -> ADDED: else
                else if( mtx[ j ][ k ].get_opt( ) == compairs.ypref.get_opt( ) )

                    paircomp.set_opty( mtx[ j ][ k ] );
            }

            // Compares x and y values. If x > y, increment xval
            if( paircomp.get_optx( ).get_value( ) > paircomp.get_opty( ).get_value( ) )

                paircomp.incrementx( );

            // Else, if x < y, increment yval
            else if( paircomp.get_optx( ).get_value( ) < paircomp.get_opty( ).get_value( ) )

                paircomp.incrementy( );

            // Else, if x == y, increment ival
            else if( paircomp.get_optx( ).get_value( ) == paircomp.get_opty( ).get_value( ) )

                paircomp.incrementi( );
        }

        // Stores the ranked tuple
        ranking.push_back( paircomp );

        // Resets the tuple for a new ranking
        // paircomp = { };
        paircomp = PairWiseRank( );
    }

    // Added this later
    order_ranking( );
}

/// Getters

/// Operators

// Overloaded assignment operator
Rank& Rank::operator=( const Rank& copy ){

	ranking = copy.ranking;

    return *this;
}

Rank& Rank::operator=( Rank&& copy ){

	ranking = std::move( copy.ranking );

	copy.clear( );

	return *this;
}

// Overloaded subscript operator. Returns a quintuple PairWiseRank of the form
// ( optx, opty, xval, yval, ival )
PairWiseRank& Rank::operator[ ]( const std::vector<int>::size_type index ){

    // Checks if RANKING is not empty
    if( !ranking.empty( ) ){

        // If it is not, and if index in within the range of RANKING
        if( ( static_cast<int>( index ) >= 0 ) && ( index < ranking.size( ) ) )

            // return PairWiseRank[ index ]
            return ranking[ index  ];

        // Else, if index is invalid
        else{

            std::cerr << "Invalid index. Please, enter another value between 0 <= x < " << ranking.size( ) << ": ";

            std::vector<int>::size_type newindex{ };

            // Get a new index
            std::cin >> newindex;

            return operator[ ]( newindex );
        }
    }

    // If RANKING is empty
    else{

        std::cerr << "Ranking is empty!. Creating a default ordered pair instead.\n\n";

        ranking.resize( 1 );

        // Return a default PairWiseRank
        return *ranking.begin( );
    }
}

/// Helpers

// Checks for transitivity. Returns true if, for any x, y, z, whenever ( x, y )
// and ( y, z ), then ( x, z ). With Rank, this means that, whenever xval > yval,
// and yval > zval, then xval > zval
bool Rank::is_transitive( ){

	/*class Transitivity{

	public:

		Transitivity( );
		~Transitivity( ){ }

		PairWiseRank get_left( ){ return left; }
		PairWiseRank get_right( ){ return right; }

	private:

		PairWiseRank left{ };
		PairWiseRank right{ };
	};*/

	for( std::vector<int>::size_type i = 0; i < ranking.size( ); ++i ){

		for( std::vector<int>::size_type j = i + 1; j < ranking.size( ); ++j ){

			if( ranking[ j ].get_optx( ) == ranking[ i ].get_opty( ) ){

				// maybe i should let k = 0?
				for( std::vector<int>::size_type k = i + 1; k < ranking.size( ); ++k ){

					if( ( ranking[ k ].get_optx( ) == ranking[ i ].get_optx( ) ) &&
						( ranking[ k ].get_opty( ) == ranking[ j ].get_opty( ) ) ){

						if( ( ranking[ i ].get_xval( ) > ranking[ i ].get_yval( ) ) &&
							( ranking[ j ].get_xval( ) > ranking[ j ].get_yval( ) ) &&
							( ranking[ k ].get_xval( ) > ranking[ k ].get_yval( ) ) ){

							std::cout << ranking[ i ] << "\n" << ranking[ j ] << "\n" << ranking[ k ] << "\t is transitive.\n"; // debug only
						}

						else{

							std::cout << ranking[ i ] << "\n" << ranking[ j ] << "\n" << ranking[ k ] << "\t is not transitive.\n"; // debug only

							return false;
						}
					}

					else

						continue;
				}
			}

			else

				continue;
		}
	}

	return true;
}

// Checks if RANKING is empty. Returns true if it is
bool Rank::empty( ){

	if( ranking.empty( ) )

		return true;

	else

		return false;
}

void Rank::clear( ){

	ranking.clear( );

	std::vector<PairWiseRank>( ).swap( ranking );
}

// Check for emptiness
void Rank::order_ranking( ){

	if( !ranking.empty( ) ){

		for( std::vector<int>::size_type i = 0; i < ranking.size( ); ++i ){

			if( ranking[ i ].get_optx( ).get_opt( ) > ranking[ i ].get_opty( ).get_opt( ) ){

				Options x = ranking[ i ].get_optx( );
				x.set_value( ranking[ i ].get_xval( ) );

				ranking[ i ].set_optx( ranking[ i ].get_opty( ) );
				ranking[ i ].set_xval( ranking[ i ].get_yval( ) );

				ranking[ i ].set_opty( x );
				ranking[ i ].set_yval( x.get_value( ) );
			}
		}

		for( std::vector<int>::size_type i = 0; i < ranking.size( ); ++i ){

			for( std::vector<int>::size_type j = i + 1; j < ranking.size( ); ++j ){

				if( ranking[ i ].get_optx( ).get_opt( ) > ranking[ j ].get_optx( ).get_opt( ) ){

					std::swap( ranking[ i ], ranking[ j ] );
				}

				else if( ranking[ i ].get_optx( ).get_opt( ) == ranking[ j ].get_optx( ).get_opt( ) ){

					if( ranking[ i ].get_opty( ).get_opt( ) > ranking[ j ].get_opty( ).get_opt( ) ){

						std::swap( ranking[ i ], ranking[ j ] );
					}
				}
			}
		}
	}

	// Think about this later
	else{

		std::cerr << "Cannot order an empty Rank.\n";

		return;
	}
}

/// Non-member helpers

// How to reconstruct a list of n elements from a list of pairs of elements? Do I really need to do this?
// If I have a SCTRank, I must also have a PreferenceMatrix or a Population, or even a Profile
// Initializes a Profile with options in RANK, withouth repetition. // THIS ALGORITHM IS DUMB DUMB DUMB DUMB DUMB
void initialize_opts( Rank& rank, Profile& profile ){

    // Get all possible options
    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

        profile.push_back( Options( rank[ i ].get_optx( ).get_opt( ), false, 0 ) );
        profile.push_back( Options( rank[ i ].get_opty( ).get_opt( ), false, 0 ) );
    }

    // Remove repeated options // The problem is obviously here: iterating over an index with size as range
	                           // while size is being modified because elements are being erased	
    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){ // The problem is i as an index. Maybe I should make i = 0 whenever j completes a full loop

        for( std::vector<int>::size_type j = 0; j < profile.size( ); ++j ){

			if( i < profile.size( ) ){

				if( i != j ){

					if( profile[ i ].get_opt( ) == profile[ j ].get_opt( ) ){

						std::cout << profile[ j ] << " index number " << j << " size " << profile.size( ) << "\n";

						profile.erase( j );
					}
				}
			}

			else{

				i = 0;
			}
        }
    }

	std::cout << profile << "\n profile size is " << profile.size( ) << "\n";
}

// Makes a generic social order, sorted in descending order - I really think that a social order
// should be generated from a procedure
Profile make_social_order( Profile& profile, Rank& rank ){

    // Holder for resulting social order
    Profile orderedrank{ profile };

    for( std::vector<int>::size_type i = 0; i < orderedrank.size( ); ++i ){

        orderedrank[ i ].set_value( 0 );
    }

    // Gets every existing option, without repetition
    // Instead of reconstructing a profile from a rank, just use the profile or matrix
    // used to build the rank itself
    //initialize_opts( rank, orderedrank ); // PROBLEM HERE

    // Check for emptyness - I really should make a exception class to handle this
    if( !orderedrank.empty( ) )

        // get every available option in RANK
        for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

            // get every possible option in ORDEREDRANK
            for( std::vector<int>::size_type j = 0; j < orderedrank.size( ); ++j ){

                // checks if the ORDEREDRANK[ j ] equals RANK[ i ]'s optx
                if( rank[ i ].get_optx( ).get_opt( ) == orderedrank[ j ].get_opt( ) ){

                    // Checks which option beats the other
                    if( rank[ i ].get_xval( ) > rank[ i ].get_yval( ) )

                        // If the option being considered beats its adversary, increment the former
                        ++orderedrank[ j ];
                }

                // checks if the ORDEREDRANK[ j ] equals RANK[ i ]'s opty
                else if( rank[ i ].get_opty( ).get_opt( ) == orderedrank[ j ].get_opt( ) ){

                    // If it is, check if opty beats optx
                    if( rank[ i ].get_xval( ) < rank[ i ].get_yval( ) )

                        // Increment it
                        ++orderedrank[ j ];
                }
            }
        }

    /*auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( orderedrank.begin( ), orderedrank.end( ), order );*/

    // order vector from greatest to smallest, according to the value
    orderedrank.value_merge_sort( 0, orderedrank.size( ) - 1 );

    // Return sorted profile
    return orderedrank;
}

/// Non-member Helpers

std::ostream& operator<<( std::ostream& os, Rank& rank ){

    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i )

        os << rank[ i ] << "\n";

    os << "\n";

    return os;
}

bool rank_relations( Rank& left, Rank& right ){

	for( std::vector<int>::size_type i = 0; i < left.size( ); ++i ){

		if( relation_comparison( left[ i ], right[ i ] ) == false )

			return false;

		else

			continue;
	}

	return true;
}
