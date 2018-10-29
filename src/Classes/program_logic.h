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

<<<<<<< HEAD
template<typename Prefs> class Program_Logic
{
public:
	std::vector<Q_Graphic_Node<Prefs>*> graphic_graph;
	std::vector<SocialPrefNode<Prefs>> run_project(int row, int column){
=======
class Program_Logic{

public:

	Program_Logic( );

	static void run_project( int row, int column ){
>>>>>>> 62dde527f5b0c715e69e2538f8189fac9e4c0b7e
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

		return graph;
	}

	void show_graph( std::vector<SocialPrefNode<Prefs>>& graph, QGraphicsScene *scene){

		int z=0;
		for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

			QPointF position = QPointF(std::rand( ) % 500,std::rand( ) % 200);

			graphic_graph.push_back(new Q_Graphic_Node<Prefs>(z++, position, 10, scene, graph[i]));
		}

		for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

			std::vector<SocialPrefNode<Prefs>*> preferences = graphic_graph[i]->getSPNode().get_preferences();
			for(SocialPrefNode<Prefs>* node : preferences){
				int aux = 0;
				for( std::vector<int>::size_type j = 0; j < graphic_graph.size( ) && node->get_id()!=graphic_graph[j]->getSPNode().get_id(); ++j){
					aux++;
				}
				if(aux<graphic_graph.size( )){
					graphic_graph[aux]->insert_node(graphic_graph[i], scene);
				}
			}
		}

	}

	void update(){

		if(std::rand()%100>90)
			std::random_shuffle(graphic_graph.begin(),graphic_graph.end());
		for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i )
		{
				graphic_graph[i]->update();

		}
	}
	void clean(){
		for( Q_Graphic_Node<Prefs>* element : graphic_graph){
//			element->
			delete element;
		}
		graphic_graph.clear();
	}
};



#endif // PROGRAM_LOGIC_H
