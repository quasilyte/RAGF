module Ragf::Numerics
  @@max_i8 = 127
  @@min_i8 = -128
  @@max_i32 = 2147483647
  @@min_i32 = -2147483648

  @@promotion_table = {
    i8: :i32,
    i32: :i64
  }

  def self.promote! arg
    arg.type = @@promotion_table[arg.type]
  end

  def self.sizeof value
    if value >= 0
      if value > @@max_i32 
        return :i64
      elsif value > @@max_i8
        return :i32
      else
        return :i8
      end
    else 
      if value < @@min_i32 
        return :i64
      elsif value < @@min_i8
        return :i32
      else
        return :i8
      end
    end
  end
end