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
    PairWiseRank( Options left, Options right ){ optx = left; 
                                                 opty = right; }
    PairWiseRank( const PairWiseRank& copy );
	PairWiseRank( PairWiseRank&& copy );
	~PairWiseRank( );

    // Setters
    void set_optx( Options opt );
    void set_opty( Options opt );

    void set_xval( int val );
    void set_yval( int val );
    void set_ival( int val );

    void incrementx( ){ ++xval; }
    void incrementy( ){ ++yval; }
    void incrementi( ){ ++ival; }

    // Getters
    Options get_optx( ) const{ return optx; } // removed return references
    Options get_opty( ) const{ return opty; } // removed return references

	int get_xval( ) const{ return xval; }
	int get_yval( ) const{ return yval; }
	int get_ival( ) const{ return ival; }

    // Operators
    PairWiseRank& operator=( const PairWiseRank& copy );
	PairWiseRank& operator=( PairWiseRank&& copy );

	// Helpers
	friend void swap( PairWiseRank& left, PairWiseRank& right );

	void clear( );

private:

    Options optx{ };
    Options opty{ };

    int xval{ };
    int yval{ };
    int ival{ };
};

// Non-member helpers
std::ostream& operator<<( std::ostream& os, PairWiseRank& rank );

bool relation_comparison( const PairWiseRank& left, const PairWiseRank& right );

inline bool operator==( const PairWiseRank& left, const PairWiseRank& right ){

	// Problem here: two PWR are equal if they
		// have the same optx and opty &&
		// hold the same relations between x and y
//	if( left.get_optx( ) == right.get_optx( ) &&
//		left.get_opty( ) == right.get_opty( ) &&
//		left.get_xval( ) == right.get_xval( ) &&
//		left.get_yval( ) == right.get_yval( ) &&
//		left.get_ival( ) == right.get_ival( ) )

	if( left.get_optx( ) == right.get_optx( ) &&
		left.get_opty( ) == right.get_opty( ) &&
		relation_comparison( left, right ) == true )

		return true;

	else

		return false;
}
inline bool operator!=( const PairWiseRank& left, const PairWiseRank& right ){ return !operator==( left, right ); }

inline bool operator<( const PairWiseRank& left, const PairWiseRank& right ){

	return( ( ( left.get_xval( ) + left.get_yval( ) ) / 2 ) < ( ( right.get_xval( ) + right.get_yval( ) ) / 2 ) );
}
inline bool operator>( const PairWiseRank& left, const PairWiseRank& right ){ return !operator<( left, right ); }

#endif // PAIRWISERANK_H
