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

    // Constructors & Destructor
    Pareto_Principle( ){ }
    Pareto_Principle( Rank& newrank, Population& pop ) : rank( newrank ), population( pop ){ }
    Pareto_Principle( const Pareto_Principle& copy ){ rank = copy.rank; population = copy.population; }
    ~Pareto_Principle( ){ clear( ); }

	// Operators
	Pareto_Principle& operator=( Pareto_Principle copy ){

        swap( *this, copy );
        return  *this;
    }

    bool operator( )( SCT::Procedure& procedure );

    // Helper functions
    friend void swap( Pareto_Principle& left, Pareto_Principle& right ){

        using std::swap;

        swap( left.rank, right.rank );
        swap( left.population, right.population );
    }

    void clear( ){

        rank.clear( );
        population.clear( );
    }

private:

    Rank rank{ };
	Population population{ };
};

class Irrelevant_Alternatives{

public:

    // Constructors & Destructor
    Irrelevant_Alternatives( ){ }
    Irrelevant_Alternatives( Preferencematrix& mtx, Population& pop ) : matrix( mtx ), population( pop ){ }
	Irrelevant_Alternatives( const Irrelevant_Alternatives& copy ){ matrix = copy.matrix; population = copy.population; }
	~Irrelevant_Alternatives( ){ clear( ); }

    // Operators
    Irrelevant_Alternatives& operator=( Irrelevant_Alternatives copy ){

        swap( *this, copy );

        return *this;
    }

    bool operator( )( SCT::Procedure& procedure );

    // Helper functions
    friend void swap( Irrelevant_Alternatives& left, Irrelevant_Alternatives& right ){

        using std::swap;

        swap( left.matrix, right.matrix );
        swap( left.population, right.population );
    }

    void clear( ){

        matrix.clear( );
        population.clear( );
    }

private:

    Preferencematrix matrix{ };
    Population population{ }; // useless
    };

class Non_Dictatorship{

public:

    // Constructors & Destructor
    Non_Dictatorship( ){ }
    Non_Dictatorship( Population& pop, Rank& newrank, Graph& newgraph ) : population( pop ), rank( newrank ), graph( newgraph ){ }
    Non_Dictatorship( const Non_Dictatorship& copy ){ population = copy.population; rank = copy.rank; graph = copy.graph; }
    ~Non_Dictatorship( ){ clear( ); }

    // Operators
    Non_Dictatorship& operator=( Non_Dictatorship copy ){

        swap( *this, copy );

        return *this;
    }

    bool operator( )( SCT::Procedure& procedure );

    // Helper functions
    friend void swap( Non_Dictatorship& left, Non_Dictatorship& right ){

        using std::swap;

        swap( left.population, right.population );
        swap( left.rank, right.rank );
        swap( left.graph, right.graph );
    }

    void clear( ){

        population.clear( );
        rank.clear( );
        graph.clear( );
    }

private:

    Population population{ };

    Rank rank{ };

    Graph graph{ };
    };

class Condorcet_Paradox{

public:

	// Constructors & Destructor
	Condorcet_Paradox( ){ }
    Condorcet_Paradox( Rank& newrank, Graph& newgraph ) : rank( newrank ), graph( newgraph ){ }
    ~Condorcet_Paradox( ){ clear( ); }

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

class Single_Peakedness{

public:

    // Constructors & Destructor
    Single_Peakedness( ){ }
    Single_Peakedness( Rank& newrank, Graph& newgraph ) : rank( newrank ), graph( newgraph ){ }
    Single_Peakedness( const Single_Peakedness& copy ){ rank = copy.rank; graph = copy.graph; }
    ~Single_Peakedness( ){ clear( ); }

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

class Arrow_Impossibility{

public:

	// Constructors & Destructor
	Arrow_Impossibility( ){ }
	Arrow_Impossibility( Preferencematrix& mtx, Rank& rank, Population& pop, Graph& graph ) : pareto( Pareto_Principle( rank, pop ) ),
																							  irrelevant( Irrelevant_Alternatives( mtx, pop ) ),
																							  dictator( Non_Dictatorship( pop, rank, graph ) ){ }

    Arrow_Impossibility( Pareto_Principle& par, Irrelevant_Alternatives& alts, Non_Dictatorship& dic, Single_Peakedness& peak ) : pareto( par ),
                                                                                                                                  irrelevant( alts ),
                                                                                                                                  dictator( dic ),
                                                                                                                                  singlePeak( peak ){ }
    Arrow_Impossibility( const Arrow_Impossibility& copy ){

        pareto = copy.pareto;
        irrelevant = copy.irrelevant;
        dictator = copy.dictator;
        singlePeak = copy.singlePeak;
    }

    ~Arrow_Impossibility( ){ clear( ); }

    // Operators
    bool operator( )( SCT::Procedure& procedure );

    // Helper functions
    void clear( ){

        pareto.clear( );
        irrelevant.clear( );
        dictator.clear( );
        singlePeak.clear( );
    }
private:

    Pareto_Principle pareto{ };
	Irrelevant_Alternatives irrelevant{ };
	Non_Dictatorship dictator{ };
	Single_Peakedness singlePeak{ };

	bool validity{ true };
    };
}

Preferencematrix generate_prime_profile( Preferencematrix& originalmatrix );

#endif // SCTHEORY_H
