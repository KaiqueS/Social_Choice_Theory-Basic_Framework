import itertools
import random
import Preference_Matrix

class Rank:

    # Constructor & Destructor
    
    # Constructor - initializes Rank to an empty list
    def __init__( self ):

        # A ranking is a list of quintuples( Option x._opt, Option y._opt, xval, yval, ival )
        self.ranking: [ ( str, str, int, int, int ) ] = []

    # Destructor - resets Rank to its default value
    def __del__( self ):

        self.ranking = [ ]

    # Setters

    # Generates a ranking based on how each alternative are related
    # to each other in each profile. I.e., if for any two alternatives
    # x and y, we have that x.value > y.value, then add 1 to x's score
    def generate_ranking( self, matrix: Preference_Matrix.Preference_Matrix ):

        #combinations: [ ( Preference_Matrix.Profile.Options.Options, Preference_Matrix.Profile.Options ) ] = self.__get_pairs( matrix[ 0 ] )
        
        # To avoid using magic numbers. Gets a random profile in matrix.
        # Since all profiles have the same alternatives in them, any
        # profile chosen will result in the same pairs of options
        self.__get_pairs( matrix[ random.randrange( 0, len( matrix ) ) ] )

        # Iterate over all pairs in combinations
        for left, right, leftval, rightval, indiffval in self.ranking:

            # Iterate over all profiles in a matrix
            for profile in matrix:

                # First iteration over the elements of each profile.
                # This will get us to the first alternative to be compared
                for opt_x in profile:

                    # Second iteration over the elements of each profile.
                    # This will get us to the second alternative to be compared
                    for opt_y in profile:

                        if opt_x != opt_y:

                            if left == opt_x and right == opt_y:

                                if opt_x.get_value( ) > opt_y.get_value( ): # cannot access methods here DAMN REFERENCING

                                    rightval += 1

                                elif opt_x.get_value( ) < opt_y.get_value( ):

                                    leftval += 1

                                else:

                                    indiffval += 1
                            
                            else:

                                continue
                        
                        else:

                            continue

    # Getters
    def get_ranking( self ):

        return self.ranking

    # Operators

    # Helpers

    # Gets all pairs of options, except for those with equal options
    def __get_pairs( self, profile: Preference_Matrix.Profile.Profile ):

        mylist: [ ( Preference_Matrix.Profile.Options.Options, Preference_Matrix.Profile.Options.Options ) ] = [ ]

        for pair in itertools.combinations( profile, 2 ):

            mylist.append( pair )

        for x, y in mylist:

            self.ranking.append( ( x, y, 0, 0, 0 ) )

""" Testing Zone """

profile: Preference_Matrix.Profile.Profile = [ ( "a", False, 1 ), ( "b", False, 2 ), ( "c", False, 3 ) ]

mylist: [ ( Preference_Matrix.Profile.Options.Options, Preference_Matrix.Profile.Options.Options ) ] = [ ]

#for pair in itertools.combinations( profile, 2 ):

#    mylist.append( pair )

#for i in range( len( mylist ) ):

#    print( mylist[ i ] )

matrix: Preference_Matrix.Preference_Matrix = Preference_Matrix.Preference_Matrix()
matrix.set_matrix( 3, 3 )

rank: Rank = Rank( )

rank.generate_ranking( matrix )