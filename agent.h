#include <iostream>
#include <vector>
#include <string>
#include <random>

#ifndef AGENT_H
#define AGENT_H

class Agent{

public:

	Agent( );

	std::vector<Agent> get_preferences( ){ return preferences; }

	bool get_status( );

	std::string get_id( ){ return id; }

	void set_preferences( std::vector<Agent> list );
	void set_ordering( std::vector<Agent> list );
	void operator=( Agent one );

	const void set_status( bool status );
	const void set_id( std::string name );

private:

	std::vector<Agent> preferences{ };

	bool status{ };

	std::string id{ }; // must be constant
};

struct PairOfAgents : public Agent{

	void set_agents( Agent one, Agent two );

	Agent one, two;
};

void set_pairs( std::vector<Agent> agents, std::vector<PairOfAgents>& list );

std::ostream& operator<<( std::ostream& os, Agent& one );

bool operator==( Agent& one, Agent& two );
bool operator!=( Agent& one, Agent& two );

#endif // AGENT_H
