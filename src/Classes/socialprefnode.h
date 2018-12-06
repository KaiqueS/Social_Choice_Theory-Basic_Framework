#pragma once

#ifndef SOCIALPREFNODE_H
#define SOCIALPREFNODE_H

#include <vector>
#include <iostream>

template <typename T, typename Parameter> class NamedType{

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
    SocialPrefNode( std::string self, int ind, int link, bool stack, std::vector<SocialPrefNode*> pref,
					std::vector<SocialPrefNode*> worse, std::vector<SocialPrefNode*> indiff );
    SocialPrefNode( const SocialPrefNode& copy );

    ~SocialPrefNode( );

    // Setters
    void set_id( std::string self );

	void set_index( int ind );
	void set_lowlink( int link );

	void set_onstack( bool stack );

    void set_pref( std::vector<SocialPrefNode*> prefs );
    void set_pref( SocialPrefNode& prefs );

    void set_worse( std::vector<SocialPrefNode*> wrs );
    void set_worse( SocialPrefNode& wrs );

    void set_indiff( std::vector<SocialPrefNode*> indiff );
    void set_indiff( SocialPrefNode& indiff );

    // Getters
    std::string get_id( ){ return id; }

	int get_index( ){ return index; }
	int get_lowlink( ){ return lowlink; }

	bool get_onstack( ){ return onstack; }

	std::vector<SocialPrefNode*> get_preferences( ){ return preferences; }
    std::vector<SocialPrefNode*> get_worse( ){ return worsethan; }
    std::vector<SocialPrefNode*> get_indiff( ){ return indifference; }

    // Operators
    SocialPrefNode& operator=( const SocialPrefNode& copy );

    using preferences_index = NamedType<std::ptrdiff_t, struct preferences_Parameter>;
    using worsethan_index = NamedType<std::ptrdiff_t, struct worsethan_Parameter>;
    using indifference_index = NamedType<std::ptrdiff_t, struct indifference_Parameter>;

    // One operator[ ] for each array index type
    SocialPrefNode* operator[ ]( preferences_index i ){ return preferences[ static_cast<std::vector<int>::size_type>( i.get( ) ) ]; }
    SocialPrefNode* operator[ ]( worsethan_index i ){ return worsethan[ static_cast<std::vector<int>::size_type>( i.get( ) ) ]; }
    SocialPrefNode* operator[ ]( indifference_index i ){ return indifference[ static_cast<std::vector<int>::size_type>( i.get( ) ) ]; }

private:

    std::string id{ };

	int index{ };
	int lowlink{ };

	bool onstack{ };

    std::vector<SocialPrefNode*> preferences{ };
    std::vector<SocialPrefNode*> worsethan{ };
    std::vector<SocialPrefNode*> indifference{ };
};

std::ostream& operator<<( std::ostream& os, SocialPrefNode& node );

#endif // SOCIALPREFNODE_H
