#include "sctrank.hpp"
#include "helper_functions.cpp"

/// Constructors & Destructor

// Default constructor
Rank::Rank( ){ ranking = { }; }

// Parameterized constructor
Rank::Rank( std::vector<PairWiseRank> ordering ){ ranking = ordering; }

// Copy constructor
Rank::Rank( const Rank& copy ){ ranking = copy.ranking; }

/// Setters

void Rank::set_rank( PairWiseRank pair ){ ranking.push_back( pair ); }

void Rank::set_rank( std::vector<PairWiseRank> order ){ ranking = order; }

/* Ranks alternatives. The ranking has a form of a vector of quintuples ( x, y, xval, yval, ival ), where
 * x and y are the alternatives, and the vals represent how many agents prefer one over the other. ival
 * represents indifference. The ranking operates in accord to how agents ranks pairs of alternatives
 */
void Rank::generate_ranking( Population& listofagents ){

    // Holder for a pair of options
    PairsOfOpts compairs{ };

    std::vector<PairsOfOpts> ordering = pair_generation( listofagents );

    // quintuples ( x, y, xval, yval, ival ) and then map occurrences into val
    PairWiseRank paircomp{ };

    //std::vector<PairWiseRank> ranking{ };

    std::vector<int>::size_type ordersize = ordering.size( );
    std::vector<int>::size_type listsize = listofagents.size( );
    std::vector<int>::size_type prefsize = listofagents[ static_cast<std::vector<int>::size_type>( rand( ) ) % listsize ].get_preferences( ).size( );

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

    // returns a vector of quintuples
    //return ranking;
}

/// Getters

/// Operators

Rank& Rank::operator=( const Rank& copy ){

    ranking = copy.ranking;

    return *this;
}

PairWiseRank& Rank::operator[ ]( const std::vector<int>::size_type index ){

    if( !ranking.empty( ) ){

        if( ( static_cast<int>( index ) >= 0 ) && ( index < ranking.size( ) ) )

            return ranking[ index  ];

        else{

            std::cerr << "Invalid index. Please, enter another value: ";

            std::vector<int>::size_type newindex{ };

            std::cin >> newindex;

            return operator[ ]( newindex );
        }
    }

    else{

        std::cerr << "Ranking is empty!. Creating a default ordered pair instead.\n";

        ranking.resize( 1 );

        return *ranking.begin( );
    }
}

/// Helpers

bool Rank::empty( ){

	if( ranking.empty( ) )

		return true;

	else

		return false;
}
