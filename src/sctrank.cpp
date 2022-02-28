#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\sctrank.hpp"
//include "listofpairs.hpp"
//#include "pairsofopts.hpp" -> Used to cause multiple definition problem if not included here

/// Constructors & Destructor

// Default constructor
Rank::Rank( ){ ranking = { }; }


Rank::Rank( Preferencematrix& matrix ){

	initialize( *matrix.begin( ) );

    generate_ranking( matrix );
    //order_ranking( );
}

// Copy constructor
Rank::Rank( const Rank& copy ){ ranking = copy.ranking; }

// Move constructor
Rank::Rank( Rank&& copy ) noexcept{

	ranking = std::move( copy.ranking );

	copy.clear( );
}

// Destructor. Clears RANKING from memory
Rank::~Rank( ){ clear( ); }

/// Setters


// Sets RANKING to order
void Rank::set_rank( std::vector<PairWiseRank> order ){

    ranking = order;

    // Added this later
    order_ranking( );
}

void Rank::generate_ranking( Preferencematrix& matrix ){

	for( auto i = 0; i < ranking.size( ); ++i ){

		for( auto line = 0; line < matrix.size( ); ++line){

			Options left( *std::find( matrix[ line ].begin( ), matrix[ line ].end( ), ranking[ i ].get_optx( ) ) );
			Options right( *std::find( matrix[ line ].begin( ), matrix[ line ].end( ), ranking[ i ].get_opty( ) ) );

			if( left > right ){

				ranking[ i ].incrementx( );
			}

			else{

				ranking[ i ].incrementy( );
			}
		}
	}
}

void Rank::initialize( Profile& profile ){

	for( auto i = 0; i < profile.size( ); ++i ){

		for( auto j = i + 1; j < profile.size( ); ++j ){

			PairWiseRank pair( profile[ i ], profile[ j ] );

			ranking.push_back( pair );
		}
	}
}

/// Getters

/// Operators

// Overloaded assignment operator
Rank& Rank::operator=( const Rank& copy ){

	ranking = copy.ranking;

    return *this;
}

Rank& Rank::operator=( Rank&& copy ) noexcept{

	ranking = std::move( copy.ranking );

	copy.clear( );

	return *this;
}

// Overloaded subscript operator. Returns a 5-tuple PairWiseRank of the form
// ( optx, opty, xval, yval, ival )
PairWiseRank& Rank::operator[ ]( const std::vector<int>::size_type index ){

    // Checks if RANKING is not empty
    if( !ranking.empty( ) ){

        // If it is not, and if index in within the range of RANKING
        if( ( static_cast<int>( index ) >= 0 ) && ( index < ranking.size( ) ) )

            // return PairWiseRank[ index ]
            return ranking[ index  ];

        // Else, if index is invalid
        else{

            std::cerr << "Invalid index. Please, enter another value between 0 <= x < " << ranking.size( ) << ": ";

            std::vector<int>::size_type newindex{ };

            // Get a new index
            std::cin >> newindex;

            return operator[ ]( newindex );
        }
    }

    // If RANKING is empty
    else{

        std::cerr << "Ranking is empty!. Creating a default ordered pair instead.\n\n";

        ranking.resize( 1 );

        // Return a default PairWiseRank
        return *ranking.begin( );
    }
}

/// Helpers

// Checks for transitivity. Returns true if, for any x, y, z, whenever ( x, y )
// and ( y, z ), then ( x, z ). With Rank, this means that, whenever xval > yval,
// and yval > zval, then xval > zval

// I do not think that transitivity checking should be here
bool Rank::is_transitive( ){

	/*class Transitivity{

	public:

		Transitivity( );
		~Transitivity( ){ }

		PairWiseRank get_left( ){ return left; }
		PairWiseRank get_right( ){ return right; }

	private:

		PairWiseRank left{ };
		PairWiseRank right{ };
	};*/

	for( std::vector<int>::size_type i = 0; i < ranking.size( ); ++i ){

		for( std::vector<int>::size_type j = i + 1; j < ranking.size( ); ++j ){

			if( ranking[ j ].get_optx( ) == ranking[ i ].get_opty( ) ){

				// maybe i should let k = 0?
				for( std::vector<int>::size_type k = i + 1; k < ranking.size( ); ++k ){

					if( ( ranking[ k ].get_optx( ) == ranking[ i ].get_optx( ) ) &&
						( ranking[ k ].get_opty( ) == ranking[ j ].get_opty( ) ) ){

						if( ( ranking[ i ].get_xval( ) > ranking[ i ].get_yval( ) ) &&
							( ranking[ j ].get_xval( ) > ranking[ j ].get_yval( ) ) &&
							( ranking[ k ].get_xval( ) > ranking[ k ].get_yval( ) ) ){

							std::cout << ranking[ i ] << "\n" << ranking[ j ] << "\n" << ranking[ k ] << "\t is transitive.\n"; // debug only
						}

						else{

							std::cout << ranking[ i ] << "\n" << ranking[ j ] << "\n" << ranking[ k ] << "\t is not transitive.\n"; // debug only

							return false;
						}
					}

					else

						continue;
				}
			}

			else

				continue;
		}
	}

	return true;
}

// Checks if RANKING is empty. Returns true if it is
bool Rank::empty( ){

	if( ranking.empty( ) )

		return true;

	else

		return false;
}

void Rank::clear( ){

	ranking.clear( );

	std::vector<PairWiseRank>( ).swap( ranking );
}

// Check for emptiness
void Rank::order_ranking( ){

	if( !ranking.empty( ) ){

		for( std::vector<int>::size_type i = 0; i < ranking.size( ); ++i ){

			if( ranking[ i ].get_optx( ).get_opt( ) > ranking[ i ].get_opty( ).get_opt( ) ){

				Options x = ranking[ i ].get_optx( );
				x.set_value( ranking[ i ].get_xval( ) );

				ranking[ i ].set_optx( ranking[ i ].get_opty( ) );
				ranking[ i ].set_xval( ranking[ i ].get_yval( ) );

				ranking[ i ].set_opty( x );
				ranking[ i ].set_yval( x.get_value( ) );
			}
		}

		for( std::vector<int>::size_type i = 0; i < ranking.size( ); ++i ){

			for( std::vector<int>::size_type j = i + 1; j < ranking.size( ); ++j ){

				if( ranking[ i ].get_optx( ).get_opt( ) > ranking[ j ].get_optx( ).get_opt( ) ){

					std::swap( ranking[ i ], ranking[ j ] );
				}

				else if( ranking[ i ].get_optx( ).get_opt( ) == ranking[ j ].get_optx( ).get_opt( ) ){

					if( ranking[ i ].get_opty( ).get_opt( ) > ranking[ j ].get_opty( ).get_opt( ) ){

						std::swap( ranking[ i ], ranking[ j ] );
					}
				}
			}
		}
	}

	// Think about this later
	else{

		std::cerr << "Cannot order an empty Rank.\n";

		return;
	}
}

/// Non-member Helpers

std::ostream& operator<<( std::ostream& os, Rank& rank ){

    for( std::vector<int>::size_type i = 0; i < rank.size( ); ++i )

        os << rank[ i ] << "\n";

    os << "\n";

    return os;
}

// ????????????
bool rank_relations( Rank& left, Rank& right ){

	for( std::vector<int>::size_type i = 0; i < left.size( ); ++i ){

		if( relation_comparison( left[ i ], right[ i ] ) == false )

			return false;

		else

			continue;
	}

	return true;
}
