#ifndef SCTHEORY_H
#define SCTHEORY_H

#include "sctrank.hpp"
#include "aggregation_rules.hpp"
#include "sct_algos.hpp"

namespace SCT{

    bool pareto_principle( Graph& graph , Rank& rank, Profile& procedure );

    bool irrelevant_alternatives( Preferencematrix& mtx, Population& people );

    bool non_dictatorship( Population& people, Rank& rank, Graph& graph );

    bool condorcet_paradox( Rank& rank, Graph& graph );

    bool is_singlePeaked( Rank& rank, Graph& graph );

    bool arrow_impossibility( Population& listofagents, Preferencematrix& mtx , Rank& rank, Graph& graph, sct::Procedure& procedure );
}

#endif // SCTHEORY_H
