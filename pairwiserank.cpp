#include "pairwiserank.hpp"

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
PairWiseRank& PairWiseRank::operator=( PairWiseRank copy ){

	swap( *this, copy );

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

/// Non-member helpers

// Comparison operator. Returns true when the average of optx + opty of LEFT is smaller than
// opty + opty of Right. I.e., it means that a pair of options is greater than another when
// its average is greater.


// Overloaded printing operator.
std::ostream& operator<<( std::ostream& os, PairWiseRank& rank ){

    os << "X: " << rank.get_optx( ).get_opt( )
       << "\tY: " << rank.get_opty( ).get_opt( )
       << "\tXval: " << rank.get_xval( )
       << "\tYval: " << rank.get_yval( )
       << "\tIval: " << rank.get_ival( );

    return os;
}

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
