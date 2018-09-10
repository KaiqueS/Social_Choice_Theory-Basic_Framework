#pragma once

#ifndef SOCIALPREFNODE_H
#define SOCIALPREFNODE_H

#include <set>
#include "options.h"
#include "agent.h"

template<typename Prefs> class SocialPrefNode{

public:

	// Constructors & Destructor
	SocialPrefNode( );
	SocialPrefNode( Options<Prefs>& itself, std::vector<Options<Prefs>>& preferred, std::vector<Options<Prefs>>& worse );
	SocialPrefNode( const SocialPrefNode<Prefs>& copy );

	~SocialPrefNode( ){ }

	//Setters
	void set_self( Options<Prefs>& opt );
	void set_preferredto( const Options<Prefs>& opt ); // FIX THIS SHIT
	void set_worse( const Options<Prefs>& opt ); // FIX THIS SHIT

	void set_numofedges( std::vector<Agent<Prefs>>& listofagents );

	// Getters
	Options<Prefs> get_self( ){ return self; }

	std::vector<Options<Prefs>*> get_preferred( ){ return preferredto; }
	std::vector<Options<Prefs>*> get_worse( ){ return worsethan; }

	// Operators
	SocialPrefNode& operator=( const SocialPrefNode<Prefs>& copy );

private:

	Options<Prefs> self{ }; // Pointer or not pointer, that is the question

	std::vector<Options<Prefs>*> preferredto{ };
	std::vector<Options<Prefs>*> worsethan{ };

	int preftosize{ 0 };
	int worsetsize{ 0 };
	// ints for xval, yval, ival - think about it later, this would just help visualize ingraph relations
};

/* Constructors */

template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( ){

	self = { };

	preferredto = { };
	worsethan = { };

	preftosize = 0;
	worsetsize = 0;
}
template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( Options<Prefs>& itself, std::vector<Options<Prefs>>& preferred, std::vector<Options<Prefs>>& worse ){

	self = itself;

	preferredto = preferred;
	worsethan = worse;
}
template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( const SocialPrefNode<Prefs>& copy ){

	self = copy.self;

	preferredto = copy.preferredto;
	worsethan = copy.worsethan;

	preftosize = copy.preftosize;
	worsetsize = copy.worsetsize;
}

/* Setters */

template<typename Prefs> void SocialPrefNode<Prefs>::set_self( Options<Prefs>& opt ){

	self.set_alternatives( opt.get_alternatives( ) );
	self.set_value( opt.get_value( ) );

	//self = opt;
}

template<typename Prefs> void SocialPrefNode<Prefs>::set_preferredto( const Options<Prefs>& opt ){ // If i do not pass by ref, a temp obj will be created, and i cannot

	Options<Prefs>* point = static_cast<const Options<Prefs>&>( opt );

	preferredto[ preftosize ] = ;

	++preftosize;
}
template<typename Prefs> void SocialPrefNode<Prefs>::set_worse( const Options<Prefs>& opt ){

	worsethan[ worsetsize ] = opt;

	++worsetsize;
}

template<typename Prefs> void SocialPrefNode<Prefs>::set_numofedges( std::vector<Agent<Prefs>>& listofagents ){

	preferredto.resize( listofagents[ 0 ].get_preferences( ).size( ) - 1 );
	worsethan.resize( listofagents[ 0 ].get_preferences( ).size( ) - 1 );
}

/* Getters */

/* Operators */

template<typename Prefs> SocialPrefNode<Prefs>& SocialPrefNode<Prefs>::operator=( const SocialPrefNode<Prefs>& copy ){

	self = copy.self;

	preferredto = copy.preferredto;
	worsethan = copy.worsethan;

	preftosize = copy.preftosize;
	worsetsize = copy.worsetsize;

	return *this;
}

#endif // SOCIALPREFNODE_H
