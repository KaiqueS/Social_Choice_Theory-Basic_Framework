import Options

# Implement push_back, sorting methods, erase, clear, no indifference,
# Search for a way to set a variable to a default instance of a class, 
# e.g.: x = Options() = ( "NULL", False, -1 )

class Profile:

    # Constructors & Destructor
    def __init__( self, value_s: bool = None, opt_s: bool = None, 
                  indiff: bool = None, alts: [ Options.Options ] = None ):

        self.value_sorted: bool = value_s if value_s is not None else False
        self.opt_sorted: bool = opt_s if opt_s is not None else False
        self.indifference: bool = indiff if indiff is not None else False

        self.alternatives: list( Options.Options ) = alts if alts is not None else list( ) # Modified this. TESTING

    # Setters
    def __setitem__( self, index: int, opt: Options.Options ):

        self.alternatives[ index ] = opt

    def set_alternatives( self, alts: [ Options.Options ] ):

        self.alternatives = alts

    def reserve( self, size: int ):

        self.alternatives += [ self.alternatives ] * ( size - len( self.alternatives ) )

    # Getters
    def __getitem__( self, index: int ) -> Options.Options:

        return self.alternatives[ index ]
    
    def __len__( self ) -> int:

        return len( self.alternatives )
    
    # Operators

    # Helpers
    def __str__( self ) -> str:

        string: str = str( )

        string += "[ "

        for opt in self.alternatives:

            string += str( opt )

        string += " ]"

        return string

    def initialize( self, profile: list( ) ): # problem here

        self.alternatives = profile

        for i in range( len( self.alternatives ) ):
    
            self.alternatives[ i ].set_value( 0 )

    def append( self, opt: Options.Options = None ):

        self.alternatives.append( opt ) if opt is not None else print( "Cannot append nothing" )

# Testing methods below
"""
def test2():

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

"""
def test3():

    x: Profile = [ ( "A", False, 1 ), ( "B", False, 0 ) ]

    y: Options.Options = ( "C", False, 1 )

    x.append( y )

    print( x )
"""

"""
def test4():

    opt = Options.Options()

    print( opt )

    x: Profile = [ ( "A", False, 1 ), ( "B", False, 0 ) ]

    prof = Profile()

    print( prof )

    y = Options.Options()
    y.set_opt( "C" )

    print( y )

    x.append( y )

    print( x[ 2 ] )
"""

"""
def test5():
    prof = Profile()

    print( len( prof ) )

    prof.reserve( 6 )

    print( len( prof ) )

    print( prof )

    for i in range( len( prof ) ):

        prof[ i ] = ( str( i ), False, i )

    print( prof )
"""

"""
prof1: Profile = Profile( )

for i in range( 3 ):

    prof1.append( Options.Options( str( i ), False, i ) )

prof2: Profile = Profile( )
prof2.initialize( prof1 )

for opt in prof2:

    print( opt )
"""