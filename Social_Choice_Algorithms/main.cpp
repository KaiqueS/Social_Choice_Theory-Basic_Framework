#include <iostream>
#include "sctheory.cpp"

// TODO: Exceptions for all classes/functions/methods that deal with vectors/containers -> Check
//       for emptiness
// TODO: Clean/organize code
// TODO: Rethink PairWiseRank -> Try to figure out how to, for any two PWR, if any of the two options
//       that it holds are equal, then they ARE the SAME, i.e., have the same address. This way one
//       can use majority rule for PWR withouht appealing to a middle-class
// TODO: template function to deal with lambdas -> Check for type, then use an appropriate lambda
// MODIFY: PreferenceMatrix: remove options, use string instead, no value for each alternative
//         Agent: agents will set their own values, instead of taking from the matrix
// TODO: create a test for irrelevant alts. Case -> two identical profiles
// MODIFY: Remember to change Options operator==. Check only for id, because of Irrelevant Alts

int main( ){

    srand( static_cast<unsigned int>( time( nullptr ) ) );

    Preferencematrix newmtx{ };

    newmtx.set_matrix( 4, 4 );

    std::vector<Agent> listofagents( newmtx.get_matrix( ).size( ) );

    std::cout << newmtx;

    initialize_agents( listofagents, newmtx );

    std::cout << "\n";

    std::cout << listofagents[ 3 ] << "\n";

    std::cout << "\n";

    std::vector<PairWiseRank> rank = rank_generation( listofagents );

    for( PairWiseRank item : rank ){

        std::cout << item << "\n";
    }

    //majority_rule( rank );

    std::cout << "\n";

	std::vector<SocialPrefNode> graph{ };

	initialize_graph( listofagents, graph );

	make_graph( listofagents, rank, graph );

    //std::cout << graph[ 0 ][ SocialPrefNode::worsethan_index{ 0 } ] -> get_id( ) << '\n';

    print_graph( graph );

    majority_rule( graph );

    // Problem here: value > number of opts
    make_social_order( listofagents, rank );

    // TRETA
    /*std::vector<SocialPrefNode> connected{ tarjan( graph ) };

    for( SocialPrefNode node : connected )

        std::cout << node.get_id( ) << "\t"*/;

    std::cout << "\n";

    condorcet_paradox( rank, graph );

    std::cout << "\n";

    arrow_impossibility( listofagents, newmtx, rank, graph );
}
