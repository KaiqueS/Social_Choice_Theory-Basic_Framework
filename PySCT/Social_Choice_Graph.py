import Profile
import Preference_Matrix
import Social_Choice_Rank
import SPNode

class Graph:

    # Constructor & Destructor
    def __init__( self ):

        self.nodes: list( SPNode.Social_Preference_Node ) = list( )

    def __del__( self ):

        self.nodes = list()

    # Setters
    def create_graph( self, rank ): # FINISH THIS

        for i in range( len( rank) ):

            for j in range( len( self.nodes ) ):

                if rank[ i ][ 0 ][ 0 ] == self.nodes[ j ].get_id() : # problem here, cannot access methods from elements in self.nodes

                    if rank[ i ][ 0 ] > rank[ i ][ 1 ]:

                        node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
                        node.set_id( rank[ i ][ 1 ] )

                        self.nodes[ j ].add_preferred( node )
                    
                    elif rank[ i ][ 0 ] < rank[ i ][ 1 ]:

                        node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
                        node.set_id( rank[ i ][ 1 ] )

                        self.nodes[ j ].add_worse( node )

                    else:

                        node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
                        node.set_id( rank[ i ][ 1 ] )

                        self.nodes[ j ].add_indiff( node )
                else:

                    continue

    # Getters

    # Operators

    # Helpers
    def __str__( self ): # Fix this

        string: str = str()

        for i in range( len( self.nodes ) ):

            string += str( self.nodes[ i ].node_id ) + "\n"

        return string

    def initialize( self, profile: Profile.Profile ):

        self.reserve( len( profile ) )

        for i in range( len( self.nodes ) ):

            node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
            node.set_id( profile[ i ][ 0 ] )

            self.nodes[ i ] = node

    def reserve( self, size: int ):

        self.nodes += [ self.nodes ] * ( size - len( self.nodes ) )

""" Testing Zone """

profile: Profile.Profile = [ ( "a", False, 1 ), ( "b", False, 2 ), ( "c", False, 3 ) ]

matrix: Preference_Matrix.Preference_Matrix = Preference_Matrix.Preference_Matrix( )

matrix.append( profile )
matrix.append( profile )
matrix.append( profile )

rank: Social_Choice_Rank.Rank = Social_Choice_Rank.Rank()
rank.generate_ranking( matrix )

graph: Graph = Graph()
graph.initialize( profile )
graph.create_graph( rank )

print( graph )