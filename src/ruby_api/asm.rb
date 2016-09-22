class Ragf::Asm
  Register = Ragf::Register 
  RegisterProvider = Ragf::RegisterProvider
  Encoder = Ragf::Encoder

  def initialize
    @aliases = {}
    @statements = []
    @reg_provider = (RegisterProvider.new @statements)
  end

  attr_reader :statements

  def self.compile &block
    compiler = new
    compiler.instance_eval(&block)
    return compiler.statements
  end

  def method_missing name, *args
    return @reg_provider if name === :r

    begin
      @statements << (Encoder.encode_stmt name, args)
    rescue RuntimeError => e 
      raise "`#{name}': #{e.message}"
    end
  end
end