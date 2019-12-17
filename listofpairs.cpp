#include "listofpairs.hpp"

/// Constructors & Destructor

ListOfPairs::ListOfPairs( ){ pairs = { }; }

ListOfPairs::ListOfPairs( Population& population ){ pair_generation( population ); }

ListOfPairs::ListOfPairs( Preferencematrix& matrix ){ pair_generation( matrix ); }

ListOfPairs::~ListOfPairs( ){ clear( ); }

/// Setters

/// Getters

/// Operators

ListOfPairs ListOfPairs::operator=( const ListOfPairs& copy ){

	pairs = copy.pairs;

    return *this;
}

ListOfPairs ListOfPairs::operator=( ListOfPairs&& copy ){

	pairs = std::move( copy.pairs );

	copy.clear( );

	return *this;
}

/// Helpers

void ListOfPairs::pair_generation( Profile& profile ){

	clear( );

	std::random_device rd;

	std::mt19937 mt( rd( ) );

	std::uniform_int_distribution<std::vector<int>::size_type> index( 0, ( profile.size( ) - 1 ) );

	PairsOfOpts compairs{ };

	//std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );
	std::vector<int>::size_type randopt = index( mt );

	std::vector<int>::size_type prefsize = profile.size( );

	// gets all possible combination of pairs, including repeated pairs
	for( std::vector<int>::size_type i = 0; i < prefsize; ++i ){

		//compairs.xpref = listofagents[ randagt ][ i ];
		compairs.xpref = profile[ randopt ];

		for( std::vector<int>::size_type j = i + 1; j < prefsize; ++j ){

			if( j != i ){

				//compairs.ypref = listofagents[ randagt ][ j ];
				compairs.ypref = profile[ randopt ];

				pairs.push_back( compairs );
			}
		}
	}
}

void ListOfPairs::pair_generation( Population& population ){

    clear( );

    std::random_device rd;

    std::mt19937 mt( rd( ) );

    std::uniform_int_distribution<std::vector<int>::size_type> index( 0, ( population.size( ) - 1 ) );

    PairsOfOpts compairs{ };

    //std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );
    std::vector<int>::size_type randagt = index( mt );

    std::vector<int>::size_type prefsize = population.begin( ) -> get_preferences( ).size( );

    // gets all possible combination of pairs, including repeated pairs
    for( std::vector<int>::size_type i = 0; i < prefsize; ++i ){

        //compairs.xpref = listofagents[ randagt ][ i ];
        compairs.xpref = population[ randagt ][ i ];

        for( std::vector<int>::size_type j = i + 1; j < prefsize; ++j ){

            if( j != i ){

                //compairs.ypref = listofagents[ randagt ][ j ];
                compairs.ypref = population[ randagt ][ j ];

                pairs.push_back( compairs );
            }
        }
    }

    // returns all combinations without repetitions
    //return pairs;
    //return *this;
}

void ListOfPairs::pair_generation( Preferencematrix& matrix ){

    clear( );

    std::random_device rd;

    //std::mt19937_64 mt( rd( ) );
    std::mt19937 mt( rd( ) );

    std::uniform_int_distribution<std::vector<int>::size_type> index( 0, ( matrix.size( ) - 1 ) );

    PairsOfOpts compairs{ };

    //std::vector<int>::size_type randrow = static_cast<std::vector<int>::size_type>( rand( ) ) % mtx.size( );
    std::vector<int>::size_type randrow = index( mt );

    //std::vector<int>::size_type listsize = mtx.size( );
    std::vector<int>::size_type prefsize = matrix.begin( ) -> get_alternatives( ).size( );

    // gets all possible combination of pairs, including repeated pairs
    for( std::vector<int>::size_type i = 0; i < prefsize; ++i ){

        //compairs.xpref = mtx[ randrow ][ i ];
        compairs.xpref = matrix[ randrow ][ i ];

        for( std::vector<int>::size_type j = i + 1; j < prefsize; ++j ){

            if( j != i ){

                // problem here - solved
                //compairs.ypref = mtx[ randrow ][ j ];
                compairs.ypref = matrix[ randrow ][ j ];

                pairs.push_back( compairs );
            }
        }
    }

    // returns all combinations without repetitions
    //return pairs;
    //return *this;
}

void ListOfPairs::clear( ){

    if( !empty( ) ){

        pairs.clear( );

        std::vector<PairsOfOpts>( ).swap( pairs );
    }

    else

        return;
}

void ListOfPairs::erase( const std::vector<int>::size_type index ){

    if( !empty( ) )

        pairs.erase( std::remove( begin( ), end( ), pairs[ index ] ), pairs.end( ) );

    else

        return;
}
void ListOfPairs::erase( const PairsOfOpts& pair ){

    if( !empty( ) )

        pairs.erase( std::remove( begin( ), end( ), pair ), pairs.end( ) );

    else

        return;
}

/// Non-member helpers

std::ostream& operator<<( std::ostream& os, ListOfPairs& pairs ){

    for( std::vector<int>::size_type i = 0; i < pairs.size( ); ++i ){

        os << pairs[ i ].xpref << ", " << pairs[ i ].ypref << "\n";
    }

    return os;
}
