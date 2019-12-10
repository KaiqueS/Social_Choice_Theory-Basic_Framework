
class Options:

    # Fields
    opt: "" = "NULL"

    status: bool = False

    value: int = -1

    # Constructors & Destructor
    def __init__( self, id = None, truth = None, val = None ):
        
        self.opt = id if id is not None else "NULL"

        self.stats = truth if truth is not None else False

        self.value = val if val is not None else -1

    def __del__( self ):

        self.opt = ""

        self.status = False

        self.value = -1

    # Setters
    def set_opt( self, id ):

        self.opt = id

    def set_status( self, truth ):

        self.status = truth

    def set_value( self, val ):

        self.value = val

    # Getters
    def get_opt( self ):

        return self.opt
    
    def get_status( self ):

        return self.status

    def get_value( self ):

        return self.value

    # Operators

    # Helpers
    def __str__( self ):

        return "( " + str( self.opt ) + ", " + str( self.status ) + ", " + str( self.value ) + " )"


# Testing methods below
"""
def test1():
    
    x = Options( "a", False, 5 )

    print( Options( "b", True, 56 ) )

    y = x

    print( y )

    x.set_opt( "D" )
    x.set_status( True )
    x.set_value( 84 )

    print( x )
"""

#x = Options(  )

#print( x )