#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

//#include "population.hpp"
//#include "profile.hpp"
#include "sctrank.hpp"

namespace SCT{

class Procedure{

    public:

        // Constructors & Destructor
        virtual ~Procedure( ) = 0;

        // Operators
        virtual Profile operator( )( Profile& profile ) = 0;
        virtual Profile operator( )( Preferencematrix& matrix ) = 0;
        virtual Profile& operator( )( Population& population ) = 0;
        virtual Profile& operator( )( Rank& rank ) = 0;

        virtual Profile& operator+=( Profile& rhs ) = 0;
        virtual Profile& operator+=( Preferencematrix& rhs ) = 0;
        virtual Profile& operator+=( Rank& rhs ) = 0;
    };
}

#endif // PROCEDURE_HPP
