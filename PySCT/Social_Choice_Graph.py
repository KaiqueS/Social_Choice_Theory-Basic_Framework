import Profile
import Preference_Matrix
import Social_Choice_Rank
from SPNode import Social_Preference_Node

class Graph:

    # Constructor & Destructor
    def __init__( self ):

        self.nodes: list( Social_Preference_Node ) = list( )

    def __del__( self ):

        self.nodes = list()

    # Setters
    def create_graph( self, rank ): # FINISH THIS

        for i in range( len( rank) ):

            for j in range( len( self.nodes ) ):

                if( rank[ i ][ 0 ].get_opt( ) == self.nodes[ j ].get_opt( ) ):

                    return

    # Getters

    # Operators

    # Helpers
    def initialize( self, profile: Profile.Profile ):

        self.reserve( len( profile ) )

        for i in range( len( self.nodes ) ):

            self.nodes[ i ].set_id( profile[ i ].get_opt( ) )

    def reserve( self, size: int ):

        self.nodes += [ self.nodes ] * ( size - len( self.nodes ) )

""" Testing Zone """