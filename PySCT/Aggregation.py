import Options
import Profile
import Preference_Matrix
import Social_Choice_Rank


def qualified_majority( matrix: Preference_Matrix.Preference_Matrix ) -> Profile.Profile:

    result: Profile.Profile = Profile.Profile( )
    result.initialize( matrix[ 0 ] )

    rank: Social_Choice_Rank.Rank = Social_Choice_Rank.Rank( )
    rank.generate_ranking( matrix )

    for left in result:

        for right in result:

            if left != right:

                for pair in rank:

                    # If x.value > y.value
                    if pair[ 2 ] > pair[ 3 ]:

                        if pair[ 0 ] == left.get_opt( ):

                            left._value += 1

                        elif pair[ 0 ] == right.get_opt( ):

                            right._value += 1

                        else:

                            continue

                    # If x.value < y.value
                    elif pair[ 2 ] < pair[ 3 ]:

                        if pair[ 1 ] == left.get_opt( ):

                            left._value += 1

                        elif pair[ 1 ] == right.get_opt( ):

                            right._value ++ 1

                        else:

                            continue
                    
                    else:

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