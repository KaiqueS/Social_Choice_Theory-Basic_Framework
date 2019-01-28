#pragma once

#ifndef SCT_ALGOS_HPP
#define SCT_ALGOS_HPP

#include "helper_functions.hpp"
#include "profile.hpp"
#include <deque>
#include <algorithm>

// TODO: remove use of graph. Instead, make every functor return a Profile.
// This profile will be used on the creation of graphs

namespace sct{

class Procedure{

    public:

        // Constructors & Destructor
        Procedure( ){ }
        ~Procedure( ){ }

        // Setters

        // Getters

        // Operators

        // Helpers
        //Profile& operator( )( Graph& graph );
        Profile& operator( )( Rank& rank );
    };

class Qualified_majority_rule : public Procedure{

    public:

		Qualified_majority_rule( ){ }
        ~Qualified_majority_rule( ){ }

        //Profile& operator( )( Graph& graph );
        Profile& operator( )( Rank& rank );

    private:

        Profile winnerset{ };
    };

class Borda_count : public Procedure{

    public:

        Borda_count( ){ }
        ~Borda_count( ){ }

        //Graph operator( )( Population& population );
        Profile& operator( )( Population& population );
        Profile& operator( )( Rank& rank );

    private:

        Profile winnerset{ };
};

//auto qualified_majority( Graph& graph ) -> std::string;
}

#endif // SCT_ALGOS_HPP
