#pragma once

#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <string>

class Options{

public:

	// Constructors & Destructor
	Options( );
    Options( std::string alts, int val );
	Options( const Options& copy );

	~Options( ){ }

	// Setters
    void set_opt( std::string newalt );
	void set_value( int val );

	// Getters
    std::string get_opt( ){ return opt; }

	int get_value( ){ return value; }

	// Operators
	Options& operator=( const Options& copy );

    Options& operator++( );

	bool operator==( const Options& rhs ) const;

private:

    std::string opt{ "NULL" };

    int value{ -1 };
};



std::ostream& operator<<( std::ostream& os, Options& opt );

#endif // OPTIONS_H
