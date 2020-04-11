#pragma once

#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <string>

// TODO: create a < or > operator

class Options{

public:

	// Constructors & Destructor
	Options( );
    Options( std::string alts, bool stats, int val ) : opt( alts ), status( stats ), value( val ){ }
	Options( std::string name );
	Options( const Options& copy );
	Options( Options&& copy );
	~Options( );

	// Setters
    void set_opt( std::string newalt );
    void set_status( bool value );
	void set_value( int val );

	// Getters
    std::string get_opt( ) const{ return opt; }

    bool get_status( ) const{ return status; }

	int get_value( ) const{ return value; }

	// Operators
	Options& operator=( const Options& copy );
	Options& operator=( Options&& copy );

    Options& operator++( );
    Options operator++( int value );

	Options& operator+=( const Options& val );
    Options& operator+=( const int val );

	// Helpers
	friend void swap( Options& left, Options& right );

	void clear( );

private:

    std::string opt{ "NULL" };

    bool status{ false };

    int value{ -1 };
};

// Non-member helpers
std::ostream& operator<<( std::ostream& os, Options& opt );

// Not comparing for values may cause trouble on IIA. Make sure to check for .value over there
inline bool operator==( const Options& left, const Options& right ){

	if( left.get_opt( ) == right.get_opt( ) )

		return true;

	else

		return false;
}
inline bool operator!=( const Options& left, const Options& right ){ return !operator==( left, right ); }

inline bool operator<( const Options& left, const Options& right ){

	return left.get_value( ) < right.get_value( );
}
inline bool operator>( const Options& left, const Options& right ){ return !operator<( left, right ); }
inline bool operator<=( const Options& left, const Options& right ){ return !operator>( left, right ); }
inline bool operator>=( const Options& left, const Options& right ){ return !operator<( left, right ); }

#endif // OPTIONS_H
