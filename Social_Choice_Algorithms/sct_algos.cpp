#include "sct_algos.hpp"

void sct::Simple_majority_rule::operator( )( Graph& graph ){

    std::deque<SocialPrefNode> list{ };

    for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

        if( graph[ i ].get_preferences( ).size( ) > ( graph.size( ) / 2 ) )

            list.push_front( graph[ i ] );

        else

            list.push_back( graph[ i ] );
    }

    for( std::vector<int>::size_type i = 0; i < list.size( ); ++i ){

        winnerset.push_back( Options( list[ i ].get_id( ), false, static_cast<int>( list[ i ].get_preferences( ).size( ) ) ) );
    }
}

std::vector<Options> majority_rule( std::vector<SocialPrefNode>& graph ){

    //return ( *proc )( graph );
}

