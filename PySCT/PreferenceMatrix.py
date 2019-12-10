import Profile

class Preference_Matrix:

    # Fields
    rowsize: int = 0
    columnsize: int = 0

    matrix: [ Profile.Profile ] = []

    # Constructors & Destructor
    def __init__( self, row: int = None, column: int = None, mtx: [ Profile.Profile ] = None ):

        self.rowsize = row if row is not None else 0
        self.columnsize = column if column is not None else 0

        self.matrix = mtx if mtx is not None else [ ]

    def __del__( self ):

        self.rowsize = 0
        self.columnsize = 0

        self.matrix = []

    # Setters

    # Getters

    # Operators

    # Helpers