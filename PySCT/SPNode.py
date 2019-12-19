import Profile
import Preference_Matrix
import Social_Choice_Rank

class Social_Preference_Node:

    # Constructors & Destructor
    def __init__( self ):

        self.node_id: str = "NULL"

        self.preferred_to: list( Social_Preference_Node ) = list( )
        self.worse_than: list( Social_Preference_Node ) = list( )
        self.indifferent_to: list( Social_Preference_Node ) = list( )

    def __del__( self ):

        self.node_id = ""

        self.preferred_to = list( )
        self.worse_than = list( )
        self.indifferent_to = list( )

    # Setters
    def set_id( self, id: str ):

        self.node_id = id

    def add_preferred( self, node ):

        self.preferred_to.append( node )

    def add_worse( self, node ):
    
        self.worse_than.append( node )

    def add_indiff( self, node ):
    
        self.indifferent_to.append( node )

    # Getters
    def get_id( self ) -> str:

        return self.node_id

    def get_preferred( self ):

        return self.preferred_to

    def get_pref( self, index: int ):

        return self.preferred_to[ index ]

    def get_worse_than( self ):

        return self.worse_than

    def get_worse( self, index: int ):

        return self.worse_than[ index ]

    def get_indifferent_to( self ):

        return self.indifferent_to

    def get_indiff( self, index: int ):

        return self.indifferent_to[ index ]

    # Operators

    # Helpers
    def __str__( self ) -> str:

        result: str = str()

        result += "Node " + self.node_id + "\nis preferred to: "

        for node in self.preferred_to:

            result += "[ " + node.get_id( ) + " ] "

        result += "\nis worse than: "

        for node in self.worse_than:

            result+= "[ " + str( node.get_id( ) ) + " ] " # Changed from node.get_id() to str( node.get_id() )

        result += "\nis indifferent to: "

        for node in self.indifferent_to:

            result += "[ " + node.get_id( ) + " ] "

        result += "\n"

        return result

""" Testing Zone """

"""

a: Social_Preference_Node = Social_Preference_Node()
a.set_id( "a" )

b: Social_Preference_Node = Social_Preference_Node()
b.set_id( "b" )

c: Social_Preference_Node = Social_Preference_Node()
c.set_id( "c" )

a.add_preferred( b )

b.add_worse( a )
b.add_preferred( c )

c.add_worse( b )
c.add_preferred( a )

print( a )
print( b )
print( c )

"""