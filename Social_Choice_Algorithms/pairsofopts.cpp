#include "pairsofopts.hpp"

/// Constructors & Destructor

// Default constructor
PairsOfOpts::PairsOfOpts( ){

    xpref = { };
    ypref = { };
}

// Copy constructor
PairsOfOpts::PairsOfOpts( const PairsOfOpts& copy ){

    xpref = copy.xpref;
    ypref = copy.ypref;
}

/// Operators

// Overloaded assignment operator
PairsOfOpts& PairsOfOpts::operator=( PairsOfOpts copy ){

	std::swap( *this, copy );

    return *this;
}

/// Non-member helpers

// Generates all possible combination of pairs of options, without repetitions
/*std::vector<PairsOfOpts> pair_generation( Population& listofagents ){

    std::random_device rd;

    std::mt19937 mt( rd( ) );

    std::uniform_int_distribution<std::vector<int>::size_type> index( 0, ( listofagents.size( ) - 1 ) );

    PairsOfOpts compairs{ };

    std::vector<PairsOfOpts> paircomp{ };

    //std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );
    std::vector<int>::size_type randagt = index( mt );

    std::vector<int>::size_type prefsize = listofagents.begin( ) -> get_preferences( ).size( );

    // gets all possible combination of pairs, including repeated pairs
    for( std::vector<int>::size_type i = 0; i < prefsize; ++i ){

        //compairs.xpref = listofagents[ randagt ][ i ];
        compairs.xpref = listofagents[ randagt ][ i ];

        for( std::vector<int>::size_type j = i + 1; j < prefsize; ++j ){

            if( j != i ){

                //compairs.ypref = listofagents[ randagt ][ j ];
                compairs.ypref = listofagents[ randagt ][ j ];

                paircomp.push_back( compairs );
            }
        }
    }

    // returns all combinations without repetitions
    return paircomp;
}

std::vector<PairsOfOpts> pair_generation( Preferencematrix& mtx ){

    std::random_device rd;

    //std::mt19937_64 mt( rd( ) );
    std::mt19937 mt( rd( ) );

    std::uniform_int_distribution<std::vector<int>::size_type> index( 0, ( mtx.size( ) - 1 ) );

    PairsOfOpts compairs{ };

    std::vector<PairsOfOpts> paircomp{ };

    //std::vector<int>::size_type randrow = static_cast<std::vector<int>::size_type>( rand( ) ) % mtx.size( );
    std::vector<int>::size_type randrow = index( mt );

    //std::vector<int>::size_type listsize = mtx.size( );
    std::vector<int>::size_type prefsize = mtx.begin( ) -> get_alternatives( ).size( );

    // gets all possible combination of pairs, including repeated pairs
    for( std::vector<int>::size_type i = 0; i < prefsize; ++i ){

        //compairs.xpref = mtx[ randrow ][ i ];
        compairs.xpref = mtx[ randrow ][ i ];

        for( std::vector<int>::size_type j = i + 1; j < prefsize; ++j ){

            if( j != i ){

                // problem here - solved
                //compairs.ypref = mtx[ randrow ][ j ];
                compairs.ypref = mtx[ randrow ][ j ];

                paircomp.push_back( compairs );
            }
        }
    }

    // returns all combinations without repetitions
    return paircomp;
}*/
