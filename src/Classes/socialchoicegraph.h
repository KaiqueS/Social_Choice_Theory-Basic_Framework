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

		for( int j = 0; j < scgraph.size( ); ++j ){

			// If xval > yval
			if( std::get<2>( rank[ i ] ) > std::get<3>( rank[ i ] ) ){

				// If scgraph[ i ] == x, set scgraph[ i ] > y, y = y, increment pref pointer
				if( scgraph[ j ].getself( ).get_alternatives( ) == std::get<0>( rank[ i ] ).get_alternatives( ) ){

					scgraph[ j ].setpreferred( std::get<1>( rank[ i ] ) );

					scgraph[ j ].getpreferred( ) -> set_alternatives( std::get<1>( rank[ i ] ).get_alternatives( ) );

					scgraph[ j ].incrementpref( );
				}

				// Else if scgraph[ i ] == y, set scgraph[ i ] < x, x = x, increment worse pointer
				else if( scgraph[ i ].getself( ).get_alternatives( ) == std::get<1>( rank[ i ] ).get_alternatives( ) ){

					scgraph[ j ].setworse( std::get<0>( rank[ i ] ) );

					scgraph[ j ].getworse( ) -> set_alternatives( std::get<0>( rank[ i ] ).get_alternatives( ) ); ;

					scgraph[ j ].incrementworse( );
				}
			}

			else if( std::get<2>( rank[ i ] ) < std::get<3>( rank[ i ] ) ){

				if( scgraph[ j ].getself( ).get_alternatives( ) == std::get<0>( rank[ i ] ).get_alternatives( ) ){

					scgraph[ j ].setpreferred( std::get<1>( rank[ i ] ) );

					scgraph[ j ].getpreferred( ) -> set_alternatives( std::get<0>( rank[ i ] ).get_alternatives( ) );

					scgraph[ j ].incrementworse( ); // shit happening here
				}

				else if( scgraph[ j ].getself( ).get_alternatives( ) == std::get<1>( rank[ i ] ).get_alternatives( ) ){

					scgraph[ j ].setworse( std::get<0>( rank[ i ] ) );

					scgraph[ j ].getworse( ) -> set_alternatives( std::get<0>( rank[ i ] ).get_alternatives( ) ); ;

					scgraph[ j ].incrementworse( );
				}
			}

			else if( std::get<2>( rank[ i ] ) == std::get<4>( rank[ i ] ) ||
					 std::get<3>( rank[ i ] ) == std::get<4>( rank[ i ] ) ){

			}
		}
	}
}

#endif // SOCIALCHOICEGRAPH_H
