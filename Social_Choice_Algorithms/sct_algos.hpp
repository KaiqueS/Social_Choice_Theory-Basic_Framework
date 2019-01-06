#pragma once

#ifndef SCT_ALGOS_HPP
#define SCT_ALGOS_HPP

#include "sctrank.hpp"
#include "sctgraph.hpp"
#include <deque>
#include <algorithm>

namespace sct{

    class Simple_majority_rule{

    public:

        Simple_majority_rule( );
        ~Simple_majority_rule( ){ }

        void operator( )( Graph& graph );
        void operator( )( Rank& graph );

    private:

        std::vector<Options> winnerset{ };
    };
}

#endif // SCT_ALGOS_HPP
