#pragma once

#ifndef PAIRWISERANK_H
#define PAIRWISERANK_H

#include "options.h"

template<typename Prefs> class PairWiseRank{

public:

	// Constructors & Destructor
	PairWiseRank( );
	PairWiseRank( const Options<Prefs>& x, const Options<Prefs>& y, const int& valx, const int& valy, const int& vali );
	PairWiseRank( const PairWiseRank<Prefs>& copy );

	~PairWiseRank( ){ }

	// Setters
	void set_optx( Options<Prefs> opt );
	void set_opty( Options<Prefs> opt );

	void set_xval( int val );
	void set_yval( int val );
	void set_ival( int val );

	void incrementx( ){ ++xval; }
	void incrementy( ){ ++yval; }
	void incrementi( ){ ++ival; }

	// Getters
	Options<Prefs> get_optx( );
	Options<Prefs> get_opty( );

	int get_xval( );
	int get_yval( );
	int get_ival( );

	// Operators
	PairWiseRank& operator=( const PairWiseRank<Prefs>& copy );

private:

	Options<Prefs> optx{ };
	Options<Prefs> opty{ };

	int xval{ };
	int yval{ };
	int ival{ };
};

/* Constructors & Destructor */

// Default constructor: initializes members to its default values
template<typename Prefs> PairWiseRank<Prefs>::PairWiseRank( ){

	optx = { };
	opty = { };

	xval = { };
	yval = { };
	ival = { };
}

// Parameterized constructor: initializes members accordingly to the arguments passed by
template<typename Prefs> PairWiseRank<Prefs>::PairWiseRank( const Options<Prefs>& x, const Options<Prefs>& y, const int& valx, const int& valy, const int& vali ){

	optx = x;
	opty = y;

	xval = valx;
	yval = valy;
	ival = vali;
}

// Copy constructor
template<typename Prefs> PairWiseRank<Prefs>::PairWiseRank( const PairWiseRank<Prefs>& copy ){

	optx = copy.optx;
	opty = copy.opty;

	xval = copy.xval;
	yval = copy.yval;
	ival = copy.ival;
}

/* Setters */

// Sets option x to opt
template<typename Prefs> void PairWiseRank<Prefs>::set_optx( Options<Prefs> opt ){ optx = opt; }

// Sets option y to opt
template<typename Prefs> void PairWiseRank<Prefs>::set_opty( Options<Prefs> opt ){ opty = opt; }

// Sets x's value as val. This value represents how x is ranked in the social ordering
template<typename Prefs> void PairWiseRank<Prefs>::set_xval( int val ){ xval = val; }

// Sets y's value as val. This value represents how y is ranked in the social ordering
template<typename Prefs> void PairWiseRank<Prefs>::set_yval( int val ){ yval = val; }

// Sets how many persons are indifferent between x and y, i.e., gave equal values to both of them
template<typename Prefs> void PairWiseRank<Prefs>::set_ival( int val ){ ival = val; }

/* Getters */

// Returns option x
template<typename Prefs> Options<Prefs> PairWiseRank<Prefs>::get_optx( ){ return optx; }

// Returns option y
template<typename Prefs> Options<Prefs> PairWiseRank<Prefs>::get_opty( ){ return opty; }

// Returns the number of votes given to x
template<typename Prefs> int PairWiseRank<Prefs>::get_xval( ){ return xval; }

// Returns the number of votes given to y
template<typename Prefs> int PairWiseRank<Prefs>::get_yval( ){ return yval; }

// Returns the number of votes given equally to both x and y
template<typename Prefs> int PairWiseRank<Prefs>::get_ival( ){ return ival; }

/* Operators */

// Overloaded assignment operator
template<typename Prefs> PairWiseRank<Prefs>& PairWiseRank<Prefs>::operator=( const PairWiseRank<Prefs>& copy ){

	optx = copy.optx;
	opty = copy.opty;

	xval = copy.xval;
	yval = copy.yval;
	ival = copy.ival;

	return *this;
}

#endif // PAIRWISERANK_H
