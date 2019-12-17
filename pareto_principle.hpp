#pragma once

#include "sctrank.hpp"
#include "sctgraph.hpp"
#include "procedure.hpp"

namespace SCT{

	class Pareto_Principle {

	public:

		// Constructors & Destructor
		Pareto_Principle( ){ }
		Pareto_Principle( Preferencematrix& mtx, Population& pop, Rank& newrank ) : matrix( mtx ), population( pop ), rank( newrank ){ } // Switch population with PreferenceMatrix
		Pareto_Principle( const Pareto_Principle& copy );
		Pareto_Principle( Pareto_Principle&& copy );
		~Pareto_Principle( );

		// Setters

		// Getters

		// Operators
		Pareto_Principle& operator=( Pareto_Principle copy );
		Pareto_Principle& operator=( Pareto_Principle&& copy );

		bool operator( )( SCT::Procedure& procedure );

		// Helper functions
		friend void swap( Pareto_Principle& left, Pareto_Principle& right ) {

			using std::swap;

			swap(left.rank, right.rank);
			swap(left.population, right.population);
		}

		void clear( );

	private:

		Preferencematrix matrix{ };
		Population population{ };
		Rank rank{ };
	};
}