#pragma once

#ifndef CYCLE_H
#define CYCLE_H

#include <vector>
#include <iostream>

class Cycle{

public:

    // Constructors & Destructor
    Cycle( );
    Cycle( std::string name, std::vector<std::string> way );
    Cycle( const Cycle& copy );

    ~Cycle( ){ }

    // Setters
    void set_id( std::string name );

    void set_path( std::vector<std::string> way );
    void set_path( std::string way );

    // Getters
    std::string get_id( ){ return id; }

    std::vector<std::string> get_path( ){ return path; }

    // Operators
    Cycle& operator=( const Cycle& copy );

    std::string& operator[ ]( const std::vector<int>::size_type& index );

private:

    std::string id{ };

    std::vector<std::string> path{ };
};

#endif // CYCLE_H
