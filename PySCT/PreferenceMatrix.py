from random import randrange
from string import ascii_lowercase
import Profile

class Preference_Matrix:

    # Fields
    #rowsize: int = 0
    #columnsize: int = 0

    #matrix: [ Profile.Profile ] = []

    # Constructors & Destructor
    def __init__( self, row: int = None, column: int = None, mtx: [ Profile.Profile ] = None ):

        self.rowsize: int = row if row is not None else 0
        self.columnsize: int = column if column is not None else 0

        self.matrix: [ Profile.Profile ] = mtx if mtx is not None else [ ]

    def __del__( self ):

        self.rowsize = 0
        self.columnsize = 0

        self.matrix = []

    # Setters
    def set_matrix( self, row: int, column: int ):

        self.rowsize = row
        self.columnsize = column

        #self.reserve( row, column )
        setofalts: Profile.Profile = Profile.Profile()
        setofalts.reserve( column )

        alphabet: [ str ] = [chr(i) for i in range(ord('a'), ord('z') + 1)]

        #for i in range( len( setofalts ) ):
    
            #setofalts[ i ] = ( alphabet[ i ], False, 0 )

        for i in range( row ):

            self.matrix.append( setofalts )

            for j in range( column ):

                self.matrix[ i ][ j ] = ( alphabet[ j ], False, randrange( column ) ) # just need to fix RNG here

    # Getters
    def __getitem__( self, index: int ) -> Profile.Profile:

        return self.matrix[ index ]

    def __len__( self ) -> int:

        return len( self.matrix )

    # Operators

    # Helpers
    def print( self ) -> str:

        for i in range( len( self.matrix ) ):

            print( self.matrix[ i ] )

    def append( self, profile: Profile.Profile ):

        self.matrix.append( profile ) if profile is not None else [ ]
    
    def reserve( self, row: int, col: int ):
    
        self.matrix += [ self.matrix ] * ( row - len( self.matrix ) )

        for i in range( len( matrix ) ):

            self.matrix[ i ] # I think the error is here

alphabet: [ str ] = [chr(i) for i in range(ord('a'), ord('z') + 1)]

print( len( alphabet ) )
print( alphabet[ 0 ] )

matrix: Preference_Matrix  = Preference_Matrix()

matrix.set_matrix( 4, 4 )

matrix.print()