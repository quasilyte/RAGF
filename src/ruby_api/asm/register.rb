class Ragf::Register
  Numerics = Ragf::Numerics
  Encoder = Ragf::Encoder

  def initialize id
    @id = id
    @arg = Ragf::Arg.new :reg, @id
  end
  
  attr_reader :id, :arg

  def +(expr)
    return (Encoder.add @arg, expr)
  end
end