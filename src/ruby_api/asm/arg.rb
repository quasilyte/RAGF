class Ragf::Arg
  def initialize type, value
    @type = type
    @value = value
  end

  attr_accessor :type, :value

  def to_s
    return "#{type}=#{value}"
  end
end