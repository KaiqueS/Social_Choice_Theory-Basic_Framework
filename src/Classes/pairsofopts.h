#ifndef PAIRSOFOPTS_H
#define PAIRSOFOPTS_H

#include "options.h"

template<typename Prefs> struct PairsOfOpts{

	PairsOfOpts& operator=( PairsOfOpts copy );

	Options<Prefs> xpref{ };
	Options<Prefs> ypref{ };
};

template<typename Prefs> PairsOfOpts<Prefs>& PairsOfOpts<Prefs>::operator=( PairsOfOpts<Prefs> copy ){

	this -> xpref = copy.xpref;
	this -> ypref = copy.ypref;

	return *this;
}

#endif // PAIRSOFOPTS_H
