#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <vector>
#include <random>
#include <algorithm>
#include "options.hpp"

class Profile{

public:

    // Constructors & Destructor
    Profile( );
    Profile( bool value, bool opt, std::vector<Options> alts ) : _value_sorted( value ), _opt_sorted( opt ), alternatives( alts ){ }
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
    bool is_ordered( );

    std::vector<Options>& get_alternatives( ){ return alternatives; }

    // Operators
    Profile& operator=( const Profile& copy );

    Options& operator[ ]( const std::vector<int>::size_type index ){ return alternatives[ index  ]; }

    bool operator==( const Profile& rhs );
    bool operator!=( const Profile& rhs );

    // Helpers
    std::vector<int>::size_type size( ){ return alternatives.size( ); }

    std::vector<Options, std::allocator<Options>>::iterator begin( ){ return alternatives.begin( ); }
    std::vector<Options, std::allocator<Options>>::iterator end( ){ return alternatives.end( ); }

    bool empty( );

    void push_back( Options opt ){ alternatives.push_back( opt ); }
    void clear( );
    void insert( std::vector<Options>::iterator pos, Options& opt ){ alternatives.insert( pos, opt ); }
    void erase( const std::vector<int>::size_type index );

	void sort_by_value( );
	void sort_by_opt( );

private:

    bool _value_sorted{ false };
    bool _opt_sorted{ false };

    std::vector<Options> alternatives{ };
};

// Non-Member Helpers
std::ostream& operator<<( std::ostream& os, Profile& profile );

bool operator==( const Profile& lhs, const Profile& rhs );

std::vector<int>::size_type find_opt( Profile profile, Options& opt );

#endif // PROFILE_HPP
