#ifndef SOCIALPREFNODE_H
#define SOCIALPREFNODE_H

#include "options.h"

template<typename Prefs> class SocialPrefNode{

public:

	// Constructors & Destructor
	SocialPrefNode( );

	~SocialPrefNode( ){ }

	//Setters
	void setself( Options<Prefs> opt );

	void setpreferred( Options<Prefs> opt );
	void setworse( Options<Prefs> opt );

	void incrementpref( ); // SHIT, FIX THIS
	void incrementworse( );

	//Getters
	Options<Prefs> getself( ){ return self; }

	Options<Prefs>* getpreferred( ){ return preferredto; }
	Options<Prefs>* getworse( ){ return worsethan; }

private:

	Options<Prefs> self{ };
	Options<Prefs>* preferredto{ };// Use Arrays!
	Options<Prefs>* worsethan{ };

	// ints for xval, yval, ival
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

template<typename Prefs> void SocialPrefNode<Prefs>::setpreferred( Options<Prefs> opt ){ preferredto = &opt; }
template<typename Prefs> void SocialPrefNode<Prefs>::setworse( Options<Prefs> opt ){ worsethan = &opt; }

template<typename Prefs> void SocialPrefNode<Prefs>::incrementpref( ){ ++preferredto; }
template<typename Prefs> void SocialPrefNode<Prefs>::incrementworse( ){ ++worsethan; }

#endif // SOCIALPREFNODE_H
