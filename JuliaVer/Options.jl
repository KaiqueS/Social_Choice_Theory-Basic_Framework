mutable struct Option

  alternative::Char

  value::Int128
end

# "Methods" - Begin

function set_char( opt, name )

  opt.alternative = name
end

function set_value( opt, val )

  opt.value = val
end

# "Methods" - End
