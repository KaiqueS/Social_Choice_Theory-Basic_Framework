#include "Classes/pairwiserank.h"
#include "Classes/socialprefnode.h"

// Majority rule using Social Choice Graph
Options majority_rule( std::vector<SocialPrefNode>& graph ){

    std::vector<Options> winnerset{ };

    // Get every element that satisfies the majority rule
    for( SocialPrefNode node : graph ){

        Options holder{ };

        if( node.get_preferences( ).size( ) > ( graph.size( ) / 2 ) ){

            holder.set_opt( node.get_id( ) );
            holder.set_value( static_cast<int>( node.get_preferences( ).size( ) ) );

            winnerset.push_back( holder );
        }
    }

    Options winner{ };

    // Select the greatest among those
    if( !winnerset.empty( ) ){

        for( Options leftopt : winnerset ){

            for( Options rightopt : winnerset ){

                if( leftopt.get_value( ) > rightopt.get_value( ) )

                    winner = leftopt;

                else if( leftopt.get_value( ) < rightopt.get_value( ) )

                    winner = rightopt;

                else if( leftopt.get_value( ) == rightopt.get_value( ) )

                    winner = leftopt;
            }
        }

        return winner;
    }

    else{

        winner.set_opt( "N" );
        winner.set_value( -1 );

        return winner;
    }
}

// Majority rule using Pairwise Rank
Options majority_rule( std::vector<PairWiseRank>& rank ){

    // how to contabilize the total amount of votes?
    std::vector<Options> winnerset{ };

    int totalvotes{ };

    for( PairWiseRank pairs : rank ){

        if( pairs.get_xval( ) > pairs.get_yval( ) ){

        }
    }

	return winnerset[ 1 ];
}

void borda_count( std::vector<PairWiseRank>& rank ){


}
