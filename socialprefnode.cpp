#include <typeinfo>
#include "/Projetos/SocialChoice_VS/Include/socialprefnode.hpp"

/// Constructors & Destructor

// Default constructor. Initializes members to its default values
SocialPrefNode::SocialPrefNode( ){

    id = "0";

	index = -1;
	distance = 0;

	onstack = false;

    preferences = { };
	worsethan = { };
	indifference = { };
}

// Copy constructor
SocialPrefNode::SocialPrefNode( const SocialPrefNode& copy ){

    id = copy.id;

	index = copy.index;
	distance = copy.distance;

	onstack = copy.onstack;

    preferences = copy.preferences;
	worsethan = copy.worsethan;
	indifference = copy.indifference;
}

// Move constructor
SocialPrefNode::SocialPrefNode( SocialPrefNode&& copy ){

	id = std::move( copy.id );

	index = std::move( copy.index );
	distance = std::move( copy.distance );

	onstack = std::move( copy.onstack );

	preferences = std::move( copy.preferences );
	worsethan = std::move( copy.worsethan );
	indifference = std::move( copy.indifference );

	copy.clear( );
}

// Destructor. Clears every vector from memory
SocialPrefNode::~SocialPrefNode( ){

    preferences.clear( );
    worsethan.clear( );
    indifference.clear( );

    std::vector<SocialPrefNode*>( ).swap( preferences );
    std::vector<SocialPrefNode*>( ).swap( worsethan );
    std::vector<SocialPrefNode*>( ).swap( indifference );
}

/// Setters

// Sets SocialPreferenceNodes's id
void SocialPrefNode::set_id( std::string self ){

    // Checks for nullptr
	if( typeid( self ) == typeid( nullptr ) ){

		std::cout << "Passing NULLPTR as argument. Initializing node's ID to default value 0.\n";

        // If a nullptr is being passed, set id to default
        self = "0";
	}

    // If no nullptr is being passed, sets id to SELF
    else if( typeid( self ) == typeid( std::string ) )

		id = self;
}

// Sets SocialPrefNode index, i.e., its position in the array
void SocialPrefNode::set_index( int ind ){ index = ind; }

// Sets SocialPrefNode lowlink. Used in Johnson's algorithm
void SocialPrefNode::set_distance( int dist ){ distance = dist; }

void SocialPrefNode::set_pi( SocialPrefNode* pie ){ pi = pie; }

// Sets wether or not a node is on the stack. Used in Johnson's algorithm
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

/// Getters

/// Operators

// Overloaded assignment operator
SocialPrefNode& SocialPrefNode::operator=( const SocialPrefNode& copy ){

	id = copy.id;

	index = copy.index;
	distance = copy.distance;

	onstack = copy.onstack;

	preferences = copy.preferences;
	worsethan = copy.worsethan;
	indifference = copy.indifference;

    return *this;
}

// Overloaded move assignment
SocialPrefNode& SocialPrefNode::operator=( SocialPrefNode&& copy ){

	id = std::move( copy.id );

	index = std::move( copy.index );
	distance = std::move( copy.distance );

	onstack = std::move( copy.onstack );

	preferences = std::move( copy.preferences );
	worsethan = std::move( copy.worsethan );
	indifference = std::move( copy.indifference );

	copy.clear( );

	return *this;
}

// Overloaded binary arithmetic operator
SocialPrefNode& SocialPrefNode::operator+=( const SocialPrefNode& right ){ 
	
	index += right.index;
	
	return *this;
}
SocialPrefNode& SocialPrefNode::operator+=( const int val ){ 
	
	index += val;
	
	return *this;
}

/// Helpers

void swap( SocialPrefNode& left, SocialPrefNode& right ){

	using std::swap;

	swap( left.id, right.id );
	swap( left.index, right.index );
	swap( left.distance, right.distance );
	swap( left.pi, right.pi );
	swap( left.onstack, right.onstack );
	swap( left.preferences, right.preferences );
	swap( left.worsethan, right.worsethan );
	swap( left.indifference, right.indifference );
}

void SocialPrefNode::clear( ){

	id.clear( );

	index = -1;
	distance = -1;
	pi = { };

	std::vector<SocialPrefNode*>( ).swap( preferences );
	std::vector<SocialPrefNode*>( ).swap( worsethan );
	std::vector<SocialPrefNode*>( ).swap( indifference );

	preferences.clear( );
	worsethan.clear( );
	indifference.clear( );
}

/// Non-member helpers

// Overloaded ostream operator
std::ostream& operator<<( std::ostream& os, SocialPrefNode& node ){

	os << "Node " << node.get_id( ) << "\nIs preferred to nodes: ";

	for( std::vector<int>::size_type i = 0; i < node.get_preferences( ).size( ); ++i ){

		os << "[ " << node.get_preferences( )[ i ]->get_id( ) << " ] ";
	}

	os << "\nIs worse than nodes: ";

	for( std::vector<int>::size_type i = 0; i < node.get_worse( ).size( ); ++i ){

		os << "[ " << node.get_worse( )[ i ]->get_id( ) << " ] ";
	}

	os << "\nIs equal to nodes: ";

	for( std::vector<int>::size_type i = 0; i < node.get_indiff( ).size( ); ++i ){

		os << "[ " << node.get_indiff( )[ i ]->get_id( ) << " ] ";
	}

	os << "\n\n";

	return os;
}