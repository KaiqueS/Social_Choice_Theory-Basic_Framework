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
	SocialChoiceGraph( const SocialChoiceGraph<Prefs>& copy );

	~SocialChoiceGraph( ){ }

	// Setters
	void set_vecsize( int size ){ scgraph.resize( size ); }
	void initializvec( std::vector<Agent<Prefs>>& listofagents );
	void makegraph( std::vector<PairWiseRank<Prefs>>& rank );

	// Getters
	std::vector<SocialPrefNode<Prefs>> get_graph( ){ return scgraph; }

	// Operators
	SocialChoiceGraph& operator=( const SocialChoiceGraph<Prefs>& copy );

	SocialPrefNode<Prefs>& operator[ ]( const int& position ){ return scgraph[ position ]; }

private:

	std::vector<SocialPrefNode<Prefs>> scgraph{ };
};

/* Constructors */
template<typename Prefs> SocialChoiceGraph<Prefs>::SocialChoiceGraph( ){ scgraph = { }; }
template<typename Prefs> SocialChoiceGraph<Prefs>::SocialChoiceGraph( const SocialChoiceGraph<Prefs>& copy ){ scgraph = copy.scgraph; }

/* Setters */
template<typename Prefs> void SocialChoiceGraph<Prefs>::initializvec( std::vector<Agent<Prefs>>& listofagents ){

	set_vecsize( listofagents[ 0 ].get_preferences( ).size( ) );

	for( int i = 0; i < scgraph.size( ); ++i ){

		scgraph[ i ].set_self( listofagents[ 0 ].get_preferences( )[ i ] );
		scgraph[ i ].set_numofedges( listofagents );
	}
}

template<typename Prefs> void SocialChoiceGraph<Prefs>::makegraph( std::vector<PairWiseRank<Prefs>>& rank ){// Revise - this is wrong

	for( int i = 0; i < rank.size( ); ++i ){

		for( int j = 0; j < scgraph.size( ); ++j ){

			// if x > y
			if( rank[ i ].get_xval( ) > rank[ i ].get_yval( ) ){

				// If scgraph[ j ] == x, set preferredto = y, increment preferredto
				if( scgraph[ j ].get_self( ).get_alternatives( ) == rank[ i ].get_optx( ).get_alternatives( ) ){
					
					scgraph[ j ].set_preferredto( rank[ i ].get_opty( ) );
				}

				// Else if scgraph[ j ] == y, set
				else if( scgraph[ j ].get_self( ).get_alternatives( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

					scgraph[ j ].set_worse( rank[ i ].get_optx( ) );
				}
			}

			else if( rank[ i ].get_xval( ) < rank[ i ].get_yval( ) ){

				// If scgraph[ j ] == x, set preferredto = y, increment preferredto
				if( scgraph[ j ].get_self( ).get_alternatives( ) == rank[ i ].get_optx( ).get_alternatives( ) ){

					scgraph[ j ].set_worse( rank[ i ].get_opty( ) );
				}

				// Else if scgraph[ j ] == y, set
				else if( scgraph[ j ].get_self( ).get_alternatives( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

					scgraph[ j ].set_preferredto( rank[ i ].get_optx( ) );
				}
			}

			else if( rank[ i ].get_xval( ) == rank[ i ].get_yval( ) ){ // Revise this later: how to deal with indifference?

				// If scgraph[ j ] == x, set preferredto = y, increment preferredto
				if( scgraph[ j ].get_self( ).get_alternatives( ) == rank[ i ].get_optx( ).get_alternatives( ) ){

					scgraph[ j ].set_preferredto( rank[ i ].get_opty( ) );
					scgraph[ j ].set_worse( rank[ i ].get_opty( ) );
				}

				// Else if scgraph[ j ] == y, set
				else if( scgraph[ j ].get_self( ).get_alternatives( ) == rank[ i ].get_opty( ).get_alternatives( ) ){

					scgraph[ j ].set_preferredto( rank[ i ].get_optx( ) );
					scgraph[ j ].set_worse( rank[ i ].get_optx( ) );
				}
			}
		}
	}
}

/* Getters */

/* Operators */

template<typename Prefs> SocialChoiceGraph<Prefs>& SocialChoiceGraph<Prefs>::operator=( const SocialChoiceGraph<Prefs>& copy ){

	scgraph = copy.scgraph;

	return *this;
}

#endif // SOCIALCHOICEGRAPH_H
