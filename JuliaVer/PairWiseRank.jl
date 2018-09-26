struct PairWiseRank

  optx::Option
  opty::Option

  xval::Int128
  yval::Int128
  ival::Int128
end

# "Methods" - Begin

function set_xval( pairwrank, valx )

  pairwrank.xval = valx
end

function set_yval( pairwrank, valy )

  pairwrank.yval = valy
end

function set_ival( pairwrank, vali )

  pairwrank.ival = vali
end

# "Methods" - End
