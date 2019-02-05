#include "options.hpp"

/* Constructors & Destructor */

// Default constructor. Initializes private properties to its default values
Options::Options( ){

    opt = "NULL";

    status = false;

    value = -1;
}

// Parameterized constructor. Initializes private properties based on the arguments passed by
Options::Options( std::string alts, bool stats, int val ){

	opt = alts;

    status = stats;

	value = val;
}

// Copy constructor. Initializes private properties based on the arguments passed by
Options::Options( const Options& copy ){

	opt = copy.opt;

    status = copy.status;

	value = copy.value;
}

/* Setters */

// Sets alternatives according to the argument passed through
void Options::set_opt( std::string newalt ){ opt = newalt; }

void Options::set_status( bool value  ){ status = value; }

// Sets values according to value passed as parameter
void Options::set_value( int val ){ value = val; }

/* Operators */

// Overloaded assignment operator
Options& Options::operator=( const Options& copy ){

	opt = copy.opt;

    status = copy.status;

	value = copy.value;

	return *this;
}

// Overloaded increment operator
Options& Options::operator++( ){

    value = value + 1;

    return *this;
}

// Compares options
bool Options::operator==( const Options& rhs ) const{

	if( opt == rhs.opt && value == rhs.value )

		return true;

	else

		return false;
}

// Check for correctness later
bool Options::operator<( const Options& rhs ){

    return value < rhs.value;
}

void Options::operator+=( const int val ){ value += val; }

// Prints option
std::ostream& operator<<( std::ostream& os, Options& opt ){

    os << "[ " << opt.get_opt( ) << ", " << opt.get_value( ) << " ]" ;

    return os;
}

