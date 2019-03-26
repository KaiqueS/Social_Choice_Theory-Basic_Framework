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
	Options get_optx( ) const{ return optx; }
	Options get_opty( ) const{ return opty; }

	int get_xval( ) const{ return xval; }
	int get_yval( ) const{ return yval; }
	int get_ival( ) const{ return ival; }

    // Operators
    PairWiseRank& operator=( PairWiseRank copy );

	// Helpers
	friend void swap( PairWiseRank& left, PairWiseRank& right );

private:

    Options optx{ };
    Options opty{ };

    int xval{ };
    int yval{ };
    int ival{ };
};

// Non-member helpers



std::ostream& operator<<( std::ostream& os, PairWiseRank& rank );

inline bool operator==( const PairWiseRank& left, const PairWiseRank& right ){

	if( left.get_optx( ) == right.get_optx( ) &&
		left.get_opty( ) == right.get_opty( ) &&
		left.get_xval( ) == right.get_xval( ) &&
		left.get_yval( ) == right.get_yval( ) &&
		left.get_ival( ) == right.get_ival( ) )

		return true;

	else

		return false;
}
inline bool operator!=( const PairWiseRank& left, const PairWiseRank& right ){ return !operator==( left, right ); }

inline bool operator<( const PairWiseRank& left, const PairWiseRank& right ){

	return( ( ( left.get_xval( ) + left.get_yval( ) ) / 2 ) < ( ( right.get_xval( ) + right.get_yval( ) ) / 2 ) );
}
inline bool operator>( const PairWiseRank& left, const PairWiseRank& right ){ return !operator<( left, right ); }

bool relation_comparison( const PairWiseRank& left, const PairWiseRank& right );

#endif // PAIRWISERANK_H
