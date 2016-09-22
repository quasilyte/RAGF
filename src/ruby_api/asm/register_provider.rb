class Ragf::RegisterProvider
  Register = Ragf::Register
  Encoder = Ragf::Encoder
  Numerics = Ragf::Numerics
  Statement = Ragf::Statement
  Assert = Ragf::Assert

  def initialize statements
    @statements = statements
    @regs = (0..8).map {|x| Register.new x}
  end

  def []=(id, expr)
    Assert.valid_register_id id, "`r[]'"
    case expr
      when Fixnum then 
        @statements << (Encoder.assign @regs[id].arg, expr)
      when Statement 
        @statements << expr

      else raise "unexpected assign of #{expr}"
    end
  end 

  def [](id)
    Assert.valid_register_id id, "`r[]'"
    @regs[id]
  end
end