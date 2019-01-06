#pragma once

#ifndef SCTRANK_H
#define SCTRANK_H

#include <vector>
#include "pairwiserank.hpp"
#include "agent.hpp"

class Rank{

public:

    // Constructors & Destructor
    Rank( );
    Rank( std::vector<PairWiseRank> ordering );
    Rank( const Rank& copy );

    ~Rank( ){ }

    // Setters
    void set_rank( PairWiseRank pair );
    void set_rank( std::vector<PairWiseRank> order );
    void generate_ranking( std::vector<Agent>& listofagents );

    // Getters
    std::vector<PairWiseRank> get_rank( ){ return ranking; }

    std::vector<int>::size_type size( ){ return ranking.size( ); }

    // Operators
    Rank& operator=( const Rank& copy );

    PairWiseRank& operator[ ]( const std::vector<int>::size_type index  );

    // Helpers

    PairWiseRank* begin( ){ return ranking.begin( ).base( ); }
    PairWiseRank* end( ){ return ranking.end( ).base( ); }

private:

        std::vector<PairWiseRank> ranking{ };
};

#endif // SCTRANK_H
