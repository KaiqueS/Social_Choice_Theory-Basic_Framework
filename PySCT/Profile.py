import Options

# Implement push_back, sorting methods, erase, clear, no indifference, 

class Profile:

    # Fields
    value_sorted: bool = False
    opt_sorted: bool = False
    indifference: bool = False

    #alternatives: List[ Options.Options ] = [ Options.Options( "NULL", False, -1 ) ]
    alternatives: [ Options.Options ] = []

    # Constructors & Destructor
    def __init__( self, value_s: bool, opt_s: bool, indiff: bool, alts: [ Options.Options ] ):

        self.value_sorted = value_s
        self.opt_sorted = opt_s
        self.indifference = indiff

        self.alternatives = alts

    # Setters
    def set_alternatives( self, alts: [ Options.Options ] ):

        self.alternatives = alts

    # Getters
    def __getitem__( self, index: int ) -> Options.Options:

        return self.alternatives[ index ]
    
    def __len__( self ) -> int:

        return len( self.alternatives )
    
    # Operators

    # Helpers
    def __str__( self ) -> str:

        for Options.Options in self.alternatives:

            return str( self.alternatives )

# Testing methods below
"""def test2():

    opt = Options.Options( "NULL", False, -1 )

    print( opt )

    list_of_opts: [ Options.Options ] = [ ( "a", False, 1 ), ( "b", False, 2 ), ( "c", False, 1 ) ]

    x: Profile = Profile( False, False, False, list_of_opts )

    print( "debug 1 begin" )

    for Options.Options in x.alternatives:

        print( Options.Options )

    print( "debug 1 end" )
    print( "debug 2 begin" )

    opts2: [ Options.Options ]

    opts2 = [ ( "d", False, 4 ), ( "e", False, 5 ), ( "f", False, 6 ) ]

    x.set_alternatives( opts2 )

    for Options.Options in x.alternatives:
    
        print( Options.Options )

    print( "debug 2 end" )

    print( len( x ) )

    print( x[ 0 ] )

    print( list_of_opts[ 1 ] )

    print( x )
"""

