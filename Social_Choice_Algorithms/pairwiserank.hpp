#pragma once

#ifndef PAIRWISERANK_H
#define PAIRWISERANK_H

#include <iostream>
#include "options.hpp"

class PairWiseRank{

public:

    // Constructors & Destructor
    PairWiseRank( );
    PairWiseRank( Options xopt, Options yopt, int valx, int valy, int vali ) : optx( xopt ), opty( yopt ),
                                                                               xval( valx ), yval( valy ), ival( vali ){ }
    PairWiseRank( const PairWiseRank& copy );

    ~PairWiseRank( ){ }

    // Setters
    void set_optx( Options& opt );
    void set_opty( Options& opt );

    void set_xval( int val );
    void set_yval( int val );
    void set_ival( int val );

    void incrementx( ){ ++xval; }
    void incrementy( ){ ++yval; }
    void incrementi( ){ ++ival; }

    // Getters
    Options& get_optx( );
    Options& get_opty( );

    int get_xval( );
    int get_yval( );
    int get_ival( );

    // Operators
    PairWiseRank& operator=( const PairWiseRank& copy );

    bool operator==( const PairWiseRank right );

private:

    Options optx{ };
    Options opty{ };

    int xval{ };
    int yval{ };
    int ival{ };
};

// Non-member helpers

bool operator<( PairWiseRank& left, PairWiseRank& right );

std::ostream& operator<<( std::ostream& os, PairWiseRank& rank );

bool operator==( PairWiseRank left, PairWiseRank right );
bool operator!=( PairWiseRank left, PairWiseRank right );

#endif // PAIRWISERANK_H
