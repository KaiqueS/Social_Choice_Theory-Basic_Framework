import Preference_Matrix

class Rank:

    # Constructor & Destructor
    
    # Constructor - initializes Rank to an empty list
    def __init__( self ):

        # A ranking is a list of quintuples( Option x._opt, Option y._opt, xval, yval, ival )
        self.ranking: [ ( str, str, int, int, int ) ] = []

    # Destructor - resets Rank to its default value
    def __del__( self ):

        self.ranking = [ ]

    # Setters
    def generate_ranking( self, matrix: Preference_Matrix.Preference_Matrix ):

        pairs_of_alternatives: [ ( str, str ) ] = [ ( optx.get_opt( ), opty.get_opt( ) ) for optx, opty in zip( matrix[ 0 ] ) ]

        for i in range( len( matrix ) ):

            for j in range( len( matrix[ i ] ) ):

                for k in range( len( matrix[ i ] ) ) and k != j :

                    for m in range( len( pairs_of_alternatives ) ):

                        if( pairs_of_alternatives[ m ] ):

                            return

    # Getters
    def get_ranking( self ):

        return self.ranking

    # Operators

    # Helpers