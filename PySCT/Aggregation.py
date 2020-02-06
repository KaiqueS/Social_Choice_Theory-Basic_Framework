import Options
import Profile
import Preference_Matrix
import Social_Choice_Rank

# Selects an alternative with >= n / 2 votes, where n is the number of voters
def qualified_majority( matrix: Preference_Matrix.Preference_Matrix ) -> Profile.Profile:

    result: Profile.Profile = Profile.Profile( )
    result.initialize( matrix[ 0 ].alternatives )

    rank: Social_Choice_Rank.Rank = Social_Choice_Rank.Rank( )
    rank.generate_ranking( matrix ) # The error is here. Ranking miscreated

    # The miscounting problem occurs because of ival in rank
    for opt in result:

        for pair in rank:

            # If x.value > y.value
            if pair[ 2 ] > pair[ 3 ]:

                # If opt == x
                if opt.get_opt( ) == pair[ 0 ]:

                    opt._value += 1

                else:

                    continue
            
            # Else, if x.value < y.value
            elif pair[ 2 ] < pair[ 3 ]:

                # If opt == y
                if opt.get_opt( ) == pair[ 1 ]:

                    opt._value += 1

                else:

                    continue

            elif pair[ 2 ] == pair[ 3 ]:

                continue

    result.order_by_value( )

    return result

# Selects an alternative with the greatest amount of votes 
def simple_majority( matrix: Preference_Matrix.Preference_Matrix ) -> Profile.Profile:

    result: Profile.Profile = Profile.Profile( )
    result.initialize( matrix[ 0 ] )

    rank: Social_Choice_Rank.Rank = Social_Choice_Rank.Rank( )
    rank.generate_ranking( matrix )



    return result

def borda_count( matrix: Preference_Matrix.Preference_Matrix ) -> Profile.Profile:

    result: Profile.Profile = Profile.Profile( )
    result.initialize( matrix[ 0 ] )

    return result

""" Testing Zone """

def test1( ):
    
    matrix: Preference_Matrix.Preference_Matrix = Preference_Matrix.Preference_Matrix()
    matrix.set_matrix( 5, 5 )

    print( "\n" )

    matrix.print( )

    print( "\n" )

    rank: Social_Choice_Rank.Rank = Social_Choice_Rank.Rank()
    rank.generate_ranking( matrix )

    print( rank )

    print( "\n" )

    profile: Profile.Profile = Profile.Profile( )
    profile = qualified_majority( matrix )

    matrix.print( )

    print( "\n" )

    print( profile )

    print( "\nThe winner is: " + str( profile.winner( ) ) )

test1( )