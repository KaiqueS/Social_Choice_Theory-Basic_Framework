#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <string>
#include "population.hpp"
#include "preferencematrix.hpp"
#include "sctrank.hpp"
#include "sctgraph.hpp"

// Get every case of !.empty( ) and put into an exception

class ExceptionHandler{

public:

    // Constructors & Destructor
    ExceptionHandler( );

	// Get all data while constructing the object. This means no setters
    ExceptionHandler( Options* opt, Profile* prof, Population* pop, Preferencematrix* mtx, Rank* ordering, Graph* nodes ) :
                        options( opt ), profile( prof ), population( pop ), matrix( mtx ), rank( ordering ), graph( nodes ){ }
	~ExceptionHandler( );

	// Setters

	// Getters

	// Operators

	// Helpers
	void option_handler( );
	void profile_handler( );

private:

    std::string warning{ };

	Options* options{ };
	Profile* profile{ };
    Population* population{ };
    Preferencematrix* matrix{ };
    Rank* rank{ };
    Graph* graph{ };
};

#endif // EXCEPTIONHANDLER_H
