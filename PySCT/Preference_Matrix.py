import random
from string import ascii_lowercase
import Options
import Profile

class Preference_Matrix:

    # Constructors & Destructor
    def __init__( self, row: int = None, column: int = None, mtx: [ Profile.Profile ] = None ):

        self.rowsize: int = row if row is not None else 0
        self.columnsize: int = column if column is not None else 0

        self.matrix: list( Profile.Profile( ) ) = mtx if mtx is not None else list( ) # Modified this. TESTING

    def __del__( self ):

        self.rowsize = 0
        self.columnsize = 0

        self.matrix = list()

    # Setters

    # Creates a matrix with row profiles and column options in each profile.
    # Assigns random values to the options in each profile.
    def set_matrix( self, row: int, column: int ): # Remember to deal with cases where column >= 26

        self.rowsize = row
        self.columnsize = column

        alphabet: [ str ] = [ chr( i ) for i in range( ord( 'a' ), ord( 'z' ) + 1 ) ]

        for i in range( row ):

            setofalts: Profile.Profile = Profile.Profile() # had to do this so as to create new/different objects, since python passes by reference
            setofalts.reserve( column )

            self.matrix.append( setofalts )

            randlist: [ int ] = self.__shuffle_values( column )

            for j in range( column ):

                self.matrix[ i ][ j ] = Options.Options( alphabet[ j ], False, randlist[ j ] ) # Modified: added Options.Options() -> This solved the issues

    # Getters

    # Overloaded subscript operator
    def __getitem__( self, index: int ) -> Profile.Profile:

        return self.matrix[ index ]

    # Returns the len of the matrix, wheren len = number of profiles in matrix.
    def __len__( self ) -> int:

        return len( self.matrix )

    # Operators

    # Helpers
    def __str__( self ) -> str:

        string: str = str( )

        for profile in self.matrix:

            string += str( profile ) + "\n"

        return string

    def print( self ) -> str:

        for i in range( len( self.matrix ) ):

            print( self.matrix[ i ] )

    def append( self, profile: Profile.Profile ):

        self.matrix.append( profile ) if profile is not None else [ ]
    
    def reserve( self, row: int, col: int ):
    
        self.matrix += [ self.matrix ] * ( row - len( self.matrix ) )

        for i in range( len( self.matrix ) ):

            self.matrix[ i ] # I think the error is here

    # Method to get permutations of a range of values. Represents different
    # values of alternatives, for different profiles
    def __shuffle_values( self, numofvalues: int ) -> [ int ]:

        listofints: [ int ] = [ i for i in range( numofvalues ) ]

        random.shuffle( listofints )

        return listofints

# Testing Zone

"""
def test1( ):

    matrix: Preference_Matrix  = Preference_Matrix()

    matrix.set_matrix( 4, 4 )

    matrix.print()

    print( "\n" )

    print( matrix[ 1 ][ 2 ] )
"""

"""
def test2( ):
    
    matrix: Preference_Matrix = Preference_Matrix( )
    matrix.set_matrix( 3, 3 )

    print( matrix )

    profile: Profile.Profile = Profile.Profile( )
    profile.initialize( matrix[ 0 ] ) # reads a matrix[ 0 ] profile as a TUPLE, not as a profile of options

    print( profile )
"""