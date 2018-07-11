#ifndef SOCIALCHOICEGRAPH_H
#define SOCIALCHOICEGRAPH_H

#include "agent.h"
#include "socialprefnode.h"
#include "pairwiserank.h"

// TODO: REFACTOR! Remove all uses of Tuple. Replace it with a custom data structure

template<typename Prefs> class SocialChoiceGraph{

public:

	// Constructor & Destructor
	SocialChoiceGraph( );

	~SocialChoiceGraph( ){ }

	// Setters
	void setvecsize( int size ){ scgraph.resize( size ); }
	void initializvec( std::vector<Agent<Prefs>>& listofagents );
	void makegraph( std::vector<std::tuple<Options<Prefs>, Options<Prefs>, int, int, int>> rank ); //REFACTOR: USei PairWiseRank instead of Tuple
	void makegraph( std::vector<PairWiseRank<Prefs>> rank );

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

template<typename Prefs> void SocialChoiceGraph<Prefs>::makegraph( std::vector<PairWiseRank<Prefs>> rank ){

	for( int i = 0; i < rank.size( ); ++i ){

		for( int j = 0; j < scgraph.size( ); ++j ){

			// if x > y
			if( rank[ i ].get_xval( ) > rank[ i ].get_yval( ) ){

				// If scgraph[ j ] == x, set preferredto = y, increment preferredto
				if( scgraph[ j ].getself( ).get_alternatives( ) == rank[ i ].get_optx( ).get_alternatives( ) ){

					scgraph[ j ].setpreferredto( rank[ i ].get_opty( ) );

					scgraph[ j ].incrmntprefto( );
				}

				// Else if scgraph[ j ] == y, set
				else if( scgraph[ j ].getself( ).get_alternatives( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

					scgraph[ j ].setworse( rank[ i ].get_optx( ) );

					scgraph[ j ].incrmntworse( );
				}
			}

			else if( rank[ i ].get_xval( ) < rank[ i ].get_yval( ) ){

				// If scgraph[ j ] == x, set preferredto = y, increment preferredto
				if( scgraph[ j ].getself( ).get_alternatives( ) == rank[ i ].get_optx( ).get_alternatives( ) ){

					scgraph[ j ].setworse( rank[ i ].get_opty( ) );

					scgraph[ j ].incrmntworse( );
				}

				// Else if scgraph[ j ] == y, set
				else if( scgraph[ j ].getself( ).get_alternatives( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

					scgraph[ j ].setpreferredto( rank[ i ].get_optx( ) );

					scgraph[ j ].incrmntprefto( );
				}
			}

			else if( rank[ i ].get_xval( ) == rank[ i ].get_yval( ) ){ // Revise this later: how to deal with indifference?

				// If scgraph[ j ] == x, set preferredto = y, increment preferredto
				if( scgraph[ j ].getself( ).get_alternatives( ) == rank[ i ].get_optx( ).get_alternatives( ) ){

					scgraph[ j ].setpreferredto( rank[ i ].get_opty( ) );
					scgraph[ j ].setworse( rank[ i ].get_opty( ) );

					scgraph[ j ].incrmntprefto( );
					scgraph[ j ].incrmntworse( );
				}

				// Else if scgraph[ j ] == y, set
				else if( scgraph[ j ].getself( ).get_alternatives( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

					scgraph[ j ].setpreferredto( rank[ i ].get_optx( ) );
					scgraph[ j ].setworse( rank[ i ].get_optx( ) );

					scgraph[ j ].incrmntprefto( );
					scgraph[ j ].incrmntworse( );
				}
			}
		}
	}
}

#endif // SOCIALCHOICEGRAPH_H
