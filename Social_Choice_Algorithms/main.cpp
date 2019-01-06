#include <iostream>
#include "sct_algos.hpp"
#include "sctheory.cpp"
#include "sctgraph.hpp"
#include "sctrank.hpp"

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
// TODO: Revise Non-Dic
// TRY: creating a SCT namespace to hold sctheory.cpp functions and aggregation_rules.cpp functions
//      see if this solves the problem of multiple definitions when integrating the GUI to the proj
// CONSIDER: .cpp files for graph algorithms and rank algorithms
// BIG QUESTION: what should SCF return? Alternatives or profiles? If the latter, are they composed
// by only the alternatives that satisfies the aggregation procedure, or are they composed by every
// alternative, sorted according to wheter they satisfy or not the procedure?

int main( ){

    srand( static_cast<unsigned int>( time( nullptr ) ) );

    Preferencematrix newmtx{ };

    newmtx.set_matrix( 10, 10 );

    std::vector<Agent> listofagents( newmtx.get_matrix( ).size( ) );

    std::cout << newmtx;

    initialize_agents( listofagents, newmtx );

    std::cout << "\n";

    std::cout << listofagents[ 3 ] << "\n";

    std::cout << "\n";

    Rank rank{ };

    rank.generate_ranking( listofagents );

    for( PairWiseRank item : rank.get_rank( ) ){

        std::cout << item << "\n";
    }

    //majority_rule( rank );

    std::cout << "\n";

    Graph graph{ };

    graph.initialize_graph( newmtx );

    graph.make_graph( newmtx, rank );

    //graph.make_graph( newmtx, rank.get_rank( ) );

    //std::cout << graph[ 0 ][ SocialPrefNode::worsethan_index{ 0 } ] -> get_id( ) << '\n';

    print_graph( graph );



    //qualified_majority_rule( graph );

    // Problem here: value > number of opts
    //make_social_order( listofagents, rank );

    std::cout << "\n";

    //condorcet_paradox( rank, graph );

    std::cout << "\n";

    // Allow for the user to select which procedure does he wants to use

    /* std::cin >> procedure
     * pass procedure as argument to arrow function
    */

    std::vector<Options> result = qualified_majority_rule( graph );

    arrow_impossibility( listofagents, newmtx, rank, graph, result );

    std::cout << "\n\n";
}
