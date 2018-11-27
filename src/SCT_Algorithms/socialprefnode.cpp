#include <typeinfo>
#include "Classes/socialprefnode.h"

/* Constructors & Destructor */

// Default constructor. Initializes members to its default values
SocialPrefNode::SocialPrefNode( ){

    id = "0";

	index = -1;
	lowlink = 0;

	onstack = false;

    preferences = { };
	worsethan = { };
	indifference = { };
}

// Parameterized constructor.
SocialPrefNode::SocialPrefNode( std::string self, int ind, int link, bool stack, std::vector<SocialPrefNode*> pref,
								std::vector<SocialPrefNode*> worse, std::vector<SocialPrefNode*> indiff ){

    id = self;

	index = ind;
	lowlink = link;

	onstack = stack;

    preferences = pref;
	worsethan = worse;
	indifference = indiff;
}

// Copy constructor
SocialPrefNode::SocialPrefNode( const SocialPrefNode& copy ){

    id = copy.id;

	index = copy.index;
	lowlink = copy.lowlink;

	onstack = copy.onstack;

    preferences = copy.preferences;
	worsethan = copy.worsethan;
	indifference = copy.indifference;
}

// Destructor
SocialPrefNode::~SocialPrefNode( ){ }

/* Setters */

// Sets SocialPreferenceNodes's id
void SocialPrefNode::set_id( std::string self ){

	if( typeid( self ) == typeid( nullptr ) ){

		std::cout << "Passing NULLPTR as argument. Initializing node's ID to default value 0.\n";

        self = '0';
	}

    else if( typeid( self ) == typeid( std::string ) )

		id = self;
}

void SocialPrefNode::set_index( int ind ){ index = ind; }

void SocialPrefNode::set_lowlink( int link ){ lowlink = link; }

void SocialPrefNode::set_onstack( bool stack ){ onstack = stack; }

// Gets a vector of pointers to SocialPrefNodes, sets PREFERENCES to the latter
void SocialPrefNode::set_pref( std::vector<SocialPrefNode*> prefs ){ preferences = prefs; }

// Gets an address to a SocialPrefNode, puts it into PREFERENCES vector
void SocialPrefNode::set_pref( SocialPrefNode& prefs ){ preferences.push_back( &prefs ); }

// Gets a vector of pointers to SocialPrefNodes, sets WORSETHAN to the latter
void SocialPrefNode::set_worse( std::vector<SocialPrefNode*> wrs ){ worsethan = wrs; }

// Gets an address to a SocialPrefNode, puts it into WORSETHAN vector
void SocialPrefNode::set_worse( SocialPrefNode& wrs ){ worsethan.push_back( &wrs ); }

// Gets a vector of pointers to SocialPrefNodes, sets INDIFFERENCE to the latter
void SocialPrefNode::set_indiff( std::vector<SocialPrefNode*> indiff ){ indifference = indiff; }

// Gets an address to a SocialPrefNode, puts it into INDIFFERENCE vector
void SocialPrefNode::set_indiff( SocialPrefNode& indiff ){ indifference.push_back( &indiff ); }

/* Getters */

/* Operators */

// Overloaded assignment operator
SocialPrefNode& SocialPrefNode::operator=( const SocialPrefNode& copy ){

    id = copy.id;

    index = copy.index;
    lowlink = copy.lowlink;

    onstack = copy.onstack;

    preferences = copy.preferences;
    worsethan = copy.worsethan;
    indifference = copy.indifference;

    return *this;
}

// Overloaded ostream operator
std::ostream& operator<<( std::ostream& os, SocialPrefNode& node ){

    os << "Node " << node.get_id( ) << "\nIs preferred to nodes: ";

    for( std::vector<int>::size_type i = 0; i < node.get_preferences( ).size( ); ++i ){

        os << "[ " << node.get_preferences( )[ i ] -> get_id( ) << " ] ";
    }

    os << "\nIs worse than nodes: ";

    for( std::vector<int>::size_type i = 0; i < node.get_worse( ).size( ); ++i ){

        os << "[ " << node.get_worse( )[ i ] -> get_id( ) << " ] ";
    }

    os << "\nIs equal to nodes: ";

    for( std::vector<int>::size_type i = 0; i < node.get_indiff( ).size( ); ++i ){

        os << "[ " << node.get_indiff( )[ i ] -> get_id( ) << " ] ";
    }

    os << "\n\n";

    return os;
}
