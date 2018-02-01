#include <iostream>
#include <vector>
#include <string>
#include <random>

#ifndef AGENT_H
#define AGENT_H

class Agent{

public:

	// Constructors
	Agent( );

	Agent( std::vector<Agent> list, std::string name );

	// Setters
	void set_ordering( std::vector<Agent>& list );
	void set_id( std::string name ){ id = name; }

	// Getters
	std::vector<Agent> get_preferences( ){ return preferences; }

	std::string get_id( ){ return id; }

	// Operators
	Agent& operator=( Agent one );

private:

	std::vector<Agent> preferences{ };

	std::string id{ }; // must be constant

};

// Helpers

std::ostream& operator<<( std::ostream& os, Agent one );

bool operator==( Agent& one, Agent& two );
bool operator!=( Agent& one, Agent& two );

struct PairOfAgents : public Agent{

	PairOfAgents( Agent man, Agent woman ) { one = man, two = woman; }

	Agent one, two;
};

std::ostream& operator<<( std::ostream& os, PairOfAgents& list );

#endif // AGENT_H
