#ifndef LISTOFPAIRS_HPP
#define LISTOFPAIRS_HPP

#include "pairsofopts.hpp"

class ListOfPairs{

public:

    // Constructos & Destructor
    ListOfPairs( );
    ListOfPairs( Population& population );
    ListOfPairs( Preferencematrix& matrix );
    ListOfPairs( std::vector<PairsOfOpts> list ) : pairs( list ){ }
    ListOfPairs( PairsOfOpts pair ){ pairs.push_back( pair ); }
    ListOfPairs( std::initializer_list<PairsOfOpts> init ) : pairs( std::move( init ) ){ }
    ListOfPairs( const ListOfPairs& copy ){ pairs = copy.pairs; }
	ListOfPairs( ListOfPairs&& copy ){ pairs = std::move( copy.pairs ); }
    ~ListOfPairs( );

    // Setters
    void set_pairs( std::vector<PairsOfOpts>& pair ){ pairs = pair; }

    // Getters
    std::vector<PairsOfOpts> get_pairs( ) const{ return pairs; }

    // Operators
    ListOfPairs operator=( const ListOfPairs& copy );
	ListOfPairs operator=( ListOfPairs&& copy );

    PairsOfOpts& operator[ ]( const std::vector<int>::size_type index ){ return pairs[ index ]; }

    // Helpers
	void pair_generation( Profile& profile );
    void pair_generation( Population& listofagents );
    void pair_generation( Preferencematrix& matrix );

    std::vector<PairsOfOpts, std::allocator<PairsOfOpts>>::iterator begin( ){ return pairs.begin( ); }
    std::vector<PairsOfOpts, std::allocator<PairsOfOpts>>::iterator end( ){ return pairs.end( ); }

    std::vector<int>::size_type size( ) const{ return pairs.size( ); }

    bool empty( ){ return pairs.empty( ); }

    void push_back( PairsOfOpts pair ){ pairs.push_back( pair ); }
    void pop_back( ){ pairs.pop_back( ); }
    void clear( );
    void erase( const std::vector<int>::size_type index );
    void erase( const PairsOfOpts& pair );
    void insert( std::vector<PairsOfOpts>::iterator position, PairsOfOpts pair ){ pairs.insert( position, pair ); }

private:

    std::vector<PairsOfOpts> pairs{ };
};

// Non-member helpers
std::ostream& operator<<( std::ostream& os, ListOfPairs& pairs );

inline bool operator==( const ListOfPairs& left, const ListOfPairs& right ){

    if( left.get_pairs( ) == right.get_pairs( ) )

        return true;

    else

        return false;
}
inline bool operator!=( const ListOfPairs& left, const ListOfPairs& right ){ return !operator==( left, right ); }

#endif // LISTOFPAIRS_HPP
