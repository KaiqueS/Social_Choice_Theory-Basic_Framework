
class Options:

    # Fields
    #opt: "" = "NULL"

    #status: bool = False

    #value: int = -1

    # Constructors & Destructor
    def __init__( self, id = None, truth = None, val = None ):
        
        self._opt: str = id if id is not None else "NULL"

        self._stats: bool = truth if truth is not None else False

        self._value: int = val if val is not None else -1

    def __del__( self ):

        self._opt = ""

        self._status = False

        self._value = -1

    # Setters
    def set_opt( self, id ):

        self._opt = id

    def set_status( self, truth ):

        self._status = truth

    def set_value( self, val ):

        self._value = val

    # Getters
    def get_opt( self ) ->  str:

        return self._opt
    
    def get_status( self ) -> bool:

        return self._status

    def get_value( self ) -> int:

        return self._value

    # Operators

    # Helpers
    def __str__( self ):

        return "( " + str( self._opt ) + ", " + str( self._value ) + " )"


# Testing methods below

def test1():
    
    x = Options( "a", False, 5 )

    print( Options( "b", True, 56 ) )

    y = x

    print( y )

    x.set_opt( "D" )
    x.set_status( True )
    x.set_value( 84 )

    print( x )

#test1()

#x = Options( )

#print( x )