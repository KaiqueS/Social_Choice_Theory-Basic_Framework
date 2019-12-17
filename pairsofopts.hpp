#ifndef PAIRSOFOPTS_H
#define PAIRSOFOPTS_H

//#include "options.hpp"
#include "population.hpp"

struct PairsOfOpts{

    // Constructors & Destructor
    PairsOfOpts( );
    PairsOfOpts( Options optx, Options opty ) : xpref( optx ), ypref( opty ){ }
    PairsOfOpts( const PairsOfOpts& copy );
	PairsOfOpts( PairsOfOpts&& copy );
	~PairsOfOpts( );

	// Setters

	// Getters

    // Operators
    PairsOfOpts& operator=( const PairsOfOpts& copy );
	PairsOfOpts& operator=( PairsOfOpts&& copy );

	// Helpers
	void clear( );

    // Members
    Options xpref{ };
    Options ypref{ };
};

/// Non-member helpers - TODO: NEEDS TESTING TO SEE IF CORRECT BEHAVIOR PERSISTS
inline bool operator==( const PairsOfOpts& left, const PairsOfOpts& right ){

	if( left.xpref == right.xpref &&
		right.ypref == right.ypref ){

		return true;
	}

	else{

		return false;
	}
}

inline bool operator!=( const PairsOfOpts& left, const PairsOfOpts& right ){ return !operator==( left, right ); }

// Non-member helpers
// std::vector<PairsOfOpts> pair_generation( Profile& profile );
//std::vector<PairsOfOpts> pair_generation( Population& listofagents );
//std::vector<PairsOfOpts> pair_generation( Preferencematrix& mtx );

#endif // PAIRSOFOPTS_H
