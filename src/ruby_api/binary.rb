module Ragf::Binary
  Assert = Ragf::Assert

  def bit_string pack
    return pack.bytes.map {|byte| '%08b' % byte}.join
  end

  def f64_bits value
    return bit_string [value].pack('D')
  end

  def uint8_bits value
    Assert.no_overflow value, 0, 0xFF
    return bit_string [value].pack('C')
  end

  def uint16_bits value
    Assert.no_overflow value, 0, 0xFF_FF
    return bit_string [value].pack('S')
  end

  def uint32_bits value
    Assert.no_overflow value, 0, 0xFF_FF_FF_FF
    return bit_string [value].pack('L')
  end

  def uint64_bits value
    Assert.positive value
    return bit_string [value].pack('Q')
  end

  def int8_bits value
    Assert.no_overflow value, (-0xFF / 2 + 1), 0xFF / 2
    return bit_string [value].pack('c')
  end

  def int16_bits value
    Assert.no_overflow value, (-0xFF_FF / 2 + 1), 0xFF_FF / 2
    return bit_string [value].pack('s')
  end

  def int32_bits value
    Assert.no_overflow value, (-0xFF_FF_FF_FF / 2 + 1), 0xFF_FF_FF_FF / 2
    return bit_string [value].pack('l')
  end

  def int64_bits value
    return bit_string [value].pack('q')
  end
end
