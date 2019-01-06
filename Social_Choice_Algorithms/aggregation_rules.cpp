#include "aggregation_rules.hpp"

// ATTENTION: every procedure should have the same return type

// Return: a vector composed only by the elements that satisfies the conditions
// OR a vector with every element flagged true if they satisfy, or false if
// they do not? - refer to BIG QUESTION

/// Majority Rules


std::vector<Options> qualified_majority_rule( Graph& graph ){

    std::vector<Options> winnerset{ };

    for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

        if( graph[ i ].get_preferences( ).size( ) >= ( graph.size( ) / 2 ) )

            winnerset.push_back( Options( graph[ i ].get_id( ), true, static_cast<int>( graph[ i ].get_preferences( ).size( ) ) ) );
    }

    auto order = [ ]( Options& left, Options& right ){

        return left.get_value( ) > right.get_value( );
    };

    std::sort( winnerset.begin( ), winnerset.end( ), order );

    return winnerset;
}

std::vector<Options> qualified_majority_rule( Rank& rank ){


}

// Majority rule using Pairwise Rank
std::vector<Options> simple_majority_rule( Rank rank ){


}


/// Counting Rules
std::vector<Options> borda_count( Rank rank ){

    std::vector<Options> winnerset{ };

    return winnerset;
}

std::vector<Options> borda_count( Graph& graph ){

    std::vector<Options> winnerset{ };

    return winnerset;
}
