#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include "population.hpp"
#include "profile.hpp"
#include "sctrank.hpp"

namespace SCT{

class Procedure{

    public:

        // Constructors & Destructor
        virtual ~Procedure( ) = 0;

        // Operators
        virtual void operator( )( Profile& profile ) = 0;
        virtual Profile& operator( )( Population& population ) = 0;
        virtual Profile& operator( )( Rank& rank ) = 0;
    };
}

#endif // PROCEDURE_HPP
