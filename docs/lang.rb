# Ruby can be used to define higher order instructions
# or syntax sugar for some forms

# mod: dst = a % b
def mod dst, a, b 
  dst = a 
  dst %= b
end

# There are 8 registers available.
# They can be referenced in different ways

# code      # assembly
u[0] = 10   # mov   r0, 10
i[0] = 10   # movsx r0, 10
m8[0]  = 10 # mov   byte  [r0], 10
m64[0] = 10 # mov   qword [r0], 10

# Give names to registers for readability
name r[0], :counter 
name r[1], :result
name r[2], :tmp

counter = 999
result = 0

### Loops 

WHILE counter != 0 do
  mod tmp, tmp, counter

  IF (tmp == 0) {result += 1}
  ELSE          {result += 2}

  counter -= 1
end 

# Same as above but with `For' instead of `While'

FOR counter = 0, counter != 0, counter += 1 do
  mod tmp, tmp, counter

  IF (tmp == 0) {result += 1}
  ELSE          {result += 2}
end 

### Assignment & expressions

# Assignment has special behavior.
# For immediate-only one can use any kind of Ruby expressions 

# code            # assembly
r[0] = 5 + 5      # mov r0, 10
r[0] = 10 % 2 + 1 # mov r0, 1
r[0] = 2 << 2     # mov r0, 8

# No random expressions are allowed if RHS contains any register reference.
# Basically RHS should match single instruction pattern to be accepted (valid)

# code              # assembly
r[0] = r[1] * 2     # lea  r0, [r2 * 2]
r[0] = r[1] + 5     # lea  r0, [r1 + 5]
r[0] = r[1] * 2 + 5 # lea  r0, [r1 * 2 + 5]
r[0] = r[1] * 20    # imul r0, r1, 20  

### SIMD

m64[0, 4] <<= 1
m8[0, 8] += 10 

# Some other things worth noting:
# - loops can be nested;
# - if/else can be nested;
