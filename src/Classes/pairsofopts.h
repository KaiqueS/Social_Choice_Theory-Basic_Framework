#ifndef PAIRSOFOPTS_H
#define PAIRSOFOPTS_H

#include "options.h"

template<typename Prefs> struct PairsOfOpts{

	// Constructors & Destructor
	PairsOfOpts( );
	PairsOfOpts( const Options<Prefs>& optx, const Options<Prefs>& opty );
	PairsOfOpts( const PairsOfOpts<Prefs>& copy );

	~PairsOfOpts( ){ }

	// Operators
	PairsOfOpts& operator=( const PairsOfOpts& copy );

	// Members
	Options<Prefs> xpref{ };
	Options<Prefs> ypref{ };
};

/* Constructors & Destructor */

// Default constructor
template<typename Prefs> PairsOfOpts<Prefs>::PairsOfOpts( ){

	xpref = { };
	ypref = { };
}

// Parameterized constructor
template<typename Prefs> PairsOfOpts<Prefs>::PairsOfOpts( const Options<Prefs>& optx, const Options<Prefs>& opty ){

	xpref = optx;
	ypref = opty;
}

// Copy constructor
template<typename Prefs> PairsOfOpts<Prefs>::PairsOfOpts( const PairsOfOpts<Prefs>& copy ){

	xpref = copy.xpref;
	ypref = copy.ypref;
}

/* Operators */

// Overloaded assignment operator
template<typename Prefs> PairsOfOpts<Prefs>& PairsOfOpts<Prefs>::operator=( const PairsOfOpts<Prefs>& copy ){

	xpref = copy.xpref;
	ypref = copy.ypref;

	return *this;
}

#endif // PAIRSOFOPTS_H
