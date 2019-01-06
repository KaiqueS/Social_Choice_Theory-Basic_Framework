#ifndef AGGREGATION_RULES_H
#define AGGREGATION_RULES_H

#include <algorithm>
#include "sctgraph.hpp"

/// Majority Rules

std::vector<Options> qualified_majority_rule( Graph& graph );

std::vector<Options> qualified_majority_rule( Rank& rank );

std::vector<Options> simple_majority_rule( Rank rank );

/// Counting Rules

std::vector<Options> borda_count( Rank rank );

std::vector<Options> borda_count( Graph& graph );

#endif // AGGREGATION_RULES_H
