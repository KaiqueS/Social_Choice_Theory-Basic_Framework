#include "agent.h"

//Class functions

// Default Constructor
Agent::Agent( ){

	preferences = {};

	id = "";

	status = false;
}

// Returns agent n's status
bool Agent::get_status( ){

	return status;
}

// Gale-Shepley algorithm, pairing and repairing
/*bool Agent::proposal( Agent& man, Agent& woman, std::vector<PairOfAgents>& list ){

	for( int i = 0; i < man.preferences.size( ); ++i ){

		if( man.preferences[ i ].get_status( ) == false ){

			for( int j = 0; j < woman.preferences.size( ); ++j ){

				if( woman.preferences[ j ] == man ){


				}
			}
		}
	}
}*/

// Receives a list of available agents. Randomly selects an element from the list.
// Puts selected element into preference.
void Agent::set_ordering( std::vector<Agent> list ){

	// TODO2: Check if the agent itself is not being included into its preferences vector - Done
	// TODO3: Optimize. LATER!
	// FIX: Sex being changed?????????????
	/*for( int i = 0; i < list.size( ); ++i ){

		if( list[ i ].get_id( ) == this -> id )

			list.erase( list.begin( ) + i );
	}*/

	// TODO: Check for double inputs of the same element, i.e., randomly select an
	// unique element - Done
	// TODO4: Find a better random number generator! - LATER!

	int flxcontrol = list.size( );

	while( flxcontrol > 0 ){

		int randindex = rand( ) % list.size( );

		if( list[ randindex ].get_id( ) != id ){

			preferences.push_back( list[ randindex ] );

			//list.erase( list.begin( ) + randindex );

		}

		--flxcontrol;
	}
}

// Self-explained
void Agent::operator=( Agent one ){

	id = one.get_id( );

	status = one.get_status( );

	preferences = one.get_preferences();
}

// Self-explained
const void Agent::set_status( bool stat ){

	// True = married, False = free
	status = stat;
}

// Self-explained. Find some way to automatize this
const void Agent::set_id( std::string name ){ id = name; }

//Non-member functions

std::ostream& operator<<( std::ostream& os, Agent& one ){

	return os << one.get_id();
}

bool operator==( Agent& one, Agent& two ){

	// Modified: deleted && one.get_status( ) == two.get_status( )
	if( one.get_id( ) == two.get_id( ) )

		return true;

	else

		return false;
}
bool operator!=( Agent& one, Agent& two ){

	if( one.get_id( ) == two.get_id( ) )

		return false;

	else

		return true;
}

// Sets pairs of agents. Actually, this is the Gale-Shepley algorithm
// TODO5: Check if there are two equal pairs in list!
void set_pairs( std::vector<Agent> agents, std::vector<PairOfAgents>& list ){

	for( int i = 0; i < agents.size( ); ++i ){

		// USE WHILE, DIPSHIT

		// If agent[ i ] is a man and is free
		if( agents[ i ].get_sex() == 'm' && agents[ i ].get_status() == false ){

			// If there is a w to whom m[ i ] has not proposed - should I add a list of proposed?
			// if the highest ranked w in m[ i ] is free - since who comes first is preferred
			// I just have to check if 'i' is married, after that, erase her from the prefere
			// nces - make a pair ( m[ i ], w )
			for( int j = 0; j < agents[ i ].get_preferences( ).size( ); ++j ){

				if( agents[ i ].get_preferences( )[ j ].get_sex( ) == 'f' ){

					// If not married, make a pair( m, w )
					if( agents[ i ].get_preferences( )[ j ].get_status() == false ){

						list.push_back( PairOfAgents( agents[ i ], agents[ i ].get_preferences( )[ j ] ) );

						agents[ i ].set_status( true );

						agents[ i ].get_preferences( )[ j ].set_status( true );

						agents[ i ].get_preferences( ).erase( agents[ i ].get_preferences( ).begin( ) + j );
					}

					// Else if married
					else if( agents[ i ].get_preferences( )[ j ].get_status( ) == true ){

						for( int k = 0; k < agents[ i ].get_preferences( )[ j ].get_preferences( ).size( ); ++k ){

							// If k < j, then w prefers m[ k ] to m[ j ], do not make a pair, erase w from m's list
							if( k < j ){

								agents[ i ].get_preferences( ).erase( agents[ i ].get_preferences( ).begin( ) + j );

								set_pairs( agents[ i ].get_preferences( ), list );
							}

							// If k > j, w: m > m', make a pair
							else if( k > j ){

								list.push_back( PairOfAgents( agents[ i ], agents[ i ].get_preferences( )[ j ] ) );

								agents[ i ].set_status( true );

								agents[ i ].get_preferences( )[ j ].set_status( true );

								agents[ i ].get_preferences( ).erase( agents[ i ].get_preferences( ).begin( ) + j );
							}
						}
					}
				}

				// else w is engaged to m'[ i ]

					// if w has m'[ i ] > m[ i ]

						// m[ i ] still free

					// else w has m[ i ] > m'[ i ]

						// make ( m[ i ], w ) a pair

						// make m'[ i ] free
			}
		}
	}

	// return list
}

std::ostream& operator<<( std::ostream& os, PairOfAgents& list ){

	return os << list.one.get_id( ) << ' ' << list.two.get_id( );
}
