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
    ExceptionHandler( std::string message, Population pop, Preferencematrix mtx, Rank ordering, Graph nodes ) :
                      warning( message ), population( pop ), matrix( mtx ), rank( ordering ), graph( nodes ){ }
    ~ExceptionHandler( );


private:

    std::string warning{ };

    Population population{ };
    Preferencematrix matrix{ };
    Rank rank{ };
    Graph graph{ };
};

#endif // EXCEPTIONHANDLER_H
