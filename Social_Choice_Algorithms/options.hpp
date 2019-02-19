#pragma once

#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <string>

// TODO: create a < operator

class Options{

public:

	// Constructors & Destructor
	Options( );
    Options( std::string alts, bool stats, int val ) : opt( alts ), status( stats ), value( val ){ }
	Options( const Options& copy );

	~Options( ){ }

	// Setters
    void set_opt( std::string newalt );
    void set_status( bool value );
	void set_value( int val );

	// Getters
    std::string get_opt( ){ return opt; }

    bool get_status( ){ return status; }

	int get_value( ){ return value; }

	// Operators
	Options& operator=( const Options& copy );

    Options& operator++( );

	bool operator==( const Options& rhs ) const;

    bool operator<( const Options& rhs );

    void operator+=( const int val );

private:

    std::string opt{ "NULL" };

    bool status{ false };

    int value{ -1 };
};

// Non-member helpers
std::ostream& operator<<( std::ostream& os, Options& opt );

bool operator==( Options& left, Options& right );

#endif // OPTIONS_H
