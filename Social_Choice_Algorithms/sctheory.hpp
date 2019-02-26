#ifndef SCTHEORY_H
#define SCTHEORY_H

#include "sctrank.hpp"
#include "sctgraph.hpp"
#include "majoritarian_rules.hpp"
#include "plurality_rules.hpp"
#include "proportional_rules.hpp"

// Every axiom must have an instance of Rank and Population in its private fields

namespace SCT{

class Pareto_Principle{

public:

    Pareto_Principle( ){ }
    Pareto_Principle( Rank& newrank, Population& pop ) : rank( newrank ), population( pop ){ }
	Pareto_Principle( const Pareto_Principle& copy ){ rank = copy.rank; population = copy.population; }
	~Pareto_Principle( ){ rank.clear( ); population.clear( ); }

    bool operator( )( SCT::Procedure& procedure );

private:

    Rank rank{ };
	Population population{ };
};

class Irrelevant_Alternatives{

public:

    Irrelevant_Alternatives( ){ }
    Irrelevant_Alternatives( Preferencematrix& mtx, Population& pop ) : matrix( mtx ), population( pop ){ }
	Irrelevant_Alternatives( const Irrelevant_Alternatives& copy ){ matrix = copy.matrix; population = copy.population; }
    ~Irrelevant_Alternatives( ){ matrix.clear( ); population.clear( ); }

    bool operator( )( SCT::Procedure& procedure );

private:

    Preferencematrix matrix{ };

    Population population{ };
    };

class Non_Dictatorship{

public:

    Non_Dictatorship( ){ }
    Non_Dictatorship( Population& pop, Rank& newrank, Graph& newgraph ) : population( pop ), rank( newrank ), graph( newgraph ){ }
    Non_Dictatorship( const Non_Dictatorship& copy ){ population = copy.population; rank = copy.rank; graph = copy.graph; }
	~Non_Dictatorship( ){ population.clear( );
						  rank.clear( );
						  graph.clear( ); }

    bool operator( )( SCT::Procedure& procedure );

private:

    Population population{ };

    Rank rank{ };

    Graph graph{ };
    };

class Condorcet_Paradox{

public:

	Condorcet_Paradox( ){ }
    Condorcet_Paradox( Rank& newrank, Graph& newgraph ) : rank( newrank ), graph( newgraph ){ }
	~Condorcet_Paradox( ){ rank.clear( );
						   graph.clear( ); }

    bool operator( )( Profile& profile );

private:

    Rank rank{ };

    Graph graph{ };
    };

class Single_Peakedness{

public:

    Single_Peakedness( ){ }
    Single_Peakedness( Rank& newrank, Graph& newgraph ) : rank( newrank ), graph( newgraph ){ }
    Single_Peakedness( const Single_Peakedness& copy ){ rank = copy.rank; graph = copy.graph; }
    ~Single_Peakedness( ){ rank.clear( );
                           graph.clear( ); }

    bool operator( )( Rank& rank, Graph& graph );

private:

    Rank rank{ };

    Graph graph{ };
    };

class Arrow_Impossibility{

public:

	Arrow_Impossibility( ){ }
    Arrow_Impossibility( Preferencematrix& mtx, Rank& rank, Population& pop, Graph& graph ) :
                            pareto( Pareto_Principle( rank, pop ) ),
                            irrelevant( Irrelevant_Alternatives( mtx, pop ) ),
                            dictator( Non_Dictatorship( pop, rank, graph ) ){ }

    Arrow_Impossibility( Pareto_Principle& par, Irrelevant_Alternatives& alts, Non_Dictatorship& dic, Single_Peakedness& peak ) :
                            pareto( par ), irrelevant( alts ), dictator( dic ), singlePeak( peak ){ }
    Arrow_Impossibility( const Arrow_Impossibility& copy ){ pareto = copy.pareto; irrelevant = copy.irrelevant;
                                                                    dictator = copy.dictator; singlePeak = copy.singlePeak; }
    ~Arrow_Impossibility( ){ }

    bool operator( )( SCT::Procedure& procedure );

private:

    Pareto_Principle pareto{ };
	Irrelevant_Alternatives irrelevant{ };
	Non_Dictatorship dictator{ };

	Single_Peakedness singlePeak{ };
    };
}

#endif // SCTHEORY_H
