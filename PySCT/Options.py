
class Options:

    # Fields
    opt = "NULL"

    status = False

    value = -1

    # Constructors & Destructor
    def __init__( self, id, truth, val ):

        self.opt = id
        self.status = truth
        self.value = val

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

def print_opt( Options ):

    print( Options.get_opt( ), Options.get_status( ), Options.get_value( ) )

x = Options( "a", False, 5 )

print_opt( Options( "b", True, 56 ) )

y = x

print_opt( y )