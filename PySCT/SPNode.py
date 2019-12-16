import Profile
import Preference_Matrix
import Social_Choice_Rank

class Social_Preference_Node:

    def __init__( self ):

        node_id: str = "NULL"

        preferred_to: list( Social_Preference_Node ) = list( )
        worse_than: list( Social_Preference_Node ) = list( )
        indifferent_to: list( Social_Preference_Node ) - list( )
