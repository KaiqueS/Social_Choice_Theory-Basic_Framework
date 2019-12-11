import Profile

class Preference_Matrix:

    # Fields
    #rowsize: int = 0
    #columnsize: int = 0

    #matrix: [ Profile.Profile ] = []

    # Constructors & Destructor
    def __init__( self, row: int = None, column: int = None, mtx: [ Profile.Profile ] = None ):

        self.rowsize = row if row is not None else 0
        self.columnsize = column if column is not None else 0

        self.matrix = mtx if mtx is not None else [ ]

    def __del__( self ):

        self.rowsize = 0
        self.columnsize = 0

        self.matrix = []

    def __str__( self ) -> str: # Think of a way of cumstomizing this

        return str( self.matrix )

    # Setters
    def set_matrix( row: int, column: int ):

        

    # Getters

    # Operators

    # Helpers

matrix: Preference_Matrix  = Preference_Matrix()

print( matrix )