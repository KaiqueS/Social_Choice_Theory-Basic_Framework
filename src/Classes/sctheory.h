#ifndef SCTHEORY_H
#define SCTHEORY_H
#include "Classes/helper_functions.h"
#include "Classes/aggregation_rules.h"

class SCTheory{

public:
	bool pareto_principle(std::vector<SocialPrefNode>& graph, std::vector<PairWiseRank>& rank);
	bool irrelevant_alternatives(std::vector<Agent> people, std::vector<SocialPrefNode>& graph);
	bool non_dictatorship(std::vector<Agent> people, std::vector<SocialPrefNode>& graph);
	void condorcet_paradox(std::vector<PairWiseRank>& rank, std::vector<SocialPrefNode>& graph);
	void arrow_impossibility(std::vector<Agent>& listofagents, std::vector<PairWiseRank>& rank, std::vector<SocialPrefNode>& graph);
};

#endif // SCTHEORY_H
