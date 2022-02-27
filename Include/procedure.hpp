#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

//#include "population.hpp"
//#include "profile.hpp"
#include "sctrank.hpp"

// TODO: I have to find a way of building an ordering relation dependant on the chosen procedure

namespace SCT{

class Procedure{

    public:

        // Constructors & Destructor
        virtual ~Procedure( ) = 0;

        // Operators
        virtual Profile operator( )( Preferencematrix& matrix ) = 0;

        // Both of these methods must be rethinked, so as not to throw away
        // processed information. I.e.: adding a profile or a matrix should
        // not make us recount all the votes from the start. We can use the
        // existing output and just calculate the effects of the new profile
        // on it.
        virtual Profile& operator+=( Profile& rhs ) = 0;
        virtual Profile& operator+=( Preferencematrix& rhs ) = 0;
        // virtual Profile& operator+=( Rank& rhs ) = 0;
    };

struct Decisors{

    std::vector<Profile*> elements{ };
    
    PairsOfOpts pair{ };

    Options winner{ };
    };

// DESIGN: decision sets will be fed to Procedures. The latter will use the former
//         to construct the social ordering. -> No need to do so. Decision sets
//         depends on preference matrixes, and procedures take matrixes as parameters.
//         Just build a decision set within a procedure.

// QUESTION: if the intersection of all decision sets is not empty, it must contain
//           one and only one profile. But, what to do when it is empty? Must we rely
//           on semi-decisiveness?
class Decision_set{

    public:

        // Constructors & Destructor
        Decision_set( ){ }
        ~Decision_set( ){ decisor.clear( ); }

        // Getters
        std::vector<Decisors> get_decisors( ){ return decisor; }

        // Operators
        void operator( )( Preferencematrix& matrix );
        
        // Methods
        void intersect( );

    private:

        std::vector<Decisors> decisor{ };
        std::vector<std::string> intersection{ };
    };
}

std::ostream& operator<<( std::ostream& os, SCT::Decision_set& set );

#endif // PROCEDURE_HPP
