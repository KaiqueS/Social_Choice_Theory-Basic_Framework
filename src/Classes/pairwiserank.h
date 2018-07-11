#pragma once

#ifndef PAIRWISERANK_H
#define PAIRWISERANK_H

#include "options.h"

template<typename Prefs> class PairWiseRank{

public:

	// Constructors & Destructor
	PairWiseRank( );

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

private:

	Options<Prefs> optx{ };
	Options<Prefs> opty{ };

	int xval{ };
	int yval{ };
	int ival{ };
};

/* Constructors & Destructor */

template<typename Prefs> PairWiseRank<Prefs>::PairWiseRank( ){

	optx = { };
	opty = { };

	xval = { };
	yval = { };
	ival = { };
}

/* Setters */

template<typename Prefs> void PairWiseRank<Prefs>::set_optx( Options<Prefs> opt ){ optx = opt; }
template<typename Prefs> void PairWiseRank<Prefs>::set_opty( Options<Prefs> opt ){ opty = opt; }

template<typename Prefs> void PairWiseRank<Prefs>::set_xval( int val ){ xval = val; }
template<typename Prefs> void PairWiseRank<Prefs>::set_yval( int val ){ yval = val; }
template<typename Prefs> void PairWiseRank<Prefs>::set_ival( int val ){ ival = val; }

/* Getters */

template<typename Prefs> Options<Prefs> PairWiseRank<Prefs>::get_optx( ){ return optx; }
template<typename Prefs> Options<Prefs> PairWiseRank<Prefs>::get_opty( ){ return opty; }

template<typename Prefs> int PairWiseRank<Prefs>::get_xval( ){ return xval; }
template<typename Prefs> int PairWiseRank<Prefs>::get_yval( ){ return yval; }
template<typename Prefs> int PairWiseRank<Prefs>::get_ival( ){ return ival; }

#endif // PAIRWISERANK_H
