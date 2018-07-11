#pragma once

#ifndef SOCIALPREFNODE_H
#define SOCIALPREFNODE_H

#include "options.h"

// TODO: Search for a way to deal with pointer's problem - Array?

template<typename Prefs> class SocialPrefNode{

public:

	// Constructors & Destructor
	SocialPrefNode( );

	~SocialPrefNode( ){ }

	//Setters
	void setself( Options<Prefs> opt );

	void setpreferredto( Options<Prefs> opt );
	void setworse( Options<Prefs> opt );

	void incrmntprefto( ); // SHIT, FIX THIS
	void incrmntworse( );

	//Getters
	Options<Prefs> getself( ){ return self; }

	std::vector<Options<Prefs>*> getpreferred( ){ return preferredto; }
	std::vector<Options<Prefs>*> getworse( ){ return worsethan; }

private:

	Options<Prefs> self{ }; // Pointer or not pointer,
	std::vector<Options<Prefs>*> preferredto{ };// Use Arrays!
	std::vector<Options<Prefs>*> worsethan{ };

	// ints for xval, yval, ival - think about it later, this would just help visualize ingraph relations
};

/* Constructors */

template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( ){

	self = { };

	preferredto = nullptr;
	worsethan = nullptr;
}

/* Setters */

template<typename Prefs> void SocialPrefNode<Prefs>::setself( Options<Prefs> opt ){

	self.set_alternatives( opt.get_alternatives( ) );
	self.set_value( 0 );
}

template<typename Prefs> void SocialPrefNode<Prefs>::setpreferredto( Options<Prefs> opt ){ preferredto = &opt; }
template<typename Prefs> void SocialPrefNode<Prefs>::setworse( Options<Prefs> opt ){ worsethan = &opt; }

template<typename Prefs> void SocialPrefNode<Prefs>::incrmntprefto( ){ ++preferredto; }
template<typename Prefs> void SocialPrefNode<Prefs>::incrmntworse( ){ ++worsethan; }

#endif // SOCIALPREFNODE_H
