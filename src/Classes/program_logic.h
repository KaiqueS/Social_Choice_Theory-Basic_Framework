#pragma once

#ifndef PROGRAM_LOGIC_H
#define PROGRAM_LOGIC_H

#include <QFile>
#include "preferencematrix.h"
#include "q_graphic_node.h"
#include "Classes/sctheory.h"

// TODO: Use RAII in class design

template<typename Prefs> class Program_Logic{

public:

	// Constructors & Destructor
	Program_Logic( );
	Program_Logic( std::vector<Q_Graphic_Node<Prefs>*>& ggraph );
	Program_Logic( const Program_Logic& copy_plogic );

	~Program_Logic( );

	// Setters

	// Getters
	std::vector<Agent> get_list_of_agents( );
	std::vector<SocialPrefNode>* getSocialPrefGraph( );
	// Operators
	std::vector<Q_Graphic_Node<Prefs>*>& operator=( const Program_Logic& plogic );

	// Helper Functions
	std::vector<SocialPrefNode> run_project( int row, int column );
	std::vector<SocialPrefNode> run_project( std::vector<Agent> listofagents );

	void show_graph( std::vector<SocialPrefNode>& graph, QGraphicsScene*& scene );
	void rank( );
	void update( bool isMagnetic );

	void setListofagents(const std::vector<Agent>& value);

	std::vector<SocialPrefNode*> spnGetFromList( std::vector<SocialPrefNode*> preferences );

private:

	std::vector<Q_Graphic_Node<Prefs>*> graphic_graph{ };
	std::vector<Agent> listofagents{ };
	std::vector<SocialPrefNode>* socialPrefGraph{ };
};

/* Constructors & Destructor */
template<typename Prefs> Program_Logic<Prefs>::Program_Logic( ){ graphic_graph = { }; }
template<typename Prefs> Program_Logic<Prefs>::Program_Logic( std::vector<Q_Graphic_Node<Prefs>*>& ggraph ){ graphic_graph = ggraph; }
template<typename Prefs> Program_Logic<Prefs>::Program_Logic( const Program_Logic& copy_plogic ){ graphic_graph = copy_plogic.graphic_graph; }

template<typename Prefs> Program_Logic<Prefs>::~Program_Logic( ){

	for( Q_Graphic_Node<Prefs>* element : graphic_graph ){

		delete element;
	}

	graphic_graph.clear( );
}

/* Setters */

/* Getters */
template<typename Prefs> std::vector<Agent> Program_Logic<Prefs>::get_list_of_agents( ){ return listofagents; }
/* Operators */

template<typename Prefs> std::vector<Q_Graphic_Node<Prefs>*>& Program_Logic<Prefs>::operator=( const Program_Logic& plogic ){

	graphic_graph = plogic.graphic_graph;

	return *this;
}

/* Helper Functions */

template<typename Prefs> std::vector<SocialPrefNode> Program_Logic<Prefs>::run_project( int row, int column ){

		Program_Logic( );

		//	Run project
		Preferencematrix newmtx{ };

		newmtx.set_matrix( static_cast<std::vector<int>::size_type>( row ), static_cast<std::vector<int>::size_type>( column ) );

		std::vector<Agent> listofagents( newmtx.get_matrix( ).size( ) );

		std::cout << newmtx;

		for( std::vector<int>::size_type i = 0; i < listofagents.size( ); ++i ){

			listofagents[ i ].set_id( "Agent " + std::to_string( i ) );

			listofagents[ i ].set_preferences( newmtx );

		}

		std::cout << "\n\n";

		std::vector<PairWiseRank> rank = Helper_functions::rank_generation( listofagents );

		socialPrefGraph = new std::vector<SocialPrefNode>( listofagents[ 0 ].get_preferences( ).size( ) );

		Helper_functions::make_graph( listofagents, rank, *socialPrefGraph );

		SCTheory().condorcet_paradox( rank, *socialPrefGraph );

		this -> listofagents = listofagents;

		std::cout << "\n\n___________________DEBUG_PREFS______________________\n\n";

		for( std::vector<int>::size_type i = 0; i < listofagents.size( ); ++i ){

			std::cout << "Agent " << listofagents[ i ].get_id( ) << " pref. : ";

			for( std::vector<int>::size_type j = 0; j < listofagents[ i ].get_preferences().size(); ++j ){

				std::cout << "( " << listofagents[ i ].get_preferences( )[ j ].get_opt( ) << " , ";
				std::cout << listofagents[ i ].get_preferences( )[ j ].get_value( ) << " ) ";
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

		return *socialPrefGraph;
}

template<typename Prefs> std::vector<SocialPrefNode> Program_Logic<Prefs>::run_project( std::vector<Agent> listofagents ){

		std::vector<PairWiseRank> rank = Helper_functions::rank_generation( listofagents );

		socialPrefGraph = new std::vector<SocialPrefNode>( listofagents[ 0 ].get_preferences( ).size( ) );

		Helper_functions::make_graph( listofagents, rank, *socialPrefGraph );

		SCTheory().condorcet_paradox( rank, *socialPrefGraph );

		this -> listofagents = listofagents;

		std::cout << "\n\n___________________DEBUG_PREFS______________________\n\n";

		for( std::vector<int>::size_type i = 0; i < listofagents.size( ); ++i ){

			std::cout << "Agent " << listofagents[ i ].get_id() << " pref. : ";

			for( std::vector<int>::size_type j = 0; j < listofagents[ i ].get_preferences( ).size( ); ++j ){

				std::cout << "( " << listofagents[ i ].get_preferences( )[ j ].get_opt( ) << " , ";
				std::cout << listofagents[ i ].get_preferences( )[ j ].get_value( ) << " ) ";
			}

			std::cout << "\n";
		}

		std::cout << "\n";

		for( std::vector<int>::size_type i = 0; i < listofagents.size( ); ++i ){

			listofagents[ i ].print_rank( );

			std::cout << "\n";
		}

		std::cout << "____________________________________________________";

		std::cout << "\n\n" << std::flush;

		return *socialPrefGraph;
}

template<typename Prefs> std::vector<SocialPrefNode*> Program_Logic<Prefs>::spnGetFromList( std::vector<SocialPrefNode*> preferences){

	std::vector<SocialPrefNode*> listAux{ };

	for( SocialPrefNode* node : preferences ){

		unsigned int aux = 0;

		for( std::vector<int>::size_type j = 0; j < socialPrefGraph -> size( ) &&
			 node -> get_id( ) != ( *socialPrefGraph)[ j ].get_id( ); ++j ){


			aux++;
		}

		if( aux < ( *socialPrefGraph ).size( ) ){

			listAux.push_back( &( *socialPrefGraph )[ aux ] );
		}
	}

	return listAux;

}


template<typename Prefs> void Program_Logic<Prefs>::show_graph( std::vector<SocialPrefNode>& graph, QGraphicsScene*& scene ){

	int z{ 0 };

	for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

		QPointF position = QPointF( ( 100 - std::rand( ) ) % 200, ( 100 - std::rand( ) ) % 200 );

		graphic_graph.push_back( new Q_Graphic_Node<Prefs>( ++z, position, 10, graph.size( ), scene, graph[ i ] ) );
	}

	for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

		std::vector<SocialPrefNode*> preferences = graphic_graph[ i ] -> getSPNode( ).get_preferences( );

		for( SocialPrefNode* node : preferences ){

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

	QPointF center = QPoint( 0,0 );

	if( isMagnetic ){

		for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

			graphic_graph[ i ] -> calcMovement( graphic_graph );

			center -= graphic_graph[ i ] -> getPosition( );
		}
		center/=graphic_graph.size( );
	}

	else{

		for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

			graphic_graph[ i ] -> setMoveVector( QPointF( 0, 0 ) );
		}
	}

	for( std::vector<int>::size_type i = 0; i < graphic_graph.size( ); ++i ){

		graphic_graph[ i ] -> setPosition(center);
		graphic_graph[ i ] -> update( );
	}
}

template<typename Prefs> void Program_Logic<Prefs>::setListofagents(const std::vector<Agent>& value){ listofagents = value;}

template<typename Prefs> std::vector<SocialPrefNode>* Program_Logic<Prefs>::getSocialPrefGraph( ){ return socialPrefGraph; }



#endif // PROGRAM_LOGIC_H
