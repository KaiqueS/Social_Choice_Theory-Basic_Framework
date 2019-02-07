#ifndef SCTHEORY_H
#define SCTHEORY_H

#include "sctrank.hpp"
#include "aggregation_rules.hpp"
#include "sct_algos.hpp"

namespace SCT{

class Pareto_Principle{

public:

    Pareto_Principle( ){ }
    Pareto_Principle( Rank& newrank ) : rank( newrank ){ }
    Pareto_Principle( const Pareto_Principle& copy ){ rank = copy.rank; }
	~Pareto_Principle( ){ rank.clear( ); }

    bool operator( )( sct::Procedure& procedure );

private:

    Rank rank{ };
};

class Irrelevant_Alternatives{

public:

    Irrelevant_Alternatives( ){ }
    Irrelevant_Alternatives( Preferencematrix& mtx, Population& pop ) : matrix( mtx ), population( pop ){ }
    Irrelevant_Alternatives( const Irrelevant_Alternatives& copy );
    ~Irrelevant_Alternatives( ){ matrix.clear( );
                                 population.clear( ); }

    bool operator( )( sct::Procedure& procedure );

private:

    Preferencematrix matrix{ };

    Population population{ };
    };

class Non_Dictatorship{

public:

    Non_Dictatorship( ){ }
    Non_Dictatorship( Population& pop, Rank& newrank, Graph& newgraph ) : population( pop ), rank( newrank ), graph( newgraph ){ }
    Non_Dictatorship( const Non_Dictatorship& copy );
	~Non_Dictatorship( ){ population.clear( );
						  rank.clear( );
						  graph.clear( ); }

    bool operator( )( sct::Procedure& procedure );

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
    Single_Peakedness( const Single_Peakedness& copy );
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
                         pareto( Pareto_Principle( rank ) ),
                         irrelevant( Irrelevant_Alternatives( mtx, pop ) ),
                         dictator( Non_Dictatorship( pop, rank, graph ) ){ }

    Arrow_Impossibility( Pareto_Principle& par, Irrelevant_Alternatives& alts, Non_Dictatorship& dic, Single_Peakedness& peak ) :
                         pareto( par ), irrelevant( alts ), dictator( dic ), singlePeak( peak ){ }
    Arrow_Impossibility( const Arrow_Impossibility& arrow ){ *this = arrow; }
    ~Arrow_Impossibility( ){ }

    bool operator( )( sct::Procedure& procedure );

private:

    Pareto_Principle pareto{ };
	Irrelevant_Alternatives irrelevant{ };
	Non_Dictatorship dictator{ };

	Single_Peakedness singlePeak{ };
    };
}

#endif // SCTHEORY_H
