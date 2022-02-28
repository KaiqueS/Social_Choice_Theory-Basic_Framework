#pragma once

#include "sctgraph.hpp"
#include "procedure.hpp"

namespace SCT{

class Irrelevant_Alternatives{

	public:

		// Constructors & Destructor
		Irrelevant_Alternatives( ){ }
		Irrelevant_Alternatives( Preferencematrix& mtx ) : matrix( mtx ){ }
		Irrelevant_Alternatives( const Irrelevant_Alternatives& copy );
		Irrelevant_Alternatives( Irrelevant_Alternatives&& alts );
		~Irrelevant_Alternatives( );

		// Operators
		Irrelevant_Alternatives& operator=( Irrelevant_Alternatives copy );
		Irrelevant_Alternatives& operator=( Irrelevant_Alternatives&& alts );

		bool operator( )( SCT::Procedure& procedure );

		// Helper functions
		friend void swap( Irrelevant_Alternatives& left, Irrelevant_Alternatives& right ){

			using std::swap;

			swap( left.matrix, right.matrix );
		}

		void clear( );

	private:

		Preferencematrix matrix{ };
};

/// Non-member helpers
Preferencematrix generate_prime_profile( Preferencematrix& originalmatrix );

void generate( int value, Profile& profile, Preferencematrix& matrix );
}