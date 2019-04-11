#include "exceptionhandler.hpp"

ExceptionHandler::ExceptionHandler( ){

    warning = { };

    population = { };
    matrix = { };
    rank = { };
    graph = { };
}

ExceptionHandler::~ExceptionHandler( ){

    warning.clear( );

    population.clear( );
    matrix.clear( );
    rank.clear( );
    graph.clear( );
}

