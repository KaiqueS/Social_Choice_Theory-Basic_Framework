#include "Classes/socialprefnode.h"
#include "Classes/cycle.h"
#include "Classes/nodeopt.h"
#include "Classes/pairwiserank.h"
#include <algorithm>

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

// Checks for cycles in graph GRAPH - Isso aqui tá claramente dando boxta
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

template<typename Prefs> std::vector<Prefs> make_social_order( std::vector<PairWiseRank<Prefs>> socialrank ){

	std::vector<Options<Prefs>> orderedrank{ };

	// get every available option


	// get their respective scores, i.e., how many options they beat

	// order vector from greatest to smallest


	return orderedrank;
}
template<typename Prefs> std::vector<Options<Prefs>> make_social_order( std::vector<SocialPrefNode<Prefs>>& socialgraph ){

	std::vector<Options<Prefs>> orderedrank = [ ]( std::vector<Options<Prefs>>& opts, std::vector<SocialPrefNode<Prefs>>& graph ){

													 opts.resize( graph.size( ) );

													 for( std::vector<int>::size_type i = 0; i < opts.size( ); ++i ){

														opts[ i ].set_alternatives( graph[ i ].get_id( ) );
													 }

													 return opts;
												 };

	for( SocialPrefNode<Prefs> node : socialgraph ){

		for( Options<Prefs> opt : orderedrank ){

			if( opt.get_alternatives( ) == node.get_id( ) )

				opt.set_value( node.get_preferences( ).size( ) );
		}
	}

	return std::sort( orderedrank.begin( ), orderedrank.end( ) );
}

// Checks if the pareto principle is violated or not
template<typename Prefs> bool pareto_principle( ){

	// Checks the situation where, for every agent, xPiy, but xPy
	// If it is the case that, for every i in Agents, xPiy
		// check if xPy, return true
		// else, return false & the social preference

	// else, everything is okay
}

// Checks if , for any x, y, and z, the relation between x and y is modified by
// the position of z in the social ranking
template<typename Prefs> bool irrelevant_alternatives( ){


}

// Searches for a dictator
template<typename Prefs> bool non_dictatorship( ){

	// if there is a dictator
		// return true, and the dictator

	// else
		// return false, the social ordering is ok
}
