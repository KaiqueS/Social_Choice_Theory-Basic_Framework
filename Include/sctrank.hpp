#pragma once

#ifndef SCTRANK_H
#define SCTRANK_H

#include <vector>
//#include <thread>
//#include <functional>
#include "pairwiserank.hpp"
#include "preferencematrix.hpp"
#include "listofpairs.hpp"

/* Class Description */

// A ranking of ever pair ( x, y ) in PreferenceMatrix.
// Counts in how many Profiles x > y and y > x

class Rank{

public:

    // Constructors & Destructor
    Rank( );
    Rank( Preferencematrix& matrix );
    Rank( std::vector<PairWiseRank> ordering ) : ranking( ordering ){ order_ranking( ); }
    Rank( std::initializer_list<PairWiseRank> init ) : ranking( std::move( init ) ){ order_ranking( ); }
    Rank( const Rank& copy );
	Rank( Rank&& copy ) noexcept;
    ~Rank( );

    // Setters
    
    void set_rank( std::vector<PairWiseRank> order );
    void generate_ranking( Preferencematrix& matrix );

    void initialize( Profile& profile );

    // Getters
    std::vector<PairWiseRank> get_rank( ) const{ return ranking; }

    std::vector<int>::size_type size( ) const{ return ranking.size( ); }

    // Operators
    Rank& operator=( const Rank& copy );
	Rank& operator=( Rank&& copy ) noexcept;

    PairWiseRank& operator[ ]( const std::vector<int>::size_type index  );

    // Helpers
	std::vector<PairWiseRank, std::allocator<PairWiseRank>>::iterator begin( ){ return ranking.begin( ); }
	std::vector<PairWiseRank, std::allocator<PairWiseRank>>::iterator end( ){ return ranking.end( ); }

	bool is_transitive( );
	bool empty( );

	void push_back( PairWiseRank& rank ){ ranking.push_back( rank ); }
	void clear( );
	void order_ranking( ); // Just in case the input is not lexicographically ordered

private:

    std::vector<PairWiseRank> ranking{ };
};

// Non-member helpers
std::ostream& operator<< ( std::ostream& os, Rank& rank );

// TODO: revise this. left == right iff all matching pairs x,y have the same xval,yval
inline bool operator==( const Rank& left, const Rank& right ){
	
	if( left.get_rank( ) == right.get_rank( ) )

		return true;

	else

		return false;
}
inline bool operator!=( const Rank& left, const Rank& right ){ return !operator==( left, right ); }

bool rank_relations( Rank& left, Rank& right );

#endif // SCTRANK_H
