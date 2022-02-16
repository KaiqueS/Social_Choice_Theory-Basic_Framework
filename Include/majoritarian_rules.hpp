#ifndef MAJORITARIAN_RULES_HPP
#define MAJORITARIAN_RULES_HPP

#include "procedure.hpp"

namespace SCT{

class Qualified_majority_rule : public Procedure{

    public:

       Qualified_majority_rule( ){ }
       //Qualified_majority_rule( Profile& winners ) : winnerset( winners ){ }
       ~Qualified_majority_rule( ){ /*winnerset.clear( ); */ }

	   virtual Profile operator( )( Preferencematrix& matrix );

       // Rethink this
       virtual Profile& operator+=( Profile& rhs );
       virtual Profile& operator+=( Preferencematrix& rhs );

    private:

        // is this really necessary? Cannot I deal only with temporaries of profiles?
        Profile winnerset{ };
    };

class Simple_majority_rule : public Procedure{

    public:

        Simple_majority_rule( ){ }
        // Simple_majority_rule( Profile& winners ) : winnerset( winners ){ }
        ~Simple_majority_rule( ) override { /*winnerset.clear( );*/ }

		virtual Profile operator( )( Preferencematrix& matrix ) override;

        virtual Profile& operator+=( Profile& rhs ) override;
        virtual Profile& operator+=( Preferencematrix& rhs ) override;

    private:

        Profile winnerset{ };
    };

class Two_rounds : public Procedure{

    public:

        Two_rounds( ){ }
        //Two_rounds( Profile& winner ) : winnerset( winner ){ }
        ~Two_rounds( ) override { /*winnerset.clear( );*/ }

        
        virtual Profile operator( )( Preferencematrix& matrix ) override;
        

        virtual Profile& operator+=( Profile& rhs ) override;
        virtual Profile& operator+=( Preferencematrix& rhs ) override;

    private:

        Profile winnerset{ };
    };
}

#endif // MAJORITARIAN_RULES_HPP
