#ifndef AGGREGATION_RULES_H
#define AGGREGATION_RULES_H

#include "Classes/pairwiserank.h"
#include "Classes/socialprefnode.h"

class Aggregation_rules{

public:

	static Options majority_rule(std::vector<SocialPrefNode>& graph);
	static Options majority_rule(std::vector<PairWiseRank>& rank);
	static void borda_count(std::vector<PairWiseRank>& rank);
};


#endif // AGGREGATION_RULES_H
