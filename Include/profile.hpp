#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <vector>
#include <random>
#include <algorithm>
#include <limits>
#include "options.hpp"

class Profile{

public:

    // Constructors & Destructor
    Profile( );
    Profile( bool value, bool opt, bool indiff, std::string id, std::vector<Options> alts ) : _value_sorted( value ), _opt_sorted( opt ), identifier( id ), indifference( indiff ), alternatives( alts ){ }
	Profile( std::initializer_list<Options> init ) : alternatives( std::move( init ) ){ }
    Profile( std::initializer_list<std::string> init );
    Profile( std::vector<int>::size_type size );
    Profile( Options opt );
    Profile( const Profile& copy );
	Profile( Profile&& copy );
    ~Profile( );

    // Setters
    void sorted_by_value( bool value ){ _value_sorted = value; }
    void sorted_by_opt( bool opt ){ _opt_sorted = opt; }

    void set_identifier( std::string id ){ identifier = id; }

    void set_alternatives( std::vector<Options>& alts );
    void set_alternatives( Options& opt );

    // Getters
    bool is_value_sorted( ) const;
	bool is_opt_sorted( ) const;

    std::string get_identifier( ){ return identifier; }

    std::vector<Options> get_alternatives( ) const{ return alternatives; } // removed return by reference

    // Operators
    Profile& operator=( const Profile& copy );
	Profile& operator=( Profile&& copy );

    Options& operator[ ]( const std::vector<int>::size_type index ){ return alternatives[ index  ]; }

    // Helpers
    std::vector<int>::size_type size( ) const{ return alternatives.size( ); }

    //std::vector<Options, std::allocator<Options>>::iterator begin( ){ return alternatives.begin( ); }
    //std::vector<Options, std::allocator<Options>>::iterator end( ){ return alternatives.end( ); } // TODO: return one-beyond-last-element

    auto begin( ){ return alternatives.begin( ); }
    auto end( ){ return alternatives.end( ); } // TODO: return one-beyond-last-element

    bool empty( );

    void push_back( Options opt ){ alternatives.push_back( opt ); }
    void clear( );
    void insert( std::vector<Options>::iterator pos, Options& opt ){ alternatives.insert( pos, opt ); }
    void erase( const std::vector<int>::size_type index );

	void merge_by_value( std::vector<int>::size_type start, std::vector<int>::size_type middle, std::vector<int>::size_type end );
	void merge_by_opt( std::vector<int>::size_type start, std::vector<int>::size_type middle, std::vector<int>::size_type end );

	void value_merge_sort( std::vector<int>::size_type start, std::vector<int>::size_type end );
	void opt_merge_sort( std::vector<int>::size_type start, std::vector<int>::size_type end );
	
	void sort_by_value( );
	void sort_by_opt( );
	
	void no_indifference( );

	friend void swap( Profile& left, Profile& right );

private:

    bool _value_sorted{ false };
    bool _opt_sorted{ false };
	bool indifference{ true }; // Default to TRUE?

    std::string identifier{ };

    std::vector<Options> alternatives{ };
};

// Non-Member Helpers
std::ostream& operator<<( std::ostream& os, Profile& profile );

// Two Profiles are equal if they hold the same set of alternatives AND if these are ranked equally.
// Implementation: assuming same size, same set of Options, and same range of values, sort by value.
// If two elements are NOT on the same ith position on both Profiles, then the Profiles are NOT equal.
// Why? When sorted by value, if x is not in the same position both in Left and Right, then the preferences
// differ by at least 2 alternatives: x and some y that occupy x's position in one profile.
inline bool operator==( const Profile& lhs, const Profile& rhs ){

    Profile left{ lhs }, right{ rhs };

    left.sort_by_value( );
    right.sort_by_value( );

    for( auto i = 0; i < right.size( ); ++i ){

        if( left[ i ] != right[ i ] ){

            return false;
        }

        else{

            continue;
        }
    }

    return true;
}
inline bool operator!=( const Profile& lhs, const Profile& rhs ){ return !operator==( lhs, rhs ); }

std::vector<int>::size_type find_opt( Profile profile, Options opt );

void merge( Profile& profile, std::vector<int>::size_type start, std::vector<int>::size_type middle, std::vector<int>::size_type end );
void merge_sort( Profile& profile, std::vector<int>::size_type start, std::vector<int>::size_type end );

#endif // PROFILE_HPP
