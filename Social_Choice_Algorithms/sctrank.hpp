#pragma once

#ifndef SCTRANK_H
#define SCTRANK_H

#include <vector>
#include <thread>
#include <pthread.h>
#include <functional>
#include "pairwiserank.hpp"
#include "population.hpp"

// TODO: solve problem when including listofpairs here. Problem solveng when removing #include population, profile from PROCEDURE class
#include "listofpairs.hpp"

/* Class Description */

class Rank{

public:

    // Constructors & Destructor
    Rank( );
    Rank( Preferencematrix& matrix ){ generate_ranking( matrix ); order_ranking( ); }
    Rank( std::vector<PairWiseRank> ordering ) : ranking( ordering ){ order_ranking( ); }
    Rank( std::initializer_list<PairWiseRank> init ) : ranking( std::move( init ) ){ order_ranking( ); }
    Rank( const Rank& copy );
    ~Rank( );

    // Setters
    void set_rank( PairWiseRank pair );
    void set_rank( std::vector<PairWiseRank> order );
	void generate_ranking( Population& listofagents );
    void generate_ranking( Preferencematrix& mtx );

    // Getters
    std::vector<PairWiseRank> get_rank( ) const{ return ranking; }

    std::vector<int>::size_type size( ) const{ return ranking.size( ); }

    // Operators
    Rank& operator=( Rank copy );

    PairWiseRank& operator[ ]( const std::vector<int>::size_type index  );

    // Helpers
	std::vector<PairWiseRank, std::allocator<PairWiseRank>>::iterator begin( ){ return ranking.begin( ); }
	std::vector<PairWiseRank, std::allocator<PairWiseRank>>::iterator end( ){ return ranking.end( ); }

	bool empty( );

	void push_back( PairWiseRank& rank ){ ranking.push_back( rank ); }
	void clear( );

	void order_ranking( );

private:

    std::vector<PairWiseRank> ranking{ };
};

// Non-member helpers
std::ostream& operator<< ( std::ostream& os, Rank& rank );

void initialize_opts( Rank& rank, Profile& profile );

Profile make_social_order( Rank& rank );

inline bool operator==( const Rank& left, const Rank& right ){
	
	if( left.get_rank( ) == right.get_rank( ) )

		return true;

	else

		return false;
}
inline bool operator!=( const Rank& left, const Rank& right ){ return !operator==( left, right ); }

bool rank_relations( Rank& left, Rank& right );

#endif // SCTRANK_H
