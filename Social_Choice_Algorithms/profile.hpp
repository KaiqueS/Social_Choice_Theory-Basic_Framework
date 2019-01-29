#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <vector>
#include "options.hpp"

class Profile{

public:

    // Constructors & Destructor
    Profile( );
    Profile( std::vector<int>::size_type size );
    Profile( std::vector<Options> alts );
    Profile( Options opt );
    Profile( const Profile& copy );
    ~Profile( );

    // Setters
    void set_alternatives( std::vector<Options>& alts );
    void set_alternatives( Options& opt );

    // Getters
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

	void clear( ){ alternatives.clear( ); }

    void insert( std::vector<Options>::iterator pos, Options& opt ){ alternatives.insert( pos, opt ); }

    void erase( const int index ){ alternatives.erase( begin( ) + index ); }

private:

    std::vector<Options> alternatives{ };
};

std::ostream& operator<<( std::ostream& os, Profile& profile );

bool operator==( const Profile& lhs, const Profile& rhs );

#endif // PROFILE_HPP
