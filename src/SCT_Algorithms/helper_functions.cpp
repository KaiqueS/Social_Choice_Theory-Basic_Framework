#include "socialprefnode.h"

template<typename Prefs> void print_graph( std::vector<SocialPrefNode<Prefs>>& graph ){

	for( int i = 0; i < graph.size( ); ++i )

		std::cout << graph[ i ] << "\n";
}
