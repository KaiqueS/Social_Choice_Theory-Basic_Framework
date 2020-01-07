import Options
import Profile
import Preference_Matrix
import Social_Choice_Rank


def qualified_majority( matrix: Preference_Matrix.Preference_Matrix ) -> Profile.Profile:

    result: Profile.Profile = Profile.Profile( )
    result.initialize( matrix[ 0 ] )

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

    return result

""" Testing Zone """

matrix: Preference_Matrix.Preference_Matrix = Preference_Matrix.Preference_Matrix()
matrix.set_matrix( 4, 4 )

print( "\n" )

matrix.print( )

print( "\n" )

rank: Social_Choice_Rank.Rank = Social_Choice_Rank.Rank()
rank.generate_ranking( matrix )

print( rank )

print( "\n" )

profile: Profile.Profile = Profile.Profile( )
profile = qualified_majority( matrix )

print( profile )