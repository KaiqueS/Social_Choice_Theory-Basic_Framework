#include "pairwiserank.hpp"

/* Constructors & Destructor */

// Default constructor: initializes members to its default values
PairWiseRank::PairWiseRank( ){

    optx = { };
    opty = { };

    xval = { };
    yval = { };
    ival = { };
}

// Parameterized constructor: initializes members accordingly to the arguments passed by
PairWiseRank::PairWiseRank( Options x, Options y, int valx, int valy, int vali ){

    optx = x;
    opty = y;

    xval = valx;
    yval = valy;
    ival = vali;
}

// Copy constructor
PairWiseRank::PairWiseRank( const PairWiseRank& copy ){

    optx = copy.optx;
    opty = copy.opty;

    xval = copy.xval;
    yval = copy.yval;
    ival = copy.ival;
}

/* Setters */

// Sets option x to opt
void PairWiseRank::set_optx( Options& opt ){

    optx = opt;
}

// Sets option y to opt
void PairWiseRank::set_opty( Options& opt ){

    opty = opt;
}

// Sets x's value as val. This value represents how x is ranked in the social ordering
void PairWiseRank::set_xval( int val ){ xval = val; }

// Sets y's value as val. This value represents how y is ranked in the social ordering
void PairWiseRank::set_yval( int val ){ yval = val; }

// Sets how many persons are indifferent between x and y, i.e., gave equal values to both of them
void PairWiseRank::set_ival( int val ){ ival = val; }

/* Getters */

// Returns option x
Options& PairWiseRank::get_optx( ){ return optx; }

// Returns option y
Options& PairWiseRank::get_opty( ){ return opty; }

// Returns the number of votes given to x
int PairWiseRank::get_xval( ){ return xval; }

// Returns the number of votes given to y
int PairWiseRank::get_yval( ){ return yval; }

// Returns the number of votes given equally to both x and y
int PairWiseRank::get_ival( ){ return ival; }

/* Operators */

// Overloaded assignment operator
PairWiseRank& PairWiseRank::operator=( const PairWiseRank& copy ){

    optx = copy.optx;
    opty = copy.opty;

    xval = copy.xval;
    yval = copy.yval;
    ival = copy.ival;

    return *this;
}

bool operator<( PairWiseRank& left, PairWiseRank& right ){

    return( ( ( left.get_xval( ) + left.get_yval( ) ) / 2 ) < ( ( right.get_xval( ) + right.get_yval( ) ) / 2 ) );
}

std::ostream& operator<<( std::ostream& os, PairWiseRank& rank ){

    os << "X: " << rank.get_optx( ).get_opt( )
       << "\tY: " << rank.get_opty( ).get_opt( )
       << "\tXval: " << rank.get_xval( )
       << "\tYval: " << rank.get_yval( )
       << "\tIval: " << rank.get_ival( );

    return os;
}
