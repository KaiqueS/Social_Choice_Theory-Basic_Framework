#include "/Projetos/SocialChoice_VS/Include/condorcet_paradox.hpp"

// TODO: use this only for the case where there are only three alternatives,
// so -> check rank and graph sizes, then check for condorcerity
bool SCT::Condorcet_Paradox::operator( )( Profile& profile ){

	int selection{ };

	Graph result{ };

	std::cout << "Which data structure do you wish to use? 1- Rank 2- Graph: ";

	std::cin >> selection;

	if( selection != 1 && selection != 2 ){

		std::cerr << "Invalid options.\n";

		// Man... this smells like shit
		return SCT::Condorcet_Paradox::operator( )( profile );
	}

	// THIS IS SHITTY AF. Use recursion instead, for god's sake.
	else{

		if( selection == 1 ){

			// is this supposed to mean n * ( n - 1 ) / 2? Damn, boi, this is shitty
			if( ( ( ( rank.size( ) ^ 2 ) - rank.size( ) ) / 2 ) > 3 ){

				std::cerr << "Invalid number of options. Condorcert only applies to cases where the number of options is 3. Use another rank.\n";

				return false;
			}

			else{

				Graph visited{ };

				for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

					SocialPrefNode actualnode( graph[ i ] );

					visited.push_back( actualnode );

					actualnode.set_onstack( true );

					for( long j = 0; j < static_cast< long >( actualnode.get_preferences( ).size( ) ); ++j ){

						if( actualnode[ SocialPrefNode::preferences_index{ j } ]->get_onstack( ) == false ){

							actualnode[ SocialPrefNode::preferences_index{ j } ]->set_onstack( true );

							visited.push_back( *actualnode[ SocialPrefNode::preferences_index{ j } ] );

							// FULL GAMBIARRA MODE ON
							actualnode = *actualnode[ SocialPrefNode::preferences_index{ j } ];

							j = 0;
						}

						else

							continue;
					}
				}
			}
		}

		else if( selection == 2 ){

			if( static_cast< int >( graph.size( ) ) != 3 ){

				std::cerr << "Invalid number of options. Condorcert only applies to cases where the number of options is 3. Use another rank.\n";

				return false;
			}

			else{

				Graph visited{ };

				for( std::vector<int>::size_type i = 0; i < graph.size( ); ++i ){

					SocialPrefNode actualnode( graph[ i ] );

					actualnode.set_onstack( true );

					visited.push_back( actualnode );

					for( long j = 0; j < static_cast< long >( actualnode.get_preferences( ).size( ) ); ++j ){

						if( actualnode[ SocialPrefNode::preferences_index{ j } ]->get_onstack( ) == false ){

							actualnode[ SocialPrefNode::preferences_index{ j } ]->set_onstack( true );

							visited.push_back( *actualnode[ SocialPrefNode::preferences_index{ j } ] );

							// FULL GAMBIARRA MODE ON
							actualnode = *actualnode[ SocialPrefNode::preferences_index{ j } ];

							--j;
						}

						else

							continue;
					}
				}

				result = visited;
			}
		}
	}

	for( std::vector<int>::size_type i = 0; i < result.size( ); ++i ){

		for( std::vector<int>::size_type j = 0; j < result.size( ); ++j ){

			if( j != i ){

				if( result[ j ].get_id( ) == result[ i ].get_id( ) ){

					std::cout << "There is a cycle!\n";

					return false;
				}
			}
		}
	}

	std::cout << "There are no cycles!\n";

	return true;
}