module Ragf::TokenProvider
  extend Ragf::Binary

  @@enum = Hash[%i{
    END
    RETURN
    ADD
    SUB
    ASSIGN
    SWAP
    NEG
    WHILE
    IF
    IF_ELSE

    NIL
    REG
    MEM
    I64
    I32
    I8
    U64
    U32
    U8

    EQ
    NEQ
    LT
    LTE
    GT
    GTE
  }.map.with_index {|key, idx| 
    [key, (uint8_bits idx)]
  }]

  def const_missing name
    if @@enum.include? name
      return @@enum[name]
    else
      raise "no token with name #{name} found" 
    end
  end
end