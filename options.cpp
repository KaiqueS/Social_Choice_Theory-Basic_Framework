#include "/Projetos/SocialChoice_VS/Include/options.hpp"

/// Constructors & Destructor

// Default constructor. Initializes private properties to its default values
Options::Options( ){

    opt = "NULL";

    status = false;

    value = -1;
}

Options::Options( std::string name ){

	opt = name;

	status = false;

	value = -1;
}

// Copy constructor. Initializes private properties based on the arguments passed by
Options::Options( const Options& copy ){

	opt = copy.opt;
    status = copy.status;
	value = copy.value;
}

Options::Options( Options&& copy ){

	opt = std::move( copy.opt );

	status = std::move( copy.status );

	value = std::move( copy.value );

	copy.clear( );
}

Options::~Options( ){ clear( ); }

/// Setters

// Sets alternatives according to the argument passed through
void Options::set_opt( std::string newalt ){ opt = newalt; }

void Options::set_status( bool value  ){ status = value; }

// Sets values according to value passed as parameter
void Options::set_value( int val ){ value = val; }

/// Operators

// Overloaded assignment operator
Options& Options::operator=( const Options& copy ){

	opt = copy.opt;

	status = copy.status;

	value = copy.value;

	return *this;
}

Options& Options::operator=( Options&& copy ){

	opt = std::move( copy.opt );

	status = std::move( copy.status );

	value = std::move( copy.value );

	copy.clear( );

	return *this;
}

// Overloaded increment operator. TEST THIS
Options& Options::operator++( ){

    //value = value + 1;
    ++value;

    return *this;
}
Options Options::operator++( int value ){

	Options tmp( *this );

	operator++( );

	return tmp;
}

/// Helpers

void swap( Options& left, Options& right ){

	using std::swap;

	swap( left.opt, right.opt );
	swap( left.status, right.status );
	swap( left.value, right.value );
}

// Resets an instance to its default state
void Options::clear( ){

	opt.clear( );

	status = false;

	value = -1;
}

// Overloaded assign-increment operator. TEST THIS
Options& Options::operator+=( const Options& val ){ 
	
	value += val.value;

	return *this;
}
Options& Options::operator+=( const int val ){ 
	
	value += val;

	return *this;
}

/// Non-member helpers

// Prints option
std::ostream& operator<<( std::ostream& os, Options& opt ){

    os << "[ " << opt.get_opt( ) << ", " << opt.get_value( ) << " ]" ;

    return os;
}
