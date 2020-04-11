#include "/Projetos/SocialChoice_VS/Include/non_dictatorship.hpp"

/// Constructors & Destructor

SCT::Non_Dictatorship::Non_Dictatorship( SCT::Non_Dictatorship&& copy ){

	matrix = copy.matrix;
	population = copy.population;
	rank = copy.rank;
	graph = copy.graph;

	copy.clear( );
}
SCT::Non_Dictatorship::Non_Dictatorship( const SCT::Non_Dictatorship& copy ){

	matrix = copy.matrix;
	population = copy.population;
	rank = copy.rank;
	graph = copy.graph;
}
SCT::Non_Dictatorship::~Non_Dictatorship( ){ clear( ); }

/// Setters

/// Getters

/// Operators

SCT::Non_Dictatorship& SCT::Non_Dictatorship::operator=( SCT::Non_Dictatorship copy ){

	swap( *this, copy );

	return *this;
}
SCT::Non_Dictatorship& SCT::Non_Dictatorship::operator=( SCT::Non_Dictatorship&& copy ){

	matrix = copy.matrix;
	population = copy.population;
	rank = copy.rank;
	graph = copy.graph;

	copy.clear( );

	return *this;
}

// Finds an agent that, whenever ONLY HER prefers x to y, the social order becomes xPy
// If is that the case that another person also prefers x to y, then the clause is not
// valid. Inform which agent is the dictator!
// To do so, define operator+= first
bool SCT::Non_Dictatorship::operator( )( SCT::Procedure& procedure ){

	return false;
}

/// Helpers

void SCT::Non_Dictatorship::clear( ){

	matrix.clear( );
	population.clear( );
	rank.clear( );
	graph.clear( );
}