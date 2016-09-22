class Ragf::Encoder
  extend Ragf::Binary
  extend Ragf::TokenProvider

  Arg = Ragf::Arg
  Numerics = Ragf::Numerics
  Statement = Ragf::Statement

  @@stmt_table = {
    assign: {
      reg: {
        reg: [ASSIGN, REG, REG],
        i32: [ASSIGN, REG, I32],
        i64: [ASSIGN, REG, I64]
      }
    },
    add: {
      reg: {
        i8:  [ADD, REG, I8],
        i32: [ADD, REG, I32]
      }
    },
    ret: RETURN
  }
  @@arity_table = {
    assign: 2,
    add:    2,
    ret:    0,
  }

  def self.encode_args args
    return args.map {|arg|
      case arg.type
        when :reg then uint8_bits  arg.value
        when :i8  then int8_bits   arg.value
        when :i16 then int16_bits  arg.value
        when :i32 then int32_bits  arg.value
        when :i64 then int64_bits  arg.value
        when :u8  then uint8_bits  arg.value
        when :u16 then uint16_bits arg.value
        when :u32 then uint32_bits arg.value
        when :u64 then uint64_bits arg.value

        else raise "failed to encode #{arg} value"
      end
    }
  end

  def self.resolve_fixnum overloading, arg 
    arg = Arg.new (Numerics.sizeof arg), arg 
    fallback = overloading 

    overloading = overloading[arg.type]
    
    until overloading
      overloading = fallback

      Numerics.promote! arg
      unless arg.type
        raise "can not infer int size for Fixnum arg"
      end

      overloading = overloading[arg.type] 
    end

    return arg, overloading
  end

  def self.resolve overloading, arg
    overloading = overloading[arg.type]
    raise "no matching overloading (failed at #{arg})" unless overloading
    return overloading
  end

  def self.encode_stmt name, raw_args
    overloadings = @@stmt_table[name]
    raise "unknown symbol" unless overloadings
    arity = @@arity_table[name]
    unless arity == raw_args.length
      raise "expected #{arity} args, got #{raw_args.length}"
    end

    overloading = overloadings

    if overloading.is_a? String
      return Statement.new name, overloading
    end

    args = []

    raw_args.each {|arg|
      case arg 
        when Fixnum then arg, overloading = resolve_fixnum overloading, arg 
        when Arg    then overloading = resolve overloading, arg 
      
        else raise "invalid arg: #{arg}"
      end

      args << arg
    }

    key = "#{name}<#{args.map(&:to_s).join(',')}>"
    tokens = (overloading + (encode_args args)).join('')
    return Statement.new key, tokens
  end

  def self.return
    return Statement.new 'return', RETURN
  end

  def self.assign dst, src
    return encode_stmt :assign, [dst, src]
  end

  def self.add dst, src
    return encode_stmt :add, [dst, src]
  end
end