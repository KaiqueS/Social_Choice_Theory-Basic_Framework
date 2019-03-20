#ifndef MAJORITARIAN_RULES_HPP
#define MAJORITARIAN_RULES_HPP

#include "procedure.hpp"

namespace SCT{

class Qualified_majority_rule : public Procedure{

    public:

       Qualified_majority_rule( ){ }
       Qualified_majority_rule( Profile& winners ) : winnerset( winners ){ }
       ~Qualified_majority_rule( ){ winnerset.clear( ); }

	   virtual Profile operator( )( Profile& profile );
	   virtual Profile operator( )( Preferencematrix& matrix );
       virtual Profile& operator( )( Population& population );
       virtual Profile& operator( )( Rank& rank );

       virtual Profile& operator+=( Profile& rhs );
       virtual Profile& operator+=( Preferencematrix& rhs );
       virtual Profile& operator+=( Rank& rhs );

    private:

        Profile winnerset{ };
    };

class Simple_majority_rule : public Procedure{

    public:

        Simple_majority_rule( ){ }
        Simple_majority_rule( Profile& winners ) : winnerset( winners ){ }
        ~Simple_majority_rule( ) override { winnerset.clear( ); }

		virtual Profile operator( )( Profile& profile ) override;
		virtual Profile operator( )( Preferencematrix& matrix ) override;
        virtual Profile& operator( )( Population& population ) override;
        virtual Profile& operator( )( Rank& rank ) override;

        virtual Profile& operator+=( Profile& rhs ) override;
        virtual Profile& operator+=( Preferencematrix& rhs ) override;
        virtual Profile& operator+=( Rank& rhs ) override;

    private:

        Profile winnerset{ };
    };
}

#endif // MAJORITARIAN_RULES_HPP
