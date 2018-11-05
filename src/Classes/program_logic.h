#pragma once

#ifndef PROGRAM_LOGIC_H
#define PROGRAM_LOGIC_H

#include <iostream>
#include <vector>
#include "Classes/preferencematrix.h"
#include "Classes/agent.h"
#include "SCT_Algorithms/SCTheory.cpp"
#include "Classes/pairwiserank.h"
#include "Classes/socialprefnode.h"
#include "Classes/q_graphic_node.h"

// TODO: Use RAII in class design

template<typename Prefs> class Program_Logic{

public:

	// Constructors & Destructor
	Program_Logic( );
	Program_Logic( std::vector<Q_Graphic_Node<Prefs>*>& ggraph );
	Program_Logic( const Program_Logic& copy_plogic );

	~Program_Logic( ){ }

	// Setters

	// Getters

	// Operators
	std::vector<Q_Graphic_Node<Prefs>*>& operator=( const Program_Logic& plogic );

	// Helper Functions
	std::vector<SocialPrefNode<Prefs>> run_project( int row, int column );

	void show_graph( std::vector<SocialPrefNode<Prefs>>& graph, QGraphicsScene*& scene );
	void rank( );
	void update( bool isMagnetic );
	void clean( );

private:

	std::vector<Q_Graphic_Node<Prefs>*> graphic_graph{ };
};

/* Constructors & Destructor */
template<typename Prefs> Program_Logic<Prefs>::Program_Logic( ){ graphic_graph = { }; }
template<typename Prefs> Program_Logic<Prefs>::Program_Logic( std::vector<Q_Graphic_Node<Prefs>*>& ggraph ){ graphic_graph = ggraph; }
template<typename Prefs> Program_Logic<Prefs>::Program_Logic( const Program_Logic& copy_plogic ){ graphic_graph = copy_plogic.graphic_graph; }

/* Setters */

/* Getters */

/* Operators */

template<typename Prefs> std::vector<Q_Graphic_Node<Prefs>*>& Program_Logic<Prefs>::operator=( const Program_Logic& plogic ){

	graphic_graph = plogic.graphic_graph;

	return *this;
}

/* Helper Functions */

template<typename Prefs> std::vector<SocialPrefNode<Prefs>> Program_Logic<Prefs>::run_project( int row, int column ){

		Program_Logic( );

		//	Run project
		Preferencematrix<Prefs> newmtx{ };

		newmtx.set_matrix( row, column );

		std::vector<Agent<Prefs>> listofagents( newmtx.get_matrix( ).size( ) );

		newmtx.print_mtx( );

		for( std::vector<int>::size_type i = 0; i < listofagents.size( ); ++i ){

			listofagents[ i ].set_id( std::to_string( i ) );
			listofagents[ i ].set_preferences( newmtx );
		}

		std::cout << "\n\n";

		std::vector<PairWiseRank<Prefs>> rank = rank_generation( listofagents );

		std::vector<SocialPrefNode<Prefs>> graph( listofagents[ 0 ].get_preferences( ).size( ) );

		condorcet_paradox( listofagents, rank, graph );

		std::cout << "\n\n___________________DEBUG_PREFS______________________\n\n";

		for( std::vector<int>::size_type i = 0; i < listofagents.size( ); ++i ){

			std::cout << "Agent " << listofagents[ i ].get_id() << " pref. : ";

			for( std::vector<int>::size_type j = 0; j < listofagents[ i ].get_preferences().size(); ++j ){

				std::cout << "( " << listofagents[ i ].get_preferences()[ j ].get_alternatives() << " , ";
				std::cout << listofagents[ i ].get_preferences()[ j ].get_value( ) << " ) ";
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

		return graph;
}

template<typename Prefs> void Program_Logic<Prefs>::show_graph( std::vector<SocialPrefNode<Prefs>>& graph, QGraphicsScene*& scene ){

	int z{ 0 };

	for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

		QPointF position = QPointF( std::rand( ) % 500,std::rand( ) % 200 );

		graphic_graph.push_back( new Q_Graphic_Node<Prefs>( ++z, position, 10, graph.size( ), scene, graph[ i ] ) );
	}

	for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

		std::vector<SocialPrefNode<Prefs>*> preferences = graphic_graph[ i ] -> getSPNode( ).get_preferences( );

		for( SocialPrefNode<Prefs>* node : preferences ){

			unsigned int aux = 0;

			for( std::vector<int>::size_type j = 0; j < graphic_graph.size( ) &&
				 node -> get_id( ) != graphic_graph[ j ] -> getSPNode( ).get_id ( ); ++j ){

				aux++;
			}

			if( aux < graphic_graph.size( ) ){

				graphic_graph[ aux ] -> insert_node( graphic_graph[ i ], scene );
			}
		}
	}
}
template<typename Prefs> void Program_Logic<Prefs>::rank( ){

	for( Q_Graphic_Node<Prefs>* node : graphic_graph ){

		std::vector<Q_Graphic_Node<Prefs>*> last_nodes{ };

		node -> walkGraph( last_nodes );
	}

	std::vector<Q_Graphic_Node<Prefs>*> sorted_rank{ };

	for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

		std::vector<Q_Graphic_Node<char>*>::iterator aux{ };

		aux = sorted_rank.begin( );

		for( std::vector<int>::size_type j = 0; j < sorted_rank.size( ) &&
			 graphic_graph[ i ] -> get_Steps( ) < sorted_rank[ j ] -> get_Steps( ); ++j, ++aux );

		sorted_rank.insert( aux, graphic_graph[ i ] );
	}

	graphic_graph = sorted_rank;

	int rank{ 1 };

	for( std::vector<int>::size_type i = 0, aux_step = graphic_graph[ i ] -> get_Steps( ); i < graphic_graph.size( ); ++i ){

		if( graphic_graph[ i ] -> get_Steps( ) < aux_step ){

			aux_step = graphic_graph[ i ] -> get_Steps( );

			++rank;
		}

		graphic_graph[ i ] -> set_Rank( rank );
	}

	for( Q_Graphic_Node<Prefs>* node : sorted_rank ){

			std::cout << ">>Node id = " << node -> getSPNode( ).get_id( ) << " steps = " <<
						 node -> get_Steps( ) << " Rank = " << node -> get_Rank( ) << "\n";
	}

	std::cout << std::flush;
}
template<typename Prefs> void Program_Logic<Prefs>::update( bool isMagnetic ){

	if( isMagnetic ){

		for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

			graphic_graph[ i ] -> calcMovement( graphic_graph );
		}
	}

	else{

		for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

			graphic_graph[ i ] -> setMoveVector( QPointF( 0, 0 ) );
		}
	}

	for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

		graphic_graph[ i ] -> update( );
	}
}
template<typename Prefs> void Program_Logic<Prefs>::clean( ){

	for( Q_Graphic_Node<Prefs>* element : graphic_graph ){

		delete element;
	}

	graphic_graph.clear( );
}

#endif // PROGRAM_LOGIC_H
