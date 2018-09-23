#include <iostream>
#include <vector>
#include "preferencematrix.h"
#include "agent.h"
#include "SCTheory.cpp"
#include "pairwiserank.h"
#include "socialchoicegraph.h"
#include "socialprefnode.h"

/* TODO: Fix indifference - Repetition going on
 *		 Fix the case where x and y have the same amount of votes, but no indifference: if xval == yval, then increase
 *		 Maybe a data structure to substitute for the use of std::tuple? It is more readable - DONE
 *		 Start documenting - IN PROGRESS
*/

int main( ){

	Preferencematrix<char> newmtx{ };

	newmtx.set_matrix( 4, 4 );

	std::vector<Agent<char>> listofagents( newmtx.get_matrix( ).size( ) );

	newmtx.print_mtx( );

	for( int i = 0; i < listofagents.size( ); ++i ){

		listofagents[ i ].set_id( std::to_string( i ) );
		listofagents[ i ].set_preferences( newmtx );
	}

	std::cout << "\n\n";

	listofagents[ 2 ].print_prefs( );

	std::cout << "\n\n";

	std::vector<PairWiseRank<char>> rank = rank_generation( listofagents );

	std::vector<SocialPrefNode<char>> graph( listofagents[ 0 ].get_preferences( ).size( ) );

	condorcet_paradox( listofagents, rank, graph );
}
