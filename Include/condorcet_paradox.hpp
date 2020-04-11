#pragma once

#include "sctgraph.hpp"
#include "procedure.hpp"

namespace SCT{

class Condorcet_Paradox{

	public:

		// Constructors & Destructor
		Condorcet_Paradox( ){ }
		Condorcet_Paradox( Rank& newrank, Graph& newgraph ) : rank( newrank ), graph( newgraph ){ }
		~Condorcet_Paradox( ){
			clear( );
		}

		// Operators
		bool operator( )( Profile& profile );

		// Helper functions
		friend void swap( Condorcet_Paradox& left, Condorcet_Paradox& right ){

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

/// Non-member helpers
}

