mutable struct Agent

  id::Char

  preferences::Array{ Option }
end

# "Methods" - Begin

function set_id( agt, name )

  agt.id = name
end

function set_preferences( agt, preference::Array{ Option } )

  agt.preferences = preference
end

function set_preferences( agt, pref::Option )

  push!( agt.preferences, pref )
end

# "Methods" - End
