#include "/Projetos/SocialChoice_VS/Include/exceptionhandler.hpp"

/// Constructors & Destructor

ExceptionHandler::ExceptionHandler( ){

	warning = "Initializing exception handler./n";

	options = { };
	profile = { };
	population = { };
	matrix = { };
	rank = { };
	graph = { };
}

// Careful with the destructor. If its life ends before the lifetime of the objects pointed by it, then
// it may wipe data before it is used as intended. Guarantee that the destructor of the exceptions is
// the last thing being called
ExceptionHandler::~ExceptionHandler( ){

	warning.clear( );

	profile -> clear( );
	population -> clear( );
	matrix -> clear( );
	rank -> clear( );
	graph -> clear( );
}

/// Setters

/// Getters

/// Operators

/// Helpers

void ExceptionHandler::option_handler( ){


}

void ExceptionHandler::profile_handler( ){

	if( profile -> empty( ) ){


	}
}