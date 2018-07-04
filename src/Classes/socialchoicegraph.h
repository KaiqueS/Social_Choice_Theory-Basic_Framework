#ifndef SOCIALCHOICEGRAPH_H
#define SOCIALCHOICEGRAPH_H

#include "agent.h"
#include "socialprefnode.h"

template<typename Prefs> class SocialChoiceGraph{

public:

	// Constructor & Destructor
	SocialChoiceGraph( );

	~SocialChoiceGraph( ){ }

	// Setters
	void setvecsize( int size ){ scgraph.resize( size ); }
	void initializvec( std::vector<Agent<Prefs>>& listofagents );
	void makegraph( std::vector<std::tuple<Options<Prefs>, Options<Prefs>, int, int, int>> rank );

	// Getters
	std::vector<SocialPrefNode<Prefs>> getgraph( ){ return scgraph; }

private:

	std::vector<SocialPrefNode<Prefs>> scgraph{ };
};

template<typename Prefs> SocialChoiceGraph<Prefs>::SocialChoiceGraph( ){

	scgraph = { };
}

template<typename Prefs> void SocialChoiceGraph<Prefs>::initializvec( std::vector<Agent<Prefs>>& listofagents ){

	setvecsize( listofagents[ 0 ].get_preferences( ).size( ) );

	for( int i = 0; i < scgraph.size( ); ++i ){

		scgraph[ i ].setself( listofagents[ 0 ].get_preferences( )[ i ] );
	}
}

template<typename Prefs> void SocialChoiceGraph<Prefs>::makegraph( std::vector<std::tuple<Options<Prefs>, Options<Prefs>, int, int, int>> rank ){

	for( int i = 0; i < rank.size( ); ++i ){

		if( std::get<2>( rank[ i ] ) > std::get<3>( rank[ i ] ) ){


		}

		else if( std::get<2>( rank[ i ] ) < std::get<23>( rank[ i ] ) ){


		}

		else if( std::get<2>( rank[ i ] ) == std::get<4>( rank[ i ] ) ||
				 std::get<3>( rank[ i ] ) == std::get<4>( rank[ i ] ) )
	}
}

#endif // SOCIALCHOICEGRAPH_H
