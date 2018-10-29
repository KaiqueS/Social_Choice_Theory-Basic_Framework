#pragma once

#ifndef SOCIALPREFNODE_H
#define SOCIALPREFNODE_H

#include <vector>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsItem>

// TODO: Document this

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

private:

	char id{ };

	std::vector<SocialPrefNode*> preferences{ };
	std::vector<SocialPrefNode*> worsethan{ };
	std::vector<SocialPrefNode*> indifference{ };
};

/* Constructors & Destructor */

// Default constructor. Initializes members to its default values
template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( ){

	id = '0';

	preferences = { };
}

// Parameterized constructor.
template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( char self, std::vector<SocialPrefNode*> pref ){

	id = self;

	preferences = pref;
}

// Copy constructor
template<typename Prefs> SocialPrefNode<Prefs>::SocialPrefNode( const SocialPrefNode& copy ){

	id = copy.id;

	preferences = copy.preferences;
}

// Destructor
template<typename Prefs> SocialPrefNode<Prefs>::~SocialPrefNode( ){ }

/* Setters */

// Sets SocialPreferenceNodes's id
template<typename Prefs> void SocialPrefNode<Prefs>::set_id( char self ){

	if( !self ) // checking for nullptr

		self = '0';

	id = self;
}

// Gets a vector of pointers to SocialPrefNodes, sets PREFERENCES to the latter
template<typename Prefs> void SocialPrefNode<Prefs>::set_pref( std::vector<SocialPrefNode*> prefs ){ preferences = prefs; }

// Gets an address to a SocialPrefNode, puts it into PREFERENCES vector
template<typename Prefs> void SocialPrefNode<Prefs>::set_pref( SocialPrefNode& prefs ){ preferences.push_back( &prefs ); }

// Gets a vector of pointers to SocialPrefNodes, sets WORSETHAN to the latter
template<typename Prefs> void SocialPrefNode<Prefs>::set_worse( std::vector<SocialPrefNode*> wrs ){ worsethan = wrs; }

// Gets an address to a SocialPrefNode, puts it into WORSETHAN vector
template<typename Prefs> void SocialPrefNode<Prefs>::set_worse( SocialPrefNode& wrs ){ worsethan.push_back( &wrs ); }

// Gets a vector of pointers to SocialPrefNodes, sets INDIFFERENCE to the latter
template<typename Prefs> void SocialPrefNode<Prefs>::set_indiff( std::vector<SocialPrefNode*> indiff ){ indifference = indiff; }

// Gets an address to a SocialPrefNode, puts it into INDIFFERENCE vector
template<typename Prefs> void SocialPrefNode<Prefs>::set_indiff( SocialPrefNode& indiff ){ indifference.push_back( &indiff ); }

/* Getters */

/* Operators */

// Overloaded assignment operator
template<typename Prefs> SocialPrefNode<Prefs>& SocialPrefNode<Prefs>::operator=( const SocialPrefNode& copy ){

	id = copy.id;

	preferences = copy.preferences;

	return *this;
}

// Overloaded ostream operator
template<typename Prefs> std::ostream& operator<<( std::ostream& os, SocialPrefNode<Prefs>& node ){

	os << "Node " << node.get_id() << "\nIs preferred to nodes: ";

	for( std::vector<int>::size_type i = 0; i < node.get_preferences( ).size( ); ++i ){

		os << "[ " << node.get_preferences( )[ i ] -> get_id( ) << " ] ";
	}

	os << "\nIs worse than nodes: ";

	for( std::vector<int>::size_type i = 0; i < node.get_worse( ).size( ); ++i ){

		os << "[ " << node.get_worse( )[ i ] -> get_id( ) << " ] ";
	}

	os << "\nIs equal to nodes: ";

	for( std::vector<int>::size_type i = 0; i < node.get_indiff( ).size( ); ++i ){

		os << "[ " << node.get_indiff( )[ i ] -> get_id( ) << " ] ";
	}

	os << "\n\n";

	return os;
}

#endif // SOCIALPREFNODE_H
