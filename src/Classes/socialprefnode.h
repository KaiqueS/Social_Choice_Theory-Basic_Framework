#pragma once

#ifndef SOCIALPREFNODE_H
#define SOCIALPREFNODE_H

#include <vector>
#include <iostream>

template<typename Prefs> class SocialPrefNode{

public:

	// Constructors & Destructor
	SocialPrefNode( );
	SocialPrefNode( char self, std::vector<SocialPrefNode*> pref );
	SocialPrefNode( const SocialPrefNode& copy );

	~SocialPrefNode( );

	// Setters
	void set_id( char self );

	void set_pref( std::vector<SocialPrefNode*> prefs );
	void set_pref( SocialPrefNode& prefs );

	void set_worse( std::vector<SocialPrefNode*> wrs );
	void set_worse( SocialPrefNode& wrs );

	void set_indiff( std::vector<SocialPrefNode*> indiff );
	void set_indiff( SocialPrefNode& indiff );

	// Getters
	char get_id( ){ return id; }

	std::vector<SocialPrefNode*> get_preferences( ){ return preferences; }
	std::vector<SocialPrefNode*> get_worse( ){ return worsethan; }
	std::vector<SocialPrefNode*> get_indiff( ){ return indifference; }


	// Operators
	SocialPrefNode& operator=( const SocialPrefNode& copy );

	//SocialPrefNode*& operator[ ]( const int index );

private:

	char id{ };

	std::vector<SocialPrefNode*> preferences{ };
	std::vector<SocialPrefNode*> worsethan{ };
	std::vector<SocialPrefNode*> indifference{ };
};

/* Constructors & Destructor */

template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( ){

	id = '0';

	preferences = { };
}
template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( char self, std::vector<SocialPrefNode*> pref ){

	id = self;

	preferences = pref;
}
template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( const SocialPrefNode& copy ){

	id = copy.id;

	preferences = copy.preferences;
}

template<typename Prefs> SocialPrefNode<Prefs>::~SocialPrefNode( ){ }

/* Setters */

template<typename Prefs> void SocialPrefNode<Prefs>::set_id( char self ){

	if( !self ) // checking for nullptr

		self = '0';

	id = self;
}

template<typename Prefs> void SocialPrefNode<Prefs>::set_pref( std::vector<SocialPrefNode*> prefs ){ preferences = prefs; }
template<typename Prefs> void SocialPrefNode<Prefs>::set_pref( SocialPrefNode& prefs ){ preferences.push_back( &prefs ); }

template<typename Prefs> void SocialPrefNode<Prefs>::set_worse( std::vector<SocialPrefNode*> wrs ){ worsethan = wrs; }
template<typename Prefs> void SocialPrefNode<Prefs>::set_worse( SocialPrefNode& wrs ){ worsethan.push_back( &wrs ); }

template<typename Prefs> void SocialPrefNode<Prefs>::set_indiff( std::vector<SocialPrefNode*> indiff ){ indifference = indiff; }
template<typename Prefs> void SocialPrefNode<Prefs>::set_indiff( SocialPrefNode& indiff ){ indifference.push_back( &indiff ); }

/* Getters */

/* Operators */

template<typename Prefs> SocialPrefNode<Prefs>& SocialPrefNode<Prefs>::operator=( const SocialPrefNode& copy ){

	id = copy.id;

	preferences = copy.preferences;

	return *this;
}

//template<typename Prefs> SocialPrefNode<Prefs>*& SocialPrefNode<Prefs>::operator[ ]( const int index ){ return preferences[ index ]; }

#endif // SOCIALPREFNODE_H
