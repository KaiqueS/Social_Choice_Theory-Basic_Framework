#include "pairwiserank.h"
#include "socialprefnode.h"
#include <algorithm>

// Majority rule using Social Choice Graph
Options majority_rule( std::vector<SocialPrefNode> graph ){

    // Lambda. Compares preferences size, returns the greatest
    auto order = [ ]( SocialPrefNode& left, SocialPrefNode& right ){

        return left.get_preferences( ).size( ) > right.get_preferences( ).size( );
    };

    // Sort according to preferences' size. Decreasing order
    std::sort( graph.begin( ), graph.end( ), order );

    // If the greatest element has size greater than the total number of options divided by two
    if( graph.begin( ).base( ) -> get_preferences( ).size( ) > ( graph.size( ) / 2 ) ){

        Options winner( graph.begin( ).base( ) -> get_id( ),
                        static_cast<int>( graph.begin( ).base( ) -> get_preferences().size( ) ) );

        // Return it as the winner
        return winner;
    }

    // Else, if its size is not greater than, return NULL: no option wins
    else

        return Options( "NULL", -1 );
}

// Majority rule using Pairwise Rank
Options majority_rule( std::vector<PairWiseRank> rank ){

    // PROBLEM HERE: values not being modified
    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

        rank[ i ].get_optx( ).set_value( 0 );
        rank[ i ].get_opty( ).set_value( 0 );
    }

    // The same here
    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i ){

        if( rank[ i ].get_xval( ) > rank[ i ].get_yval( ) )

            ++rank[ i ].get_optx( );

        else if( rank[ i ].get_xval( ) < rank[ i ].get_yval( ) )

            ++rank[ i ].get_opty( );
    }

    // This is just bullshit
//    auto comparison = [ ]( PairWiseRank& left, PairWiseRank right ){

//        if( ( ( left.get_xval( ) + left.get_yval( ) ) / 2 ) > ( ( right.get_xval( ) + right.get_yval( ) ) / 2 ) )

//            return left;

//        else if( ( ( left.get_xval( ) + left.get_yval( ) ) / 2 ) < ( ( right.get_xval( ) + right.get_yval( ) ) / 2 ) )

//            return right;
//    };

    // This might work when the bullshit above start working properly
    std::sort( rank.begin( ), rank.end( ) );

    // This WOULD BE fine if the aforementioned shit actually worked
    if( rank.begin( ).base( ) -> get_optx( ).get_value( ) > rank.begin( ).base( ) -> get_opty( ).get_value( ) )

        return rank.begin( ).base( ) -> get_optx( );

    else if( rank.begin( ).base( ) -> get_optx( ).get_value( ) < rank.begin( ).base( ) -> get_opty( ).get_value( ) )

        return rank.begin( ).base( ) -> get_opty( );

    else

        return Options( "NULL", -1 );
}

void borda_count( std::vector<PairWiseRank>& rank ){


}
