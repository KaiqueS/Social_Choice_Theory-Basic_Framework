#include <iostream>
#include <vector>
#include "Classes/preferencematrix.h"
#include "Classes/agent.h"
#include "SCTheory.cpp"
#include "Classes/pairwiserank.h"
#include "Classes/socialprefnode.h"

/*
 *		 Fix indifference - associate alternatives that have the same weight for an agent
 *		 Fix the case where x and y have the same amount of votes, but no indifference: if xval == yval, then increase
 *		 Start documenting - IN PROGRESS
 *		 Problem: when i > 9, id, being a char, cannot contain 2 or more characters
 *		 TODO: enhance code -> ADD EXCEPTIONS!
 *		 TODO: Problem: when row != col, for col > row
 *		 TODO: Remove templates, use static typing
 */

int main( ){

	srand( time( NULL ) );

	while( true ){

	Preferencematrix<char> newmtx{ };

	newmtx.set_matrix( 4, 5 );

	std::vector<Agent<char>> listofagents( newmtx.get_matrix( ).size( ) );

	newmtx.print_mtx( );

    for( std::vector<int>::size_type i = 0; i < listofagents.size( ); ++i ){

        listofagents[ i ].set_id( std::to_string( i ) );
        listofagents[ i ].set_preferences( newmtx );
    }

	std::cout << "\n\n";

	listofagents[ 2 ].print_prefs( );

	std::cout << "\n\n LINHA DE ERRO \n" << std::flush;

	std::vector<PairWiseRank<char>> rank = rank_generation( listofagents );

	std::cout << "\n\n LINHA DE ERRO 2 \n" << std::flush;

	std::vector<SocialPrefNode<char>> graph( listofagents[ 0 ].get_preferences( ).size( ) );

	std::cout << "\n\n LINHA DE ERRO 3 \n" << std::flush;

	condorcet_paradox( listofagents, rank, graph );

	std::cout << "\n\n LINHA DE ERRO 4 \n" << std::flush;


    //listofagents[ 2 ].get_indifference( );

    std::cout << "\n\n___________________DEBUG_PREFS______________________\n\n";

    for( std::vector<int>::size_type i = 0; i < listofagents.size( ); ++i ){

        std::cout << "Agent " << listofagents[ i ].get_id() << " pref. : \t";

		for( std::vector<int>::size_type j = 0; j < listofagents[ i ].get_preferences().size(); ++j ){

			std::cout << "( " << listofagents[ i ].get_preferences()[ j ].get_alternatives() << " , ";
			std::cout << listofagents[ i ].get_preferences()[ j ].get_value() << " ) ";
        }

		std::cout << "\n";
    }

	std::cout << "\n";

	for( std::vector<int>::size_type i = 0; i < listofagents.size( ); ++i ){

		listofagents[i].print_rank( );

		std::cout << "\n";
	}

    std::cout << "____________________________________________________";

	std::cout << "\n\n" << std::flush;
	}
}
