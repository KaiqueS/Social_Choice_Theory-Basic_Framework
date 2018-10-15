#pragma once

#ifndef NODEOPT_H
#define NODEOPT_H

#include "options.h"

template<typename Prefs> class NodeOpt{

public:

	// Constructors & Destructor
	NodeOpt( );
	NodeOpt( Options<Prefs> option, int link );
	NodeOpt( const NodeOpt& copy );

	~NodeOpt( );

	// Setters
	void set_opt( Options<Prefs> option );
	void set_opt( Prefs option );
	void set_opt( int option );

	void set_link( int link );

	void set_onstack( bool val );

	// Getters
	Options<Prefs> get_opt( ){ return opt; }

	int get_link( ){ return lowlink; }

	bool get_onstack( ){ return onstack; }

	// Operators
	NodeOpt& operator=( const NodeOpt& copy );

private:

	Options<Prefs> opt{ };

	int lowlink{ };

	bool onstack{ };
};

/* Constructors & Destructor */

template<typename Prefs> NodeOpt<Prefs>::NodeOpt( ){

	opt = { };

	lowlink = { };
}
template<typename Prefs> NodeOpt<Prefs>::NodeOpt( Options<Prefs> option, int link ){

	opt = option;

	lowlink = link;
}
template<typename Prefs> NodeOpt<Prefs>::NodeOpt( const NodeOpt& copy ){

	opt = copy.opt;

	lowlink = copy.lowlink;
}

/* Setters */

template<typename Prefs> void NodeOpt<Prefs>::set_opt( Options<Prefs> option ){ opt = option; }
template<typename Prefs> void NodeOpt<Prefs>::set_opt( Prefs option ){ opt.set_alternatives( option ); }
template<typename Prefs> void NodeOpt<Prefs>::set_opt( int option ){ opt.set_value( option ); }

/* Getters */

/* Operators */

template<typename Prefs> NodeOpt<Prefs>& NodeOpt<Prefs>::operator=( const NodeOpt& copy ){

	opt = copy.opt;

	lowlink = copy.lowlink;

	return *this;
}

#endif // NODEOPT_H
