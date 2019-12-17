#pragma once

#include "pareto_principle.hpp"
#include "non_dictatorship.hpp"
#include "iia.hpp"

// Every axiom must have an instance of Rank and Population in its private fields

// Remember: function will be a functor, which, in turn, will return a profile of preferences, so
// one has to guarantee that the parameter function will return something that have the below nec
// essary methods, like, e.g., .size( ).

namespace SCT{

class Arrow_Impossibility{

	public:

		// Constructors & Destructor
		Arrow_Impossibility( ){ }
		Arrow_Impossibility( Preferencematrix& mtx, Rank& rank, Population& pop, Graph& graph ) : pareto( Pareto_Principle( mtx, pop, rank  ) ),
			                                                                                      irrelevant( Irrelevant_Alternatives( mtx, pop ) ),
			                                                                                      dictator( Non_Dictatorship( mtx, pop, rank, graph ) ){ }

		Arrow_Impossibility( Pareto_Principle& par, Irrelevant_Alternatives& alts, Non_Dictatorship& dic/*, Single_Peakedness& peak*/ ) : pareto( par ),
			                                                                                                                              irrelevant( alts ),
			                                                                                                                              dictator( dic ){ }
			                                                                                                                              //singlePeak( peak ){ }
		Arrow_Impossibility( const Arrow_Impossibility& copy ){

			pareto = copy.pareto;
			irrelevant = copy.irrelevant;
			dictator = copy.dictator;
			//singlePeak = copy.singlePeak;
		}

		~Arrow_Impossibility( ){
			clear( );
		}

		// Operators
		bool operator( )( SCT::Procedure& procedure );

		// Helper functions
		void clear( ){

			pareto.clear( );
			irrelevant.clear( );
			dictator.clear( );
			//singlePeak.clear( );
		}
	private:

		Pareto_Principle pareto{ };
		Irrelevant_Alternatives irrelevant{ };
		Non_Dictatorship dictator{ };
		//Single_Peakedness singlePeak{ };

		bool validity{ true };
};

/// Non-member helpers
}