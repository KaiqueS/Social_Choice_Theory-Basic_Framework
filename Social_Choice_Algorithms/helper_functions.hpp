#pragma once

#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "pairsofopts.hpp"
#include "sctgraph.hpp"

std::vector<PairsOfOpts> pair_generation( std::vector<Agent>& listofagents );

void initialize_opts( std::vector<Agent>& listofagents, std::vector<Options>& opts );

void circuits( Graph& graph );

void johnson( Graph& graph );

std::vector<Options> make_social_order( std::vector<Agent>& listofagt, Rank& rank );

std::vector<Options> make_social_order( Graph& socialgraph );

#endif // HELPER_FUNCTIONS_H
