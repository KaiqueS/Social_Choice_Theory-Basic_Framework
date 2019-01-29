#ifndef SCTHEORY_H
#define SCTHEORY_H

#include "sctrank.hpp"
#include "aggregation_rules.hpp"
#include "sct_algos.hpp"

bool pareto_principle( Graph& graph , Rank& rank, std::vector<Options>& procedure );

bool irrelevant_alternatives( Preferencematrix& mtx, std::vector<Agent>& people );

bool non_dictatorship( std::vector<Agent>& people, Rank& rank, Graph& graph );

bool condorcet_paradox( std::vector<PairWiseRank>& rank, Graph& graph );

bool arrow_impossibility( std::vector<Agent>& listofagents, Preferencematrix& mtx , Rank& rank, Graph& graph, sct::Procedure& procedure );

#endif // SCTHEORY_H
