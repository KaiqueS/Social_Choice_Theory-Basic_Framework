#pragma once

#ifndef SCTRANK_H
#define SCTRANK_H

#include <vector>
//#include <thread>
//#include <functional>
#include "pairwiserank.hpp"
#include "population.hpp"

// TODO: solve problem when including listofpairs here. Problem solven when removing #include population, profile from PROCEDURE class
#include "listofpairs.hpp"

// TODO: Miscounting when constructing a rank - Only happening with ICPC - Apparently it is not happening anymore

/* Class Description */

// Decision Set

class Rank{

public:

    // Constructors & Destructor
    Rank( );
    Rank( Population& population );
    Rank( Preferencematrix& matrix );
    Rank( std::vector<PairWiseRank> ordering ) : ranking( ordering ){ order_ranking( ); }
    Rank( std::initializer_list<PairWiseRank> init ) : ranking( std::move( init ) ){ order_ranking( ); }
    Rank( const Rank& copy );
	Rank( Rank&& copy );
    ~Rank( );

    // Setters
    void set_rank( PairWiseRank pair );
    void set_rank( std::vector<PairWiseRank> order );
    void generate_ranking( Profile& profile );
    void generate_ranking( Population& listofagents );
    void generate_ranking( Preferencematrix& mtx );

    // Getters
    std::vector<PairWiseRank> get_rank( ) const{ return ranking; }

    std::vector<int>::size_type size( ) const{ return ranking.size( ); }

    // Operators
    Rank& operator=( const Rank& copy );
	Rank& operator=( Rank&& copy );

    PairWiseRank& operator[ ]( const std::vector<int>::size_type index  );

    // Helpers
	std::vector<PairWiseRank, std::allocator<PairWiseRank>>::iterator begin( ){ return ranking.begin( ); }
	std::vector<PairWiseRank, std::allocator<PairWiseRank>>::iterator end( ){ return ranking.end( ); }

	bool is_transitive( );
	bool empty( );

	void push_back( PairWiseRank& rank ){ ranking.push_back( rank ); }
	void clear( );
	void order_ranking( );

private:

    std::vector<PairWiseRank> ranking{ };
};

// Non-member helpers
std::ostream& operator<< ( std::ostream& os, Rank& rank );

void initialize_opts( Rank& rank, Profile& profile ); // Useless after modifying below

Rank make_social_order( Preferencematrix& matrix );

inline bool operator==( const Rank& left, const Rank& right ){
	
	if( left.get_rank( ) == right.get_rank( ) )

		return true;

	else

		return false;
}
inline bool operator!=( const Rank& left, const Rank& right ){ return !operator==( left, right ); }

bool rank_relations( Rank& left, Rank& right );

#endif // SCTRANK_H
