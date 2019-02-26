#pragma once

#ifndef SCT_ALGOS_HPP
#define SCT_ALGOS_HPP

#include <deque>
#include <algorithm>
#include "population.hpp"
#include "profile.hpp"
#include "sctrank.hpp"

// TODO: remove use of graph. Instead, make every functor return a Profile.
// This profile will be used on the creation of graphs

// TODO: create headers for each type of procedure, and a header for the
// base class Procedure. If a procedure is a majority, put it in a header,
// if it is proportional, in another, etc..

namespace sct{

class Procedure{

    public:

        // Constructors & Destructor
        //Procedure( ){ }
        virtual ~Procedure( ){ }

        // Helpers
        //Profile& operator( )( Graph& graph );
		virtual Profile& operator( )( Population& population ) = 0;
		virtual Profile& operator( )( Rank& rank ) = 0;

    private:

        //Profile winnerset{ };
    };

class Qualified_majority_rule : public Procedure{

    public:

        Qualified_majority_rule( ){ }
        Qualified_majority_rule( Profile& winners ) : winnerset( winners ){ }
        ~Qualified_majority_rule( ){ winnerset.clear( ); }

        //Profile& operator( )( Graph& graph );
       virtual Profile& operator( )( Population& population );
       virtual Profile& operator( )( Rank& rank );

    private:

        Profile winnerset{ };
    };

class Simple_majority_rule : public Procedure{

    public:

        Simple_majority_rule( ){ }
		Simple_majority_rule( Profile& winners ) : winnerset( winners ){ }
        ~Simple_majority_rule( ){ winnerset.clear( ); }

		virtual Profile& operator( )( Population& population ) override;
		virtual Profile& operator( )( Rank& rank ) override;

    private:

        Profile winnerset{ };
    };

class Borda_count : public Procedure{

    public:

        Borda_count( ){ }
		Borda_count( Profile& winners ) : winnerset( winners ){ }
        ~Borda_count( ){ winnerset.clear( ); }

        //Graph operator( )( Population& population );
		virtual Profile& operator( )( Population& population ) override;
		virtual Profile& operator( )( Rank& rank ) override;

    private:

        Profile winnerset{ };
    };

class Proportional : public Procedure{

public:

    Proportional( ){ }
	Proportional( Profile& winners ) : winnerset( winners ){ }
    ~Proportional( ){ winnerset.clear( ); }

	virtual Profile& operator( )( Population& population ) override;
	virtual Profile& operator( )( Rank& rank ) override;

private:

    Profile winnerset{ };
    };

//auto qualified_majority( Graph& graph ) -> std::string;
}

#endif // SCT_ALGOS_HPP
