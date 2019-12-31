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
        virtual Profile operator( )( Profile& profile ) override;
        virtual Profile operator( )( Preferencematrix& matrix ) override;
        virtual Profile& operator( )( Population& population ) override;

        virtual Profile& operator+=( Profile& profile ) override;
        virtual Profile& operator+=( Preferencematrix& matrix ) override;

    private:

        Profile winnerset{ };
    };

class First_past_the_post : public Procedure{

    public:

        //Graph operator( )( Population& population );
        virtual Profile operator( )( Profile& profile ) override;
        virtual Profile operator( )( Preferencematrix& matrix ) override;
        virtual Profile& operator( )( Population& population ) override;       

        virtual Profile& operator+=( Profile& profile ) override;
        virtual Profile& operator+=( Preferencematrix& matrix ) override;

    private:

    Profile winnerset{ };
};

}

#endif // PLURALITY_RULES_HPP
