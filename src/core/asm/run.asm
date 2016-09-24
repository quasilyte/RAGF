global run_int8
global run_int16
global run_int32
global run_int64
global run_uint8
global run_uint16
global run_uint32
global run_uint64

run_int8:
run_int16:
run_int32:
run_int64:
run_uint8:
run_uint16:
run_uint32:
run_uint64:
  ;; rsi -- code
  ;; rdi -- data
  mov r9, rdi
  call rsi
  mov rax, r8
  ret
