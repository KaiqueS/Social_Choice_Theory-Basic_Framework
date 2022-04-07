#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include "pairsofopts.hpp"
#include "sctrank.hpp"

// TODO: I have to find a way of building an ordering relation dependant on the chosen procedure

namespace SCT{

class Procedure{

    public:

        // Constructors & Destructor
        virtual ~Procedure( ) = 0;

        // Operators
        virtual Profile operator( )( Preferencematrix& matrix ) = 0;
        virtual Options operator( )( Options& left, Options& right, Preferencematrix& matrix ) = 0;

        // Helpers
        virtual void score( Preferencematrix& matrix ) = 0;
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

// NOTE: by design, for any pair ( a, b ), anyone in the decision set of the pair is
// NECESSARILY semi-decisive for that pair, EXCEPT when the size of the set equals
// the number of profile. In this case, we have pure decisiveness, by pareto condition.
// Why? Because anyone not in the set necessarily ranks ( a, b ) inversely! Since the
// sets just stores the profiles that ranks the winner from ( a, b ) higher. But, is
// it possible to have pure decisiveness when the set cardinality != number of profiles?
// If this were the case, then we would necessarily have a dictatorial profile.
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
