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

	//Getters
	Options<Prefs> getself( ){ return self; }

	Options<Prefs>* getpreferred( ){ return preferredto; }
	Options<Prefs>* getworse( ){ return worsethan; }

private:

	Options<Prefs> self{ };
	Options<Prefs>* preferredto{ };
	Options<Prefs>* worsethan{ };
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

#endif // SOCIALPREFNODE_H
