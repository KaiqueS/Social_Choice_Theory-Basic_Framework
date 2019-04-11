#ifndef PROPORTIONAL_RULES_HPP
#define PROPORTIONAL_RULES_HPP

#include "procedure.hpp"

namespace SCT{

class Proportional : public Procedure{

public:

    Proportional( ){ }
    Proportional( Profile& winners ) : winnerset( winners ){ }
    ~Proportional( ) override { winnerset.clear( ); }

	virtual Profile operator( )( Profile& profile ) override;
	virtual Profile operator( )( Preferencematrix& matrix ) override;
    virtual Profile& operator( )( Population& population ) override;
    virtual Profile& operator( )( Rank& rank ) override;

    virtual Profile& operator+=( Profile& profile ) override;
    virtual Profile& operator+=( Preferencematrix& matrix ) override;
    virtual Profile& operator+=( Rank& rank ) override;

private:

    Profile winnerset{ };
    };
}

#endif // PROPORTIONAL_RULES_HPP
