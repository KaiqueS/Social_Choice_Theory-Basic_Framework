#include "pairsofopts.hpp"

/* Constructors & Destructor */

// Default constructor
PairsOfOpts::PairsOfOpts( ){

    xpref = { };
    ypref = { };
}

// Parameterized constructor
PairsOfOpts::PairsOfOpts( Options optx, Options opty ){

    xpref = optx;
    ypref = opty;
}

// Copy constructor
PairsOfOpts::PairsOfOpts( const PairsOfOpts& copy ){

    xpref = copy.xpref;
    ypref = copy.ypref;
}

/* Operators */

// Overloaded assignment operator
PairsOfOpts& PairsOfOpts::operator=( const PairsOfOpts& copy ){

    xpref = copy.xpref;
    ypref = copy.ypref;

    return *this;
}


