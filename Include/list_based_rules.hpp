#ifndef LIST_BASED_RULES_HPP
#define LIST_BASED_RULES_HPP

#include "procedure.hpp"

namespace SCT{

class Open_list : public Procedure{

public:

    // Constructors & Destructor
    Open_list( ){ }
    Open_list( Profile& winners ) : winnerset( winners ){ }
    ~Open_list( ) override { winnerset.clear( ); }

    // Setters

    // Getters

    // Operators
    virtual Profile operator( )( Profile& profile ) override;
    virtual Profile operator( )( Preferencematrix& matrix ) override;
    virtual Profile& operator( )( Population& population ) override;

    virtual Profile& operator+=( Profile& rhs ) override;
    virtual Profile& operator+=( Preferencematrix& rhs ) override;

    // Helpers

private:

    Profile winnerset{ };
    };

class Closed_list : public Procedure{

public:

    // Constructors & Destructor
    Closed_list( ){ }
    Closed_list( Profile& winners ) : winnerset( winners ){ }
    ~Closed_list( ) override { winnerset.clear( ); }

    // Setters

    // Getters

    // Operators
    virtual Profile operator( )( Profile& profile ) override;
    virtual Profile operator( )( Preferencematrix& matrix ) override;
    virtual Profile& operator( )( Population& population ) override;

    virtual Profile& operator+=( Profile& rhs ) override;
    virtual Profile& operator+=( Preferencematrix& rhs ) override;

    // Helpers

private:

    Profile winnerset{ };
    };

class Flexible_list : public Procedure{

public:

    // Constructors & Destructor
    Flexible_list( ){ }
    Flexible_list( Profile& winners ) : winnerset( winners ){ }
    ~Flexible_list( ) override { winnerset.clear( ); }

    // Setters

    // Getters

    // Operators
    virtual Profile operator( )( Profile& profile ) override;
    virtual Profile operator( )( Preferencematrix& matrix ) override;
    virtual Profile& operator( )( Population& population ) override;

    virtual Profile& operator+=( Profile& rhs ) override;
    virtual Profile& operator+=( Preferencematrix& rhs ) override;

    // Helpers

private:

    Profile winnerset{ };
    };

class Free_list : public Procedure{

public:

    // Constructors & Destructor
    Free_list( );
    Free_list( Profile& winners ) : winnerset( winners ){ }
    ~Free_list( ) override { winnerset.clear( ); }

    // Setters

    // Getters

    // Operators
    virtual Profile operator( )( Profile& profile ) override;
    virtual Profile operator( )( Preferencematrix& matrix ) override;
    virtual Profile& operator( )( Population& population ) override;

    virtual Profile& operator+=( Profile& rhs ) override;
    virtual Profile& operator+=( Preferencematrix& rhs ) override;

    // Helpers

private:

    Profile winnerset{ };
    };
}
#endif // LIST_BASED_RULES_HPP
