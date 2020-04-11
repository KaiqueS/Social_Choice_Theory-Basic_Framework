#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "agent.hpp"

class Population{

public:

    // Constructors & Destructor
    Population( );
	Population( std::vector<int>::size_type size );
    Population( std::vector<Agent> people ) : population( people ){ }
	Population( std::initializer_list<Agent> list ) : population( std::move( list ) ){ }
    Population( Agent person );
    Population( const Population& copy );
	Population( Population&& copy );
	~Population( );

    // Setters
    void set_population( std::vector<Agent>& people );
    void set_population( Agent& people );

    // Getters
    std::vector<Agent> get_population( ) const{ return population; } // removed return by reference

    // Operators
    Population& operator=( const Population& copy );
	Population& operator=( Population&& copy );

    Agent& operator[ ]( const std::vector<int>::size_type index ){ return population[ index ]; }

    // Helpers
    std::vector<Agent, std::allocator<Agent>>::iterator begin( ){ return population.begin( ); }
    std::vector<Agent, std::allocator<Agent>>::iterator end( ){ return population.end( ); } // TODO: change this to one-beyond-last-element

	std::vector<int>::size_type size( ) const{ return population.size( ); }

	bool empty( );

	void initialize_population( Preferencematrix mtx );
    void order_preferences( );
    void push_back( Agent& agt ){ population.push_back( agt ); }
    void pop_back( ){ population.pop_back( ); }
    void clear( );

private:

    std::vector<Agent> population{ };
};

// Non-member Helpers
std::ostream& operator<<( std::ostream& os, Population& people );

void initialize_opts( Population& listofagents, Profile& opts );

// Deprecated - total NONSENSE
//Profile make_social_order( Population& population );

#endif // POPULATION_HPP
