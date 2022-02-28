#pragma once

#include "sctgraph.hpp"
#include "procedure.hpp"

namespace SCT{

class Non_Dictatorship{

	public:

		// Constructors & Destructor
		Non_Dictatorship( ){ }
		Non_Dictatorship( Preferencematrix& mtx, Rank& newrank, Graph& newgraph ) : matrix( mtx ), rank( newrank ), graph( newgraph ){ }
		Non_Dictatorship( const Non_Dictatorship& copy );
		Non_Dictatorship( Non_Dictatorship&& copy );
		~Non_Dictatorship( );

		// Operators
		Non_Dictatorship& operator=( Non_Dictatorship copy );
		Non_Dictatorship& operator=( Non_Dictatorship&& copy );

		bool operator( )( SCT::Procedure& procedure );

		// Helper functions
		friend void swap( Non_Dictatorship& left, Non_Dictatorship& right ){

			using std::swap;

			swap( left.matrix, right.matrix );
			swap( left.rank, right.rank );
			swap( left.graph, right.graph );
		}

		void clear( );

	private:

		Preferencematrix matrix{ };
		Rank rank{ };
		Graph graph{ };
};

/// Non-member helpers
}
