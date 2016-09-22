module Ragf::Assert
  @@valid_sizes = [8, 16, 32, 64]
  @@valid_reg_ids = (0..8)

  def self.is_fixnum x, name = nil
    unless x.is_a? Fixnum
      name ||= caller[0]
      raise "#{name}: expected Fixnum, got #{x.class}"
    end
  end

  def self.valid_register_id id, name = nil
    is_fixnum id, name
    unless  @@valid_reg_ids.include? id
      name ||= caller[0]
      raise "#{name}: expected #{@@valid_reg_ids} register indexes"
    end
  end

  def self.positive value, name = nil 
    unless value > 0
      name ||= caller[0]
      raise "#{name}: expected positive value, got #{value}"
    end
  end

  def self.no_overflow value, min, max, name = nil
    unless value >= min && value <= max
      name ||= caller[0]
      raise "#{name}: value #{value} overflows [#{min}, #{max}]" 
    end
  end
end
