#include "D:\Trabalho\Projetos\Cpp\Social_Choice\Include\arrow_impossibility.hpp"

bool SCT::Arrow_Impossibility::operator( )( SCT::Procedure& procedure ){

	// If it is the case that every conditions is satisfied, then, check the structure of the preferences for single-
	// peakedness or anything that might have made it possible for the result to hold

	//std::cout << "Problem line 1\n";

	if( pareto( procedure ) == true ){

		if( irrelevant( procedure ) == true ){

			// then, according to arrow, non dictator must be false, i.e., there must be a dictator
			if( dictator( procedure ) == false ){

				// theorem complete and etc.
				return true;
			}

			else{

				return false;
			}
		}
	}
}

/// Non-member helpers