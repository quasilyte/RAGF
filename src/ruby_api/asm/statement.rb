class Ragf::Statement
  def initialize key, tokens
    @key = key
    @tokens = tokens
  end

  attr_reader :key, :tokens
end