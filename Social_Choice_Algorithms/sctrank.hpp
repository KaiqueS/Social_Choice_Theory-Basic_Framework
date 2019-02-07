#pragma once

#ifndef SCTRANK_H
#define SCTRANK_H

#include <vector>
#include "pairwiserank.hpp"
#include "population.hpp"

class Rank{

public:

    // Constructors & Destructor
    Rank( );
    Rank( std::vector<PairWiseRank> ordering ) : ranking( ordering ){ }
    Rank( const Rank& copy );

    ~Rank( );

    // Setters
    void set_rank( PairWiseRank pair );
    void set_rank( std::vector<PairWiseRank> order );
	void generate_ranking( Population& listofagents );

    // Getters
    std::vector<PairWiseRank> get_rank( ){ return ranking; }

    std::vector<int>::size_type size( ){ return ranking.size( ); }

    // Operators
    Rank& operator=( const Rank& copy );

    PairWiseRank& operator[ ]( const std::vector<int>::size_type index  );

    // Helpers
	std::vector<PairWiseRank, std::allocator<PairWiseRank>>::iterator begin( ){ return ranking.begin( ); }
	std::vector<PairWiseRank, std::allocator<PairWiseRank>>::iterator end( ){ return ranking.end( ); }

	bool empty( );

	void push_back( PairWiseRank& rank ){ ranking.push_back( rank ); }
    void clear( ){ ranking.clear( ); }

private:

    std::vector<PairWiseRank> ranking{ };
};

void initialize_opts( Rank& rank, Profile& profile );

Profile make_social_order( /*std::vector<Agent>& listofagt,*/ Rank& rank );

#endif // SCTRANK_H
