#include <iostream>
#include "sct_algos.hpp"
#include "sctheory.hpp"
#include "sctgraph.hpp"
#include "sctrank.hpp"
#include "population.hpp"

// TODO: Exceptions for all classes/functions/methods that deal with vectors/containers -> Check
//       for emptiness
// TODO: Clean/organize code & start documenting
// TODO: Rethink PairWiseRank -> Try to figure out how to, for any two PWR, if any of the two options
//       that it holds are equal, then they ARE the SAME, i.e., have the same address. This way one
//       can use majority rule for PWR withouht appealing to a middle-class
// TODO: template function to deal with lambdas -> Check for type, then use an appropriate lambda - DONE, used functors instead
// MODIFY: PreferenceMatrix: remove options, use string instead, no value for each alternative
//         Agent: agents will set their own values, instead of taking from the matrix -> Smells like boilerplate
// TODO: create a test for irrelevant alts. Case -> two identical profiles
// MODIFY: Remember to change Options operator==. Check only for id, because of Irrelevant Alts
// TODO: Revise Non-Dic
// TRY: creating a SCT namespace to hold sctheory.cpp functions and aggregation_rules.cpp functions
//      see if this solves the problem of multiple definitions when integrating the GUI to the proj - Done, but needs testing
// CONSIDER: .cpp files for graph algorithms and rank algorithms
// BIG QUESTION: what should SCF return? Alternatives or profiles? If the latter, are they composed
// by only the alternatives that satisfies the aggregation procedure, or are they composed by every
// alternative, sorted according to wheter they satisfy or not the procedure? - For Arrow, return profiles, for GS, return an alternative
// TODO: allow choosing between a pure graph, i.e., graph not based on any aggregation procedure and
// a graph based on procedures
// TODO: modify arrow -> Allow for a procedure to be passed as an argument, use the profile resulted
// from the procedure in the axioms
// TODO: when allowing for used-defined aggregation procedures, use as example a custom threshold
// procedure, i.e., allow for the user to input a threshold that, when a given option surpasses
// the latter, it becomes the winner or one of the winners. Add that to GUI

int main( ){

    srand( static_cast<unsigned int>( time( nullptr ) ) );

    Preferencematrix newmtx{ };

    newmtx.set_matrix( 5, 5 );

    Population listofagents( newmtx.get_matrix( ).size( ) );

    std::cout << newmtx;

    listofagents.initialize_population( newmtx );

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

    // Allow for the user to select which procedure does he wants to use

     //std::cin >> procedure
     //pass procedure as argument to arrow function

    std::vector<Options> result = qualified_majority_rule( graph );

    //SCT::arrow_impossibility( listofagents, newmtx, rank, graph, {} );

    std::cout << "\n\n";

    /*Graph graph{ };

    Preferencematrix mtx{ };

    Rank rank{ };

    mtx.set_matrix( 45, 45 );

	Population population( mtx.get_matrix( ).size( ) );

	population.initialize_population( mtx );

    rank.generate_ranking( population );

    graph.initialize_graph( mtx );

    graph.make_graph( mtx, rank );

	sct::Qualified_majority_rule maj{ };

    sct::Borda_count count{ };

    sct::Simple_majority_rule simple{ };

	Profile social = simple( population );

    //sct::Procedure newproc = { sct::Qualified_majority_rule( ) };

    Profile result = maj( rank );

    Graph newgraph{ };

    Profile newres = count( population );

    std::cout << "The majority winner is: " << std::max_element( result.begin( ), result.end( ) ) -> get_opt( ) << "\n\n";

    std::cout << "The borda winner is: " << std::max_element( newres.begin( ), newres.end( ) ) -> get_opt( ) << "\n\n";

    std::cout << "The simple majority winner is: " << std::max_element( social.begin( ), social.end( ) ) -> get_opt( ) << "\n\n";

    for( std::vector<int>::size_type i = 0; i < result.size( ); ++i ){

        std::cout << result[ i ] << " ";
    }

    std::cout << "\n\n";

    for( std::vector<int>::size_type i = 0; i < newres.size( ); ++i ){

        std::cout << newres[ i ] << " ";
    }

    //std::string res = sct::qualified_majority( graph );

    std::cout << "\n\n";

    //std::cout << res;

    std::cout << "\n\n"; */
}
