global run_void
global run_int8
global run_int16
global run_int32
global run_int64
global run_uint8
global run_uint16
global run_uint32
global run_uint64

;! @param[rsi/u8*] -- code
;! @param[rdi/u8*] -- data
run_void:
run_int8:
run_int16:
run_int32:
run_int64:
run_uint8:
run_uint16:
run_uint32:
run_uint64:
  ;; preserve non-scratch registers
  push r12
  push r13
  push r14
  push r15
  ;; execute passed machine code (it should contain "ret")
  call rsi
  ;; restore preserved registers
  pop r15
  pop r14
  pop r13
  pop r12
  ret
