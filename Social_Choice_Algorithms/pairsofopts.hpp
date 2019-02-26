#ifndef PAIRSOFOPTS_H
#define PAIRSOFOPTS_H

//#include "options.hpp"
#include "population.hpp"

struct PairsOfOpts{

    // Constructors & Destructor
    PairsOfOpts( );
    PairsOfOpts( Options optx, Options opty ) : xpref( optx ), ypref( opty ){ }
    PairsOfOpts( const PairsOfOpts& copy );

    ~PairsOfOpts( ){ }

    // Operators
    PairsOfOpts& operator=( const PairsOfOpts& copy );

    // Members
    Options xpref{ };
    Options ypref{ };
};

// Non-member helpers
std::vector<PairsOfOpts> pair_generation( Population& listofagents );
std::vector<PairsOfOpts> pair_generation( Preferencematrix& mtx );

#endif // PAIRSOFOPTS_H
