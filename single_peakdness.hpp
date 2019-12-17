#pragma once

#include "sctgraph.hpp"

namespace SCT{

class Single_Peakedness{

	public:

		// Constructors & Destructor
		Single_Peakedness( ){ }
		Single_Peakedness( Rank& newrank, Graph& newgraph ) : rank( newrank ), graph( newgraph ){ }
		Single_Peakedness( const Single_Peakedness& copy ){
			rank = copy.rank; graph = copy.graph;
		}
		~Single_Peakedness( ){
			clear( );
		}

		// Operators
		Single_Peakedness& operator=( Single_Peakedness copy ){

			swap( *this, copy );

			return *this;
		}

		bool operator( )( Rank& rank, Graph& graph );

		// Helper functions
		friend void swap( Single_Peakedness& left, Single_Peakedness& right ){

			using std::swap;

			swap( left.rank, right.rank );
			swap( left.graph, right.graph );
		}

		void clear( ){

			rank.clear( );
			graph.clear( );
		}

	private:

		Rank rank{ };

		Graph graph{ };
	};

// Non-member helpers
}