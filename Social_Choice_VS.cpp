#include <iostream>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <iterator>
#include <numeric>
//#include <thread>
#include "arrow_impossibility.hpp"
#include "majoritarian_rules.hpp"
#include "proportional_rules.hpp"
#include "list_based_rules.hpp"
#include "plurality_rules.hpp"

// TODO: Exceptions for all classes/functions/methods that deal with vectors/containers -> Check for emptiness
// TODO: Revise Non-Dic - Focus on this now
// TODO: allow choosing between a pure graph, i.e., graph not based on any aggregation procedure and
// a graph based on procedures - what would a PURE GRAPH be here? This makes no sense
// TODO: when allowing for used-defined aggregation procedures, use as example a custom threshold
// procedure, i.e., allow for the user to input a threshold that, when a given option surpasses
// the latter, it becomes the winner or one of the winners. Add that to GUI
// TODO: let the user decide between procedures - GUI
// TODO: make it possible for one to enable/disable indifference -> FOCUS ON THIS! - DONE? .no_indifference()
// TODO: make a container of alternatives. Let the agents push back the alternatives and assign a random value to them,
// this will make things more similar to how SCT works - This is not really necessary, and I could use PROFILE for that
// TODO: increasing_merge_sort and decreasing_merge_sort
// TODO: Miscounting when constructing a rank - URGENT! - Only happening with ICPC - Apparently it is not happening anymore - Stay alert
//       The problem happened because one was printing a SCMatrix while generating a rank from a Population, instead of the SCMatrix
// TODO: for all container wrapers with begin() and end(), return pointer to elements of container's type
// Found the error where ranking would not coincide with PrefMatrix: ranking was being generated from Population, instead
// of PreferenceMatrix
// Do not forget to test new version of Preferencematrix::Preferencematrix( std::vector<int>::size_type row, std::vector<int>::size_type col )
// PROVIDE: Move constructors and Move operator
// TODO: revise everything that uses ERASE
// TODO: remember to put breakpoints in .set_matrix() and .initialize_opts()
// How to guarantee reusing of Data Structures instances?
// I/O handling. Take databases and apply methods to it
// TODO: do not forget to solve set_matrix() and IIA combinatorial problems
// TODO: graph algorithms needs testing
// TODO: Fix problem SCTGraph.cpp


void test1() {

        Preferencematrix newmtx{ };

        newmtx.set_matrix(5, 5);
        std::cout << newmtx;

        Population listofagents(newmtx.size());
        listofagents.initialize_population(newmtx);
        std::cout << listofagents;

        std::cout << "\n";

        std::cout << listofagents[3] << "\n";

        std::cout << "\n";

        Rank rank{ };

        rank.generate_ranking(newmtx);

        std::cout << rank << "\n";

        //majority_rule( rank );

        std::cout << "\n";

        Graph graph{ };

        graph.initialize_graph(newmtx);

        graph.make_graph( rank );

        //std::thread graphthread( [ &graph, &newmtx, &rank ]( ){ graph.make_graph( newmtx, rank ); } );

        //graphthread.join( );

        //graph.make_graph( newmtx, rank.get_rank( ) );

        //std::cout << graph[ 0 ][ SocialPrefNode::worsethan_index{ 0 } ] -> get_id( ) << '\n';

        //qualified_majority_rule( graph );

        // Problem here: value > number of opts
        //make_social_order( listofagents, rank );

        std::cout << "\n";

        // Allow for the user to select which procedure does he wants to use

         //std::cin >> procedure
         //pass procedure as argument to arrow function

        SCT::Arrow_Impossibility arrow(newmtx, rank, listofagents, graph);

        SCT::Qualified_majority_rule maj;

        maj(listofagents);

        SCT::Simple_majority_rule majority;

        SCT::Proportional proport;

        SCT::Borda_count borda;

        Profile count = borda(listofagents);

        //Profile res = proport( listofagents );

        SCT::Borda_count bordinha;

        bordinha(listofagents);

        /*for( std::vector<int>::size_type i = 0; i < res.size( ); ++i ){

                if( res[ i ].get_status( ) == true )

                        std::cout << res[ i ] << " ";
        }*/

        //	std::cout << "\nProblem below!\n";

        //	bool truth = arrow( majority );

        //	std::cout << "Problem above!\n";

        //	if( truth )

        //		std::cout << "All right.\n\n";

        //	else

        //		std::cout << "Oh, damn!.\n\n";
}

void test2() {

        Graph graph{ };

        Preferencematrix mtx{ };

        Rank rank{ };

        mtx.set_matrix(45, 45);

        Population population(mtx.get_matrix().size());

        population.initialize_population(mtx);

        rank.generate_ranking(population);

        graph.initialize_graph(mtx);

        graph.make_graph( rank );

        SCT::Qualified_majority_rule maj{ };

        SCT::Borda_count count{ };

        SCT::Simple_majority_rule simple{ };

        Profile social = simple(population); // PROBLEM HERE

        //sct::Procedure newproc = { sct::Qualified_majority_rule( ) };

        Profile result = maj( mtx ); // MODIFIED

        Graph newgraph{ };

        Profile newres = count(population);

        std::cout << "The majority winner is: " << result[0] << "\n\n";

        std::cout << "The borda winner is: " << std::max_element(newres.begin(), newres.end())->get_opt() << "\n\n";

        std::cout << "The simple majority winner is: " << std::max_element(social.begin(), social.end())->get_opt() << "\n\n";

        for (std::vector<int>::size_type i = 0; i < result.size(); ++i) {

                std::cout << result[i] << " ";
        }

        std::cout << "\n\n";

        for (std::vector<int>::size_type i = 0; i < newres.size(); ++i) {

                std::cout << newres[i] << " ";
        }

        //std::string res = sct::qualified_majority( graph );

        std::cout << "\n\n";

        //std::cout << res;

        std::cout << "\n\n";
}

void test3() {

        Preferencematrix mtx{ };

        mtx.set_matrix(4, 4);

        Rank rank{ };

        rank.generate_ranking(mtx);

        std::cout << rank;

        Population pop{ };

        // Problem here
        pop.initialize_population(mtx);

        Profile prof{ };

        prof = mtx[2];

        Options opt = prof[1];

        find_opt(prof, opt);

        prof.sort_by_opt();

        Graph graph{ };

        graph.initialize_graph(pop);

        graph.make_graph( rank );

        SCT::Borda_count bordinha;

        SCT::Simple_majority_rule maj;

        SCT::Qualified_majority_rule newmaj;

        SCT::Arrow_Impossibility arrow(mtx, rank, pop, graph);

        //std::cout << arrow( newmaj ) << "\n";
}

void test4() {

        Profile testprof = { Options("d", false, 3), Options("b", false, 1), Options("c", false, 2), Options("a", false, 0) };
        Profile testprof2 = { Options("e", false, 4), Options("d", false, 3), Options("b", false, 1), Options("c", false, 2), Options("a", false, 0) };

        //merge_sort( testprof, 0, testprof.size( ) - 1 );
        //merge_sort( testprof2, 0, testprof2.size( ) - 1 );
        testprof.value_merge_sort(0, testprof.size() - 1);
        testprof2.value_merge_sort(0, testprof.size() - 1);

        Profile profile = { Options("d", false, 3), Options("b", false, 1), Options("c", false, 2), Options("a", false, 0) };

        profile.value_merge_sort(0, profile.size() - 1);

        std::cout << testprof << "\n";

        std::cout << testprof2 << "\n";

        std::cout << profile << "\n";
}

void test5() {

        Profile profile = { Options("a", false, 3) };

        Agent one = { "one", profile };

        Agent two = one;

        two.set_id("two");

        if (one == two)

                std::cout << "true\n";

        else

                std::cout << "false\n";

        std::cout << one << "\n" << two << "\n";

        Options opt{ "opt", false, 5 };
        Options opt2{ "opt2", false, 3 };

        if (opt > opt2)

                std::cout << "opt is greater than opt2\n";

        if (opt != opt2)

                std::cout << "opt is not opt2\n";

        std::cout << opt << "\n";

        opt += opt2;

        std::cout << opt;
}

void test6() {

        // Since I know that the second profile holds the same relations as the first, I could use it as a test case. Could test IIA's ranking_comparison to see if it generates the
        // second profile from the first to check for correctness

        Preferencematrix original = { Profile({ Options("a", false, 5), Options("b", false, 4), Options("c", false, 3), Options("d", false, 2), Options("e", false, 1) }),
                                                                  Profile({ Options("b", false, 5), Options("c", false, 4), Options("d", false, 3), Options("e", false, 2), Options("a", false, 1) }),
                                                                  Profile({ Options("c", false, 5), Options("d", false, 4), Options("e", false, 3), Options("a", false, 2), Options("b", false, 1) }),
                                                                  Profile({ Options("d", false, 5), Options("e", false, 4), Options("a", false, 3), Options("b", false, 2), Options("c", false, 1) }),
                                                                  Profile({ Options("e", false, 5), Options("a", false, 4), Options("b", false, 3), Options("c", false, 2), Options("d", false, 1) }) };

        Preferencematrix prime = { Profile({ Options("c", false, 5), Options("d", false, 4), Options("e", false, 3), Options("a", false, 2), Options("b", false, 1) }),
                                                                  Profile({ Options("e", false, 5), Options("d", false, 4), Options("a", false, 3), Options("b", false, 2), Options("c", false, 1) }),
                                                                  Profile({ Options("c", false, 5), Options("b", false, 4), Options("a", false, 3), Options("d", false, 2), Options("e", false, 1) }),
                                                                  Profile({ Options("b", false, 5), Options("d", false, 4), Options("a", false, 3), Options("c", false, 2), Options("e", false, 1) }),
                                                                  Profile({ Options("e", false, 5), Options("a", false, 4), Options("b", false, 3), Options("c", false, 2), Options("d", false, 1) }) };

        Rank left(original);
        Rank right(prime);

        //left.order_ranking( );
        //right.order_ranking( );

        SCT::Simple_majority_rule maj;
        SCT::Borda_count borda;
        SCT::Qualified_majority_rule quali;

        Profile first{ borda(original) };
        Profile second{ borda(prime) };

        Profile third{ maj(original) };
        Profile four{ maj(prime) };

        Profile five{ quali(original) };
        Profile six{ quali(prime) };

        std::cout << original << "\n\n" << prime << "\n";

        std::cout << left << "\n" << right << "\n";

        //first.sort_by_opt( );
        //second.sort_by_opt( );

        std::cout << first << "\n" << second << "\n" << third << "\n" << four << "\n" << five << "\n" << six << "\n";

        if (first == second)

                std::cout << "\ntrue\n\n";

        else

                std::cout << "\nfalse\n\n";
}

void test7() {

        bool val = false;

        while (val == false) {

                Preferencematrix matrix(5, 5);

                Rank rank(matrix);

                std::cout << matrix << "\n";

                std::cout << rank << "\n";

                if (rank.is_transitive())

                        val = true;

                std::cout << "\n";
        }
}

void test8() {

        Preferencematrix original = { Profile({ Options("a", false, 5), Options("b", false, 4), Options("c", false, 3), Options("d", false, 2), Options("e", false, 1) }),
                                                                  Profile({ Options("b", false, 5), Options("c", false, 4), Options("d", false, 3), Options("e", false, 2), Options("a", false, 1) }),
                                                                  Profile({ Options("c", false, 5), Options("d", false, 4), Options("e", false, 3), Options("a", false, 2), Options("b", false, 1) }),
                                                                  Profile({ Options("d", false, 5), Options("e", false, 4), Options("a", false, 3), Options("b", false, 2), Options("c", false, 1) }),
                                                                  Profile({ Options("e", false, 5), Options("a", false, 4), Options("b", false, 3), Options("c", false, 2), Options("d", false, 1) }) };

        /*Preferencematrix prime = { Profile( { Options( "c", false, 5 ), Options( "d", false, 4 ), Options( "e", false, 3 ), Options( "a", false, 2 ), Options( "b", false, 1 ) } ),
                                                                  Profile( { Options( "e", false, 5 ), Options( "d", false, 4 ), Options( "a", false, 3 ), Options( "b", false, 2 ), Options( "c", false, 1 ) } ),
                                                                  Profile( { Options( "c", false, 5 ), Options( "b", false, 4 ), Options( "a", false, 3 ), Options( "d", false, 2 ), Options( "e", false, 1 ) } ),
                                                                  Profile( { Options( "b", false, 5 ), Options( "d", false, 4 ), Options( "a", false, 3 ), Options( "c", false, 2 ), Options( "e", false, 1 ) } ),
                                                                  Profile( { Options( "e", false, 5 ), Options( "a", false, 4 ), Options( "b", false, 3 ), Options( "c", false, 2 ), Options( "d", false, 1 ) } ) };*/

        Rank one(original);

        Preferencematrix prime{ };

        //Preferencematrix prime = generate_prime_profile( original, one );
        Rank two(prime);

        std::cout << prime << "\n";

        std::cout << one << "\n" << two << "\n";

        if (SCT::Borda_count().operator( )(original) != SCT::Borda_count( ).operator( )( prime ) ) // MODIFIED

                std::cout << "true\n";

        else

                std::cout << "false\n";
}

void test9() {

        bool test = true;

        while (test) {

                Preferencematrix original(4, 4);
                Rank rank(original);

                Preferencematrix prime{ };

                //Preferencematrix prime = generate_prime_profile( original, rank );
                Rank primerank(prime);

                std::cout << original << "\n" << prime << "\n";

                std::cout << rank << "\n" << primerank << "\n";

                if (rank_relations(rank, primerank) == false)

                        test = false;
        }
}

void test10( ){

        Preferencematrix matrix( 14, 14 );

        Preferencematrix prime = SCT::generate_prime_profile( matrix );

        std::cout << matrix << "\n" << prime << "\n";
}

void heapPermutation( Profile& profile, int size ){

    // if size becomes 1 then prints the obtained 
    // permutation 
    if( size == 1 ){

        //std::cout << profile << "\n";

        return;
    }

    for( std::vector<int>::size_type i = 0; i < size; i++ ){

        heapPermutation( profile, size - 1 );

        // if size is odd, swap first and last element 
        if( size % 2 == 1 ){

            swap( profile[ 0 ], profile[ size - 1 ] );
        }

        // If size is even, swap ith and last element
        else{

            swap( profile[ i ], profile[ size - 1 ] );
        }
    }
}

void test11( ){

    std::vector<char> prof = { 'a', 'b', 'c', 'd', 'e' };

    std::sort( prof.begin( ), prof.end( ) );

    /*do{

        std::copy( prof.begin( ), prof.end( ), std::ostream_iterator<char>( std::cout, " " ) );

        std::cout << std::endl;
    }*/

    //while( std::next_permutation( prof.begin( ), prof.end( ) ) );

    Preferencematrix matrix{ };

    Profile teste = { "a", "b", "c", "d", "e" };

    for( std::vector<int>::size_type i = 0; i < std::tgamma( teste.size( ) ); ++i ){

        heapPermutation( teste, teste.size( ) );

        matrix.push_back( teste );
    }

    std::cout << matrix << "\n";
}

std::vector<int> num_of_elem( int size ){

	std::vector<int> elements{ };

	int remainder{ size };

	int i = 1;

	while( remainder > 0 ){

		if( ( remainder - ( std::pow( 26, i ) ) > 0 ) ){

			elements.push_back( std::pow( 26, i ) );

			remainder -= std::pow( 26, i );
		}

		else{

			elements.push_back( remainder );

			remainder -= std::pow( 26, i );
		}

		++i;
	}

    return elements;
}

void alphabet( std::vector<int>& elem ){

	// elem.size is the max num of houses resulting string will have

	std::string alpha = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
						  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };


}

// THIS IS IT AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA - pass this to IIA.h
// Always pre-sort the original profile according to lexical order
void generate( int value, Profile& profile, Preferencematrix& matrix ){

    if( value == 1 ){

        std::cout << profile << "\n";

        matrix.push_back( profile );
    }

    else{

        generate( value - 1, profile, matrix );

        for( std::vector<int>::size_type i = 0; i < ( value - 1 ); ++i ){

            if( value % 2 == 0 ){

                swap( profile[ i ], profile[ value - 1 ] );
            }

            else{

                swap( profile[ 0 ], profile[ value - 1 ] );
            }

            generate( value - 1, profile, matrix );
        }
    }
}

void test12( ){

    Profile tryprof = { "a", "b", "c" };

    Preferencematrix result{};

    generate( tryprof.size( ), tryprof, result );

    std::cout << "\n" << result << "\n";
}

void program_interface( ){

    std::cout << "Hello! This is an alpha version of Social Choice Theory, and educational software companion."
              << " The ideia is to provide an intuitive and interactive way of learning Social Choice Theory."
              << " Let me give you a hand, lets have a look at all data structures of this project.\n\n";

    Options option{ "Options", false, 0 }; // Overload >> operator

    std::cout << option
              << "\n\nThis is an Option. The most basic data structure here. It represents an alternative,"
              << " i.e., a preference to be ordered by an aggregation procedure. It is defined by an name or id, and"
              << " a value. The name/id is used to identify an alternative among others, while its value is used so "
              << "as to make it possible for it to be ordered.\n\n";

    std::cout << "To hold multiple options, we have a specific data structure, called a Profile."
              << "\n\n";
       
    Profile profile = { "a", "b", "c" };

    std::cout << profile
              << "\n\nA profile holds many alternatives, and makes it possible for one to order them, wether by its "
              << "names or by its values. Since in social choice theory alternatives are ranked according to how they"
              << " are ordered in many different profiles, we will choose to procceed here by ordering them according"
              << " to their values."
              << "\n\nBut, what good does one person aggregating one sole profile? None, my dear reader. None. To get"
              << " to the fun part of social choice, one must aggregate MANY, preferable different, profiles! To handle"
              << " an arbitrary amount of profiles, we have a Preference Matrix. A matrix where each row represents a "
              << "profile, and each column represents an alternative.\n\n";

    Preferencematrix matrix{};
    matrix.set_matrix( 4, 4 );

    std::cout << matrix
              << "\n\nFrom now on, we are entering in the realm of aggregation! The first step is to provide a way of"
              << " comparing the alternatives in a profile or matrix. The first data structure that does that is a "
              << "Ranking! A Ranking compares pairs of alternatives. All possible pairs, except for the ones with equal"
              << " elements. Any pair x, y in a Ranking is compared on the matrix, to check wether, for all profiles in"
              << " the matrix, x beats, is beaten, or is equal to y.\n\n";

    Rank rank{};
    rank.generate_ranking( matrix );

    // Apresentar grafos por último
    std::cout << rank
              << "\nFrom now on, one can apply aggregation procedures to a rank, to see social preference relations be"
              << "tween ant pair of alternatives. By social preference relation, it is meant here that what an aggrega"
              << "tion procedure does is to use an selection rule to both order a social profile and decide wether or "
              << "not an alternative is approved.\nFor example, from the previous matrix and ranking, the Qualified ma"
              << "jority rule, a rule that checks wether or not an alternative beats every other alternative in half o"
              << "f the profiles, can be applied. It gives the following profile as a result, where the chosen alterna"
              << "tive is top ranked, i.e., is found at the beginning of the profile.\n";

    SCT::Qualified_majority_rule maj{};

    Profile result = maj( matrix ); // MODIFIED

    std::cout << "\n";
    std::cout << result << "\n";

    std::cout << "\nBut now, lets take a little detour to check another data structure that might be used here. This "
              << "one is called a Social Choice Graph. It is a graph that takes alternatives as nodes and constructs "
              << "edges between any two nodes based on a relation defined by an aggregation procedure.";
              
    Graph graph{ };
    graph.make_graph( rank );

    std::cout << graph << "\n\n";

    std::cout << "\n";
}

int main( ) {
    
    Preferencematrix matrix{ };
    matrix.set_matrix( 4, 4 );

    std::cout << matrix << "\n\n";

    Rank rank{ };
    rank.generate_ranking( matrix );

    std::cout << rank << "\n\n";

    Graph graph{ };
    graph.initialize_graph( matrix );

    Profile profile = SCT::Qualified_majority_rule( )( matrix );

    graph.make_graph( profile );

    std::cout << graph << "\n";

    std::cout << "\n";
}

