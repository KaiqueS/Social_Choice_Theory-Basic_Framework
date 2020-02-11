#pragma once

#include <vector>
#include <string>
#include <cmath>

const std::vector<std::string> alphabet( );

std::vector<int> num_of_elem( int size );

std::vector<std::string> zip_alphabet( std::vector<std::string> alpha, int remainder, int position, std::vector<int>::size_type recursion_depht );

std::vector<std::string> newtry( std::vector<std::string> alpha, int remainder );