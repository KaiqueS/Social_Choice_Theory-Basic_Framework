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
    Profile( bool value, bool opt, std::vector<Options> alts ) : _value_sorted( value ), _opt_sorted( opt ), alternatives( alts ){ }
	Profile( std::initializer_list<Options> init ) : alternatives( std::move( init ) ){ }
    Profile( std::vector<int>::size_type size );
    Profile( Options opt );
    Profile( const Profile& copy );
    ~Profile( );

    // Setters
    void sorted_by_value( bool value ){ _value_sorted = value; }
    void sorted_by_opt( bool opt ){ _opt_sorted = opt; }

    void set_alternatives( std::vector<Options>& alts );
    void set_alternatives( Options& opt );

    // Getters
    bool is_value_sorted( ) const;
	bool is_opt_sorted( ) const;

    std::vector<Options> get_alternatives( ) const{ return alternatives; } // removed return by reference

    // Operators
    Profile& operator=( Profile copy );

    Options& operator[ ]( const std::vector<int>::size_type index ){ return alternatives[ index  ]; }

    // Helpers
    std::vector<int>::size_type size( ) const{ return alternatives.size( ); }

    std::vector<Options, std::allocator<Options>>::iterator begin( ){ return alternatives.begin( ); }
    std::vector<Options, std::allocator<Options>>::iterator end( ){ return alternatives.end( ); }

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
	
	friend void swap( Profile& left, Profile& right );

private:

    bool _value_sorted{ false };
    bool _opt_sorted{ false };

    std::vector<Options> alternatives{ };
};

// Non-Member Helpers
std::ostream& operator<<( std::ostream& os, Profile& profile );

// One must guarantee that lhs and rhs are sorted by opt, else, it may occur that
// lhs and rhs have the same opts with the same values, but, being the opts in a
// different order, the operator may understand that lhs != rhs
inline bool operator==( const Profile& lhs, const Profile& rhs ){

	if( lhs.get_alternatives( ) == rhs.get_alternatives( ) )

		return true;

	else

		return false;
}
inline bool operator!=( const Profile& lhs, const Profile& rhs ){ return !operator==( lhs, rhs ); }

std::vector<int>::size_type find_opt( Profile profile, Options opt );

void merge( Profile& profile, std::vector<int>::size_type start, std::vector<int>::size_type middle, std::vector<int>::size_type end );
void merge_sort( Profile& profile, std::vector<int>::size_type start, std::vector<int>::size_type end );

#endif // PROFILE_HPP
