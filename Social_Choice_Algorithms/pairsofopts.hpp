#ifndef PAIRSOFOPTS_H
#define PAIRSOFOPTS_H

#include "options.hpp"
#include "agent.hpp"

struct PairsOfOpts{

    // Constructors & Destructor
    PairsOfOpts( );
    PairsOfOpts( Options optx, Options opty );
    PairsOfOpts( const PairsOfOpts& copy );

    ~PairsOfOpts( ){ }

    // Operators
    PairsOfOpts& operator=( const PairsOfOpts& copy );

    // Members
    Options xpref{ };
    Options ypref{ };
};

#endif // PAIRSOFOPTS_H
