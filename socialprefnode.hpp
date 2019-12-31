#pragma once

#ifndef SOCIALPREFNODE_H
#define SOCIALPREFNODE_H

#include <vector>
#include <iostream>
#include <string>

template<typename T, typename Parameter> class NamedType{

public:

    // Constructors & Destructor
    explicit NamedType( T const& value ) : value_( value ){ }
    explicit NamedType( T&& value ) : value_( std::move( value ) ){ }

    ~NamedType( ){ }

    // Getters
    T& get( ) { return value_; }
    T const& get( ) const { return value_; }

private:

    T value_{ };
};

class SocialPrefNode{

public:

    // Constructors & Destructor
    SocialPrefNode( );
    SocialPrefNode( std::string self, int ind, int distance, bool stack, std::vector<SocialPrefNode*> pref, std::vector<SocialPrefNode*> worse, std::vector<SocialPrefNode*> indiff ) :
                    id( self ), index( ind ), distance( distance ), onstack( stack ), preferences( pref ), worsethan( worse ), indifference( indiff ){ }
	SocialPrefNode( std::initializer_list<SocialPrefNode*> prefs, std::initializer_list<SocialPrefNode*> worse, std::initializer_list<SocialPrefNode*> ind ) :
					preferences( std::move( prefs ) ), worsethan( std::move( worse ) ), indifference( std::move( ind ) ){ }
    SocialPrefNode( const SocialPrefNode& copy );
	SocialPrefNode( SocialPrefNode&& copy );
    ~SocialPrefNode( );

    // Setters
    void set_id( std::string self );

	void set_index( int ind );
	void set_distance( int dist );
    void set_pi( SocialPrefNode* pie );

	void set_onstack( bool stack );

    void set_pref( std::vector<SocialPrefNode*> prefs );
    void set_pref( SocialPrefNode& prefs );

    void set_worse( std::vector<SocialPrefNode*> wrs );
    void set_worse( SocialPrefNode& wrs );

    void set_indiff( std::vector<SocialPrefNode*> indiff );
    void set_indiff( SocialPrefNode& indiff );

    // Getters
    std::string get_id( ) const{ return id; }

	int get_index( ) const{ return index; }
	int get_distance( ) const{ return distance; }
    
    SocialPrefNode* get_pi( ) const{ return pi; }

	bool get_onstack( ) const{ return onstack; }

    std::vector<SocialPrefNode*> get_preferences( ) const{ return preferences; }
    std::vector<SocialPrefNode*> get_worse( ) const{ return worsethan; }
    std::vector<SocialPrefNode*> get_indiff( ) const{ return indifference; }

    // Operators
    SocialPrefNode& operator=( const SocialPrefNode& copy );
	SocialPrefNode& operator=( SocialPrefNode&& copy );

	SocialPrefNode& operator+=( const SocialPrefNode& right ); // What is the meaning of these operators?
    SocialPrefNode& operator+=( const int val );

    using preferences_index = NamedType<std::ptrdiff_t, struct preferences_Parameter>;
    using worsethan_index = NamedType<std::ptrdiff_t, struct worsethan_Parameter>;
    using indifference_index = NamedType<std::ptrdiff_t, struct indifference_Parameter>;

    // One operator[ ] for each array index type - Document the use of this
    SocialPrefNode* operator[ ]( preferences_index i ){ return preferences[ static_cast<std::vector<int>::size_type>( i.get( ) ) ]; }
    SocialPrefNode* operator[ ]( worsethan_index i ){ return worsethan[ static_cast<std::vector<int>::size_type>( i.get( ) ) ]; }
    SocialPrefNode* operator[ ]( indifference_index i ){ return indifference[ static_cast<std::vector<int>::size_type>( i.get( ) ) ]; }

	// Helpers

	friend void swap( SocialPrefNode& left, SocialPrefNode& right );

	void clear( );

private:

    std::string id{ "NULL" };

    //int weight - the same as an opt value??????
    //  What about a set of ( SPN, value ) to represent weights of edges?
	int index{ -1 };
    int distance{ -1 };
	
    SocialPrefNode* pi{ };

	bool onstack{ false };

    std::vector<SocialPrefNode*> preferences{ };
    std::vector<SocialPrefNode*> worsethan{ };
    std::vector<SocialPrefNode*> indifference{ };
};

// Non-member helpers
std::ostream& operator<<( std::ostream& os, SocialPrefNode& node );

inline bool operator==( const SocialPrefNode& left, const SocialPrefNode& right ){

	if( left.get_id( ) == right.get_id( ) )

		return true;

	else

		return false;
}
inline bool operator!=( const SocialPrefNode& left, const SocialPrefNode& right ){ return !operator==( left, right ); }

inline bool operator<( const SocialPrefNode& left, const SocialPrefNode& right ){ return left.get_preferences( ).size( ) > right.get_preferences( ).size( ); }
inline bool operator>( const SocialPrefNode& left, const SocialPrefNode& right ){ return !operator<( left, right ); }

#endif // SOCIALPREFNODE_H
