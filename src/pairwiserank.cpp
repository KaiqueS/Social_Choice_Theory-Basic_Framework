#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\pairwiserank.hpp"

/// Constructors & Destructor

// Default constructor: initializes members to its default values
PairWiseRank::PairWiseRank( ){

    optx = { };
    opty = { };

    xval = { };
    yval = { };
    ival = { };
}

// Copy constructor
PairWiseRank::PairWiseRank( const PairWiseRank& copy ){

    optx = copy.optx;
    opty = copy.opty;

    xval = copy.xval;
    yval = copy.yval;
    ival = copy.ival;
}

PairWiseRank::PairWiseRank( PairWiseRank&& copy ){

	optx = std::move( copy.optx );
	opty = std::move( copy.opty );

	xval = std::move( copy.xval );
	yval = std::move( copy.yval );
	ival = std::move( copy.ival );

	copy.clear( );
}

PairWiseRank::~PairWiseRank( ){ clear( ); }

/// Setters

// Sets option x to opt
void PairWiseRank::set_optx( Options opt ){ optx = opt; }

// Sets option y to opt
void PairWiseRank::set_opty( Options opt ){ opty = opt; }

// Sets x's value as val. This value represents how x is ranked in the social ordering
void PairWiseRank::set_xval( int val ){ xval = val; }

// Sets y's value as val. This value represents how y is ranked in the social ordering
void PairWiseRank::set_yval( int val ){ yval = val; }

// Sets how many persons are indifferent between x and y, i.e., gave equal values to both of them
void PairWiseRank::set_ival( int val ){ ival = val; }

/// Getters

/// Operators

// Overloaded assignment operator
PairWiseRank& PairWiseRank::operator=( const PairWiseRank& copy ){

	optx = copy.optx;
	opty = copy.opty;

	xval = copy.xval;
	yval = copy.yval;
	ival = copy.ival;

    return *this;
}

PairWiseRank& PairWiseRank::operator=( PairWiseRank&& copy ) noexcept{

	optx = std::move( copy.optx );
	opty = std::move( copy.opty );

	xval = std::move( copy.xval );
	yval = std::move( copy.yval );
	ival = std::move( copy.ival );

	copy.clear( );

	return *this;
}

/// Helpers

void swap( PairWiseRank& left, PairWiseRank& right ){

	using std::swap;

	swap( left.optx, right.optx );
	swap( left.opty, right.opty );
	swap( left.xval, right.xval );
	swap( left.yval, right.yval );
	swap( left.ival, right.ival );
}

void PairWiseRank::clear( ){

	optx.clear( );
	opty.clear( );

	xval = -1;
	yval = -1;
	ival = -1;
}

/// Non-member helpers

// Overloaded printing operator.
std::ostream& operator<<( std::ostream& os, PairWiseRank& rank ){

	os << "X: " << rank.get_optx( ).get_opt( )
	   << "\tY: " << rank.get_opty( ).get_opt( )
	   << "\tXval: " << rank.get_xval( )
	   << "\tYval: " << rank.get_yval( )
	   << "\tIval: " << rank.get_ival( );

    return os;
}

// What the fuck???????????
bool relation_comparison( const PairWiseRank& left, const PairWiseRank& right ){

	if( ( left.get_xval( ) > left.get_yval( ) && right.get_xval( ) > right.get_yval( ) ) ||
		( left.get_yval( ) > left.get_xval( ) && right.get_yval( ) > right.get_xval( ) ) ||
		( left.get_yval( ) == left.get_xval( ) && right.get_yval( ) == right.get_xval( ) ) ){

		return true;
	}

	else{

		return false;
	}
}
