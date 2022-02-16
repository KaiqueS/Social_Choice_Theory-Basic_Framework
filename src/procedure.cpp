#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\procedure.hpp"

/* Desired behavior: if Procedure = Majority_rule, then, when receveing
 * an appropriate argument, Procedure will behave just as if it was a M
 * ajority_rule
 *
 * So, instead of doing Procedure::operator( ), it will, in turn, perfo
 * rm a Majority_rule::operator( ).
 *
 * Procedure must PRESERVE an acquired rule and perform its computation
 * when needed
*/

SCT::Procedure::~Procedure( ){ }

// Eu pego a matriz, construo o ranking, uso o ranking de referência
// pra ver quem ganha em cada par, pego só os profiles com a relação
// observada no ranking

void SCT::Decision_set::operator( )( Preferencematrix& matrix ){

	Rank social_order = make_social_order( matrix );

	Decisors decide{ };

	for( auto i = 0; i < social_order.size( ); ++i ){

		if( social_order[ i ].get_xval( ) > social_order[ i ].get_yval( ) ){

			decide.pair.xpref = social_order[ i ].get_optx( );
			decide.pair.ypref = social_order[ i ].get_opty( );

			decide.winner = social_order[ i ].get_optx( );
			decide.winner.set_value( social_order[ i ].get_xval( ) );

			for( auto j = 0; j < matrix.size( ); ++j ){

				if( *std::find( matrix[ j ].begin( ), matrix[ j ].end( ), social_order[ i ].get_optx( ) ) >
					*std::find( matrix[ j ].begin( ), matrix[ j ].end( ), social_order[ i ].get_opty( ) ) ){

					std::string identity = std::to_string( j );

					matrix[ j ].set_identifier( identity );

					decide.elements.push_back( &matrix[ j ] );
				}
			}

			decisor.push_back( decide );
		}

		else if( social_order[ i ].get_xval( ) < social_order[ i ].get_yval( ) ){

			decide.pair.xpref = social_order[ i ].get_optx( );
			decide.pair.ypref = social_order[ i ].get_opty( );

			decide.winner = social_order[ i ].get_opty( );
			decide.winner.set_value( social_order[ i ].get_yval( ) );

			for( auto j = 0; j < matrix.size( ); ++j ){

				if( *std::find( matrix[ j ].begin( ), matrix[ j ].end( ), social_order[ i ].get_optx( ) ) <
					*std::find( matrix[ j ].begin( ), matrix[ j ].end( ), social_order[ i ].get_opty( ) ) ){

					std::string identity = std::to_string( j );

					matrix[ j ].set_identifier( identity );

					decide.elements.push_back( &matrix[ j ] );
				}
			}

			decisor.push_back( decide );
		}

		decide = { };
	}
}

void SCT::Decision_set::intersect( ){

	if( !this -> decisor.begin( ) -> elements.empty( ) ){

		for( auto opt : this -> decisor.begin( ) -> elements ){

			for( auto letter : opt->get_alternatives( ) ){

				intersection.push_back( letter.get_opt( ) );
			}
		}
	}

		
}