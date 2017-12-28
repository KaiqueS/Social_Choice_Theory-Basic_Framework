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

	bool get_status( ){ return status; }

	std::string get_id( ){ return id; }

	char get_sex( ){ return sex; }

	void operator=( Agent one );
	void set_ordering( std::vector<Agent> list );

	const void set_sex( char sex ){ this -> sex = sex; }
	const void set_status( bool stat );
	const void set_id( std::string name );

private:

	std::vector<Agent> preferences{ };

	bool status{ };

	std::string id{ }; // must be constant

	char sex{};
};

std::ostream& operator<<( std::ostream& os, Agent& one );

bool operator==( Agent& one, Agent& two );
bool operator!=( Agent& one, Agent& two );

struct PairOfAgents : public Agent{

	PairOfAgents( Agent man, Agent woman ) { one = man, two = woman; }

	Agent one, two;
};

//void set_pairs( std::vector<Agent> agents, std::vector<PairOfAgents>& list );

std::ostream& operator<<( std::ostream& os, PairOfAgents& list );

std::ostream& operator<<( std::ostream& os, PairOfAgents& list );

#endif // AGENT_H
