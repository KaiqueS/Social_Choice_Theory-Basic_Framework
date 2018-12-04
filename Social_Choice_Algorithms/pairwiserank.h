#pragma once

#ifndef PAIRWISERANK_H
#define PAIRWISERANK_H

#include <iostream>
#include "options.h"

class PairWiseRank{

public:

    // Constructors & Destructor
    PairWiseRank( );
    PairWiseRank( Options optx, Options opty, int xval, int yval, int ival );
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

private:

    Options optx{ };
    Options opty{ };

    int xval{ };
    int yval{ };
    int ival{ };
};

bool operator<( PairWiseRank& left, PairWiseRank& right );

std::ostream& operator<<( std::ostream& os, PairWiseRank& rank );

#endif // PAIRWISERANK_H
