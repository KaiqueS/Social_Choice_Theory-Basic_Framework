#include "sctrank.hpp"
#include "helper_functions.cpp"

/// Constructors & Destructor

// Default constructor
Rank::Rank( ){ ranking = { }; }

// Copy constructor
Rank::Rank( const Rank& copy ){ ranking = copy.ranking; }

// Destructor. Clears RANKING from memory
Rank::~Rank( ){

    clear( );

    std::vector<PairWiseRank>( ).swap( ranking );
}

/// Setters

// Inserts a PairWiseRank at the end of RANKING
void Rank::set_rank( PairWiseRank pair ){ ranking.push_back( pair ); }

// Sets RANKING to order
void Rank::set_rank( std::vector<PairWiseRank> order ){ ranking = order; }

/* Ranks alternatives. The ranking has a form of a vector of quintuples ( x, y, xval, yval, ival ), where
 * x and y are the alternatives, and the vals represent how many agents prefer one over the other. ival
 * represents indifference. The ranking operates in accord to how agents ranks pairs of alternatives */
void Rank::generate_ranking( Population& listofagents ){

    // Holder for a pair of options
    PairsOfOpts compairs{ };

    // Generates all possible combinations of pairs, without repetitions
    std::vector<PairsOfOpts> ordering = pair_generation( listofagents );

    // quintuples ( x, y, xval, yval, ival ) and then map occurrences into val
    PairWiseRank paircomp{ };

    //std::vector<PairWiseRank> ranking{ };

    // Number of all possible combinations of pairs, without repetitions
    std::vector<int>::size_type ordersize = ordering.size( );

    // Number of profiles
    std::vector<int>::size_type listsize = listofagents.size( );

    // Number of options in each profile
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
}

void Rank::generate_ranking( Preferencematrix& mtx ){

    // Holder for a pair of options
    PairsOfOpts compairs{ };

    // Generates all possible combinations of pairs, without repetitions
    std::vector<PairsOfOpts> ordering = pair_generation( mtx );

    // quintuples ( x, y, xval, yval, ival ) and then map occurrences into val
    PairWiseRank paircomp{ };

    //std::vector<PairWiseRank> ranking{ };

    // Number of all possible combinations of pairs, without repetitions
    std::vector<int>::size_type ordersize = ordering.size( );

    // Number of profiles
    std::vector<int>::size_type listsize = mtx.size( );

    // Number of options in each profile
    //std::vector<int>::size_type prefsize = listofagents[ static_cast<std::vector<int>::size_type>( rand( ) ) % listsize ].get_preferences( ).size( );
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
        paircomp = { };
    }
}

/// Getters

/// Operators

// Overloaded assignment operator
Rank& Rank::operator=( const Rank& copy ){

    ranking = copy.ranking;

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

            std::cerr << "Invalid index. Please, enter another value: ";

            std::vector<int>::size_type newindex{ };

            // Get a new index
            std::cin >> newindex;

            return operator[ ]( newindex );
        }
    }

    // If RANKING is empty
    else{

        std::cerr << "Ranking is empty!. Creating a default ordered pair instead.\n";

        ranking.resize( 1 );

        // Return a default PairWiseRank
        return *ranking.begin( );
    }
}

/// Helpers

// Checks if RANKING is empty. Returns true if it is
bool Rank::empty( ){

	if( ranking.empty( ) )

		return true;

	else

		return false;
}

// Initializes a Profile with options in RANK, withouth repetition.
void initialize_opts( Rank& rank, Profile& profile ){

    // Get all possible options
    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

        profile.push_back( Options( rank[ i ].get_optx( ).get_opt( ), false, 0 ) );
        profile.push_back( Options( rank[ i ].get_opty( ).get_opt( ), false, 0 ) );
    }

    // Remove repeated options
    for( std::vector<int>::size_type i = 0; i < profile.size( ); ++i ){

        for( std::vector<int>::size_type j = 0; j < profile.size( ); ++j ){

            if( i != j ){

                if( profile[ i ].get_opt( ) == profile[ j ].get_opt( ) ){

                    profile.erase( static_cast<int>( j ) );
                }
            }
        }
    }
}

// Makes a generic social order, sorted in descending order
Profile make_social_order( Rank& rank ){

    // Holder for resulting social order
    Profile orderedrank{ };

    // Gets every existing option
    initialize_opts( rank, orderedrank );

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

    // Returns best ranked option
    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    // order vector from greatest to smallest, according to the value
    std::sort( orderedrank.begin( ), orderedrank.end( ), order );

    // Return sorted profile
    return orderedrank;
}

/// Non-member Helpers

bool operator==( Rank& left, Rank& right ){

    if( left.get_rank( ) == right.get_rank( ) )

        return true;

    else

        return false;
}

bool operator!=( Rank& left, Rank& right ){

    if( left.get_rank( ) == right.get_rank( ) )

        return false;

    else

        return true;
}
