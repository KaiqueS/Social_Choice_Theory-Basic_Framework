#include "Classes/socialprefnode.h"
#include "Classes/cycle.h"
#include "Classes/nodeopt.h"

template<typename Prefs> void print_graph( std::vector<SocialPrefNode<Prefs>>& graph ){

	for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i )

		std::cout << graph[ i ] << "\n";
}

template<typename Prefs> void strongconnect( std::vector<SocialPrefNode<Prefs>>& graph, std::vector<NodeOpt<Prefs>>& track, int index ){

	NodeOpt<Prefs> v{ };

	v.set_opt( index );
	v.set_link( index );

	++index;

	track.push_back( v );

	for( std::vector<int>::size_type i = 0; i < track.size( ); ++i ){

		if( track[ i ].get_opt( ).get_id( ) == v.get_opt( ).get_id( ) )

			v.set_onstack( true );

		else

			v.set_onstack( false );
	}


}

// Checkes for cycles in graph GRAPH - Isso aqui tá claramente dando boxta
template<typename Prefs> std::vector<Cycle<Prefs>> check_cycle( std::vector<SocialPrefNode<Prefs>>& graph ){

	/*std::vector<Cycle<Prefs>> paths( graph.size( ) );

	for( int i = 0; i < graph.size( ); ++i ){

		paths[ i ].set_id( graph[ i ].get_id( ) );
	}

	for( int i = 0; i < graph.size( ); ++i ){

		for( int j = 0; j < paths.size( ) ; ++j ){

			if( graph[ i ].get_id( ) == paths[ j ].get_id( )  ){

				for( int k = 0; k < graph[ i ].get_preferences( ).size( ); ++k ){

					paths[ j ].set_path( graph[ i ].get_preferences( )[ k ] -> get_id( ) );
				}
			}
		}
	}*/

	// Tarjan algorithm - DFS
		// Get a random node in path, add it to path
			// Get a random value from preferences, add it to path
				// Do this until a repeated node is reached


	int index = 0;

	std::vector<Prefs> paths{ };

	//return paths;
}
