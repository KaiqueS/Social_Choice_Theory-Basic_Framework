#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include "Classes/agent.h"
#include "Classes/socialprefnode.h"
#include "Classes/cycle.h"
#include "Classes/pairwiserank.h"
#include "Classes/pairsofopts.h"

class Helper_functions{

public:


	static void initialize_graph(std::vector<Agent>& listofagents, std::vector<SocialPrefNode>& graph);
	static void initialize_opts(std::vector<Agent>& listofagents, std::vector<Options>& opts);
	static void print_graph(std::vector<SocialPrefNode>& graph);
	static void strong_connect(SocialPrefNode& v, std::vector<SocialPrefNode>& s, int& index);
	static std::vector<SocialPrefNode> tarjan(std::vector<SocialPrefNode>& graph);
	static std::vector<Cycle> check_cycle(std::vector<SocialPrefNode>& graph);
	static std::vector<Options> make_social_order(std::vector<Agent>& listofagt, std::vector<PairWiseRank>& rank);
	static std::vector<Options> make_social_order(std::vector<SocialPrefNode>& socialgraph);
	static std::vector<PairsOfOpts> pair_generation(std::vector<Agent>& listofagents);
	static std::vector<PairWiseRank> rank_generation(std::vector<Agent>& listofagents);
	static void make_graph(std::vector<Agent>& listofagents, std::vector<PairWiseRank>& rank, std::vector<SocialPrefNode>& graph);
	static Cycle make_paths(std::vector<SocialPrefNode> graph);

};

#endif // HELPER_FUNCTIONS_H
