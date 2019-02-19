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
PairsOfOpts& PairsOfOpts::operator=( const PairsOfOpts& copy ){

    xpref = copy.xpref;
    ypref = copy.ypref;

    return *this;
}

/// Non-member helpers

// Generates all possible combination of pairs of options, without repetitions
std::vector<PairsOfOpts> pair_generation( Population& listofagents ){

    PairsOfOpts compairs{ };

    std::vector<PairsOfOpts> paircomp{ };

    std::vector<int>::size_type randagt = static_cast<std::vector<int>::size_type>( rand( ) ) % listofagents.size( );

    std::vector<int>::size_type listsize = listofagents.size( );
    std::vector<int>::size_type prefsize = listofagents[ static_cast<std::vector<int>::size_type>( rand( ) ) % listsize ].get_preferences( ).size( );

    // gets all possible combination of pairs, including repeated pairs
    for( std::vector<int>::size_type i = 0; i < prefsize; ++i ){

        compairs.xpref = listofagents[ randagt ][ i ];

        for( std::vector<int>::size_type j = i + 1; j < prefsize; ++j ){

            if( j != i ){

                compairs.ypref = listofagents[ randagt ][ j ];

                paircomp.push_back( compairs );
            }
        }
    }

    // returns all combinations without repetitions
    return paircomp;
}
