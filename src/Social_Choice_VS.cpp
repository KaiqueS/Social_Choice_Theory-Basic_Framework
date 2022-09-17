#include <iostream>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <iterator>
#include <numeric>
//#include <thread>
#include "/Projetos/CPP/SocialChoice/Include/arrow_impossibility.hpp"
#include "/Projetos/CPP/SocialChoice/Include/majoritarian_rules.hpp"

//#include "/Projetos/SocialChoice_VS/Include/testing_grounds.hpp"

/// Backend TODO

// TODO: Exceptions for all classes/functions/methods that deal with vectors/containers -> Check for emptiness
// TODO: Revise Non-Dic - Focus on this now
// TODO: make it possible for one to enable/disable indifference -> FOCUS ON THIS! - DONE? .no_indifference()
// TODO: increasing_merge_sort and decreasing_merge_sort

// TODO: revise everything that uses ERASE
// TODO: implement I/O interface. I/O handling. Take databases and apply methods to it
// TODO: revise Profile and PreferenceMatrix operator==. IIA depends on it.
// TODO: implement methods to export data to .CSV. I can use special cases of PreferenceMatrix and
//       SCTGraph in unit testing!

/// GUI TODO

// TODO: make it possible for the user to select the edge set that will be used to make a graph, i.e.,
// wether the edges are being taken from preferred_to, worse_than, indifferent_to

/*void testing_func( int num ){

    std::vector<std::string> opts{ newtry( alphabet( ), num ) };

    for( std::vector<int>::size_type i = 0; i < opts.size( ); ++i ){

        std::cout << opts[ i ] << " ";
    }

    std::cout << "\n\n";
}*/

// Remember: use only TRANSITIVE matrixes!
void testing_dictator(Preferencematrix& matrix) {

    SCT::Qualified_majority_rule rule{ };
    Profile result = rule(matrix);

    SCT::Decision_set set{ };
    set(matrix);

    SCT::Decisors minimal{ *set.get_decisors( ).begin( ) }; // potential trouble

    for (auto i = 0; i < set.get_decisors().size(); ++i) {

        if (minimal.elements.size() > set.get_decisors()[i].elements.size()) {

            minimal = set.get_decisors()[i];
        }
    }

    Preferencematrix i{ }; // potential trouble
    Preferencematrix minimal_minus_i{ };
    Preferencematrix set_minus_minimal{ };

    Options smallest{ };
    Options greatest{ minimal.winner };

    if (minimal.pair.xpref != minimal.winner) {

        smallest = minimal.pair.xpref;
    }

    else {

        smallest = minimal.pair.ypref;
    }
    
    // now I have to split minimal into i, minimal - i, and set - minimal s.t.
      // i             = a b c
      // minimal - i   = c a b
      // set - minimal = b c a
  // to do so, i have to find a c s.t. this split happens
      // select i in minimal s.t. i is unique for c
      // let minimal_minus_i be minimal - i
      // set_minus_minimal is the rest

    for (auto first_prof = 0; first_prof < minimal.elements.size(); ++first_prof) {

        Profile first = *minimal.elements[first_prof];

        for (auto second_prof = first_prof + 1; second_prof < minimal.elements.size(); ++second_prof) {

            Profile second = *minimal.elements[second_prof];

            auto small_first = std::find(first.begin(), first.end(), smallest);
            auto small_second = std::find(second.begin(), second.end(), smallest);
            
            auto great_first = std::find(first.begin(), first.end(), greatest);
            auto great_second = std::find(second.begin(), second.end(), greatest);

            if (small_first <= great_second) {

                i.push_back(first);
                minimal_minus_i.push_back(second);
            }

            else {

                continue;
            }
        }
    }

    std::cout << i << "\n\n" << minimal_minus_i << "\n\n";
}

int main( ) {

    Preferencematrix left{ };

    bool tester = true;

    Graph graph{ };

    SCT::Qualified_majority_rule maj{};

    while (tester) {

        left.set_matrix(5, 5);
        graph.initialize(*left.begin());

        maj(left);

        graph.make_graph(left, maj);

        if (transitivity(graph)) {

            tester = false;
        }

        else {

            left.clear();
            graph.clear();
            maj = {};
        }
    }

    std::cout << left << '\n';

    testing_dictator(left);
}

