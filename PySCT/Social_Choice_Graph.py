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

                # If node read equal opt x in rank
                if rank[ i ][ 0 ][ 0 ] == self.nodes[ j ].get_id() :                                                                                                             

                    # If x.value > y.value
                    if rank[ i ][ 2 ] > rank[ i ][ 3 ]:

                        # Make a node = y
                        node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
                        node.set_id( rank[ i ][ 1 ][ 0 ] )

                        # Add y to x.preferred to
                        self.nodes[ j ].add_preferred( node )
                    
                    # Else, if y.value > x.value
                    elif rank[ i ][ 2 ] < rank[ i ][ 3 ]:

                        # Make a node = y
                        node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
                        node.set_id( rank[ i ][ 0 ][ 0 ] )

                        # Add y to x.worse_than
                        self.nodes[ j ].add_worse( node )

                    # Else, if x.value == y.value
                    else:

                        # Make a node = y
                        node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
                        node.set_id( rank[ i ][ 1 ][ 0 ] )

                        # Add y to x.indifferent_to
                        self.nodes[ j ].add_indiff( node )

                # Else, if node read equals opt y in rak
                elif rank[ i ][ 1 ][ 0 ] == self.nodes[ j ].get_id() :                                                                                                             

                    # If x.value > y.value
                    if rank[ i ][ 2 ] > rank[ i ][ 3 ]:

                        # Make a node = x
                        node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
                        node.set_id( rank[ i ][ 0 ][ 0 ] )

                        # Add x to y.worse_than
                        self.nodes[ j ].add_preferred( node )
                    
                    # Else, if y.value > x.value
                    elif rank[ i ][ 2 ] < rank[ i ][ 3 ]:

                        # Make a node = x
                        node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
                        node.set_id( rank[ i ][ 1 ][ 0 ] )

                        # Add x to y.preferred_to
                        self.nodes[ j ].add_preferred( node )

                    # Else, if y.value == x.value
                    else:

                        # Make a node = x
                        node: SPNode.Social_Preference_Node = SPNode.Social_Preference_Node()
                        node.set_id( rank[ i ][ 1 ][ 0 ] )

                        # Add x to y.indifferent_to
                        self.nodes[ j ].add_indiff( node )

    # Getters

    # Operators

    # Helpers
    def __str__( self ): # Fix this

        string: str = str()

        for i in range( len( self.nodes ) ):

            string += str( self.nodes[ i ] ) + "\n"

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