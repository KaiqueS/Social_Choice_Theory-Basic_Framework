import itertools
import random
import Preference_Matrix

class Rank:

    # Constructor & Destructor
    
    # Constructor - initializes Rank to an empty list
    def __init__( self ):

        # A ranking is a list of quintuples( Option x._opt, Option y._opt, xval, yval, ival )
        self.ranking: list( str, str, int, int, int ) = list( )

    # Destructor - resets Rank to its default value
    def __del__( self ):

        self.ranking = list( )

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
        for pair in range( len( self.ranking ) ):

            # Iterate over all profiles in a matrix
            for profile in matrix:

                # First iteration over the elements of each profile.
                # This will get us to the first alternative to be compared
                for opt_x in profile:

                    # Second iteration over the elements of each profile.
                    # This will get us to the second alternative to be compared
                    for opt_y in profile:

                        if opt_x != opt_y:

                            # If the options are the same, i.e., have the same id
                            # Debug note: after modifying line 45 in Preference_Matrix,
                            # elements of Profile in Matrix are now Options. Remove subscripts here
                            # used in opt_x and opt_y
                            if self.ranking[ pair ][ 0 ][ 0 ] == opt_x.get_opt( ) and self.ranking[ pair ][ 1 ][ 0 ] == opt_y.get_opt( ):

                                
                                if opt_x.get_value( ) > opt_y.get_value( ):
                                    
                                    self.ranking[ pair ] = list( self.ranking[ pair ] )
                                    self.ranking[ pair ][ 2 ] += 1

                                elif opt_x.get_value( ) < opt_y.get_value( ):

                                    self.ranking[ pair ] = list( self.ranking[ pair ] )
                                    self.ranking[ pair ][ 3 ] += 1

                                else:

                                    self.ranking[ pair ] = list( self.ranking[ pair ] )
                                    self.ranking[ pair ][ 4 ] += 1
                            
                            else:

                                continue
                        
                        else:

                            continue

    # Getters
    def __getitem__( self, index: int ) -> [ ( str, str, int, int, int ) ]:

        return self.ranking[ index ]

    def __len__( self ):

        return len( self.ranking )

    def get_ranking( self ):

        return self.ranking

    # Operators

    # Helpers
    def __str__( self ):

        string: str = str( )

        for i in range( len( self.ranking ) ):

            string += "Option X: " + str( self.ranking[ i ][ 0 ] )
            string += " Option Y: " + str( self.ranking[ i ][ 1 ] )
            string += " Xval: " + str( self.ranking[ i ][ 2 ] )
            string += " Yval: " + str( self.ranking[ i ][ 3 ] )
            string += " Ival: " + str( self.ranking[ i ][ 4 ] )
            string += "\n"

        return string

    # Gets all pairs of options, except for those with equal options
    def __get_pairs( self, profile: Preference_Matrix.Profile.Profile ):

        mylist: list( Preference_Matrix.Profile.Options.Options, Preference_Matrix.Profile.Options.Options ) = list( ) # Modified this. TESTING

        for pair in itertools.combinations( profile, 2 ):

            mylist.append( pair )

        for x, y in mylist:

            self.ranking.append( ( x.get_opt( ), y.get_opt( ), 0, 0, 0 ) ) # modified here

""" Testing Zone """

"""
profile: Preference_Matrix.Profile.Profile = [ ( "a", False, 1 ), ( "b", False, 2 ), ( "c", False, 3 ) ]

mylist: [ ( Preference_Matrix.Profile.Options.Options, Preference_Matrix.Profile.Options.Options ) ] = [ ]

#for pair in itertools.combinations( profile, 2 ):

#    mylist.append( pair )

#for i in range( len( mylist ) ):

#    print( mylist[ i ] )

matrix: Preference_Matrix.Preference_Matrix = Preference_Matrix.Preference_Matrix()
matrix.set_matrix( 3, 3 )

matrix.print( )

print( "\n" )

rank: Rank = Rank( )

rank.generate_ranking( matrix )

for i in range( len( rank ) ):

    print( rank[ i ] )

print( "\n" )

print( rank )
"""