#ifndef PLURALITY_RULES_HPP
#define PLURALITY_RULES_HPP

#include "procedure.hpp"

namespace SCT{

class Borda_count : public Procedure{

    public:

        Borda_count( ){ }
        Borda_count( Profile& winners ) : winnerset( winners ){ }
        ~Borda_count( ) override { winnerset.clear( ); }

        //Graph operator( )( Population& population );
        virtual void operator( )( Profile& profile ) override;
        virtual Profile& operator( )( Population& population ) override;
        virtual Profile& operator( )( Rank& rank ) override;

    private:

        Profile winnerset{ };
    };
}

#endif // PLURALITY_RULES_HPP
