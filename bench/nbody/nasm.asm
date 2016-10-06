global main

extern printf

%define STEPS_COUNT  100000
%define BODIES_COUNT 5

%define xword    oword
%define tailcall jmp

struc Body 
  .x:    resq 1 
  .y:    resq 1
  .z:    resq 1
  .vx:   resq 1 
  .vy:   resq 1
  .vz:   resq 1
  .mass: resq 1
  .size:
endstruc

;; dst := sqrt(dst)
;;! @param[xmm/changed] dst
%macro negsd 1
  xorpd %1, xword [$negsd.mask]
%endmacro

;; dst := pow(dst, 2)
;;! @param[xmm/changed] dst
%macro sqrsd 1
  mulsd %1, %1
%endmacro

;; dst := a * b
;;! @param[xmm/float64] dst 
;;! @param[xmm/float64] a 
;;! @param[xmm/float64] b 
%macro mulsdx 3
  %define %%dst %1
  %define %%a   %2
  %define %%b   %3

  movapd %%dst, %%a
  mulsd %%dst, %%b
%endmacro

SECTION .data 

$negsd.mask: 
  dq 0x8000000000000000
  dq 0x8000000000000000

;;                            \n \0
$print_double.fmt: db "%.9f", 10, 0 

;; nasm has no compile-time floating point computations,
;; so I evaluated {vx/vy/vz * days_per_year} 
;; and {mass * solar_mass} outside this program
$system:
  $sun: istruc Body
    at Body.x,    dq 0.0
    at Body.y,    dq 0.0
    at Body.z,    dq 0.0
    at Body.vx,   dq 0.0
    at Body.vy,   dq 0.0
    at Body.vz,   dq 0.0
    at Body.mass, dq 39.47841760435743
  iend
  $jupiter: istruc Body
    at Body.x,    dq 4.84143144246472090e+00
    at Body.y,    dq -1.16032004402742839e+00
    at Body.z,    dq -1.03622044471123109e-01
    at Body.vx,   dq 0.606326392995832
    at Body.vy,   dq 2.81198684491626
    at Body.vz,   dq -0.02521836165988763
    at Body.mass, dq 0.03769367487038949
  iend
  $saturn: istruc Body
    at Body.x,    dq 8.34336671824457987e+00
    at Body.y,    dq 4.12479856412430479e+00
    at Body.z,    dq -4.03523417114321381e-01
    at Body.vx,   dq -1.0107743461787924
    at Body.vy,   dq 1.8256623712304119
    at Body.vz,   dq 0.008415761376584154
    at Body.mass, dq 0.011286326131968767
  iend
  $uranus: istruc Body
    at Body.x,    dq 1.28943695621391310e+01
    at Body.y,    dq -1.51111514016986312e+01
    at Body.z,    dq -2.23307578892655734e-01
    at Body.vx,   dq 1.0827910064415354
    at Body.vy,   dq 0.8687130181696082
    at Body.vz,   dq -0.010832637401363636
    at Body.mass, dq 0.0017237240570597112
  iend
  $neptune: istruc Body
    at Body.x,    dq 1.53796971148509165e+01
    at Body.y,    dq -2.59193146099879641e+01
    at Body.z,    dq 1.79258772950371181e-01
    at Body.vx,   dq 0.979090732243898
    at Body.vy,   dq 0.5946989986476762
    at Body.vz,   dq -0.034755955504078104
    at Body.mass, dq 0.0020336868699246304
  iend
$system_end:

;; PI   = 3.141592653589793
;; PI^2 = 9.869604401089358
;; solar_mass = 4.0 * PI^2
$solar_mass: dq 39.47841760435743

$half:     dq 0.5
$dt_coeff: dq 0.01 

SECTION .text ;;;;

%macro @system_step 0
  ;; unrolled loop over system objects 
  %assign %%i 0
  %rep BODIES_COUNT
    mov rdi, ($system + %%i * Body.size) 
    call move_from_i

    %assign %%i (%%i + 1)
  %endrep
%endmacro

;;! @param[xmm0/float64] value to print
print_double:
  mov edi, $print_double.fmt
  mov eax, 1
  jmp printf

;;! @param[rdi/int32]  argc 
;;! @param[rsi/char**] argv
main:
  %define .argc rdi
  %define .argv rsi
  %define .n    rcx

  push rbp
  push .argc 
  push .argv

  call init_system
  call energy
  call print_double

  mov .n, STEPS_COUNT
  .loop_body:
    @system_step
    sub .n, 1
  .loop_check:
    jne .loop_body

  call energy
  call print_double

  pop .argv
  pop .argc
  pop rbp
  
  ret

;; system cycle step
;;! @param[rdi/Body*] body 
move_from_i:
  %define .body       rdi
  %define .dt_coeff   xmm4
  %define .other_body rsi

  movsd .dt_coeff, [dt_coeff]

  ;; unpacking struct 
  %define .body_vx xmm15
  %define .body_vy xmm14
  %define .body_vz xmm13
  %define .body_x  xmm12
  %define .body_y  xmm11
  %define .body_z  xmm10
  movsd .body_vx, [.body + Body.vx]
  movsd .body_vy, [.body + Body.vy]
  movsd .body_vz, [.body + Body.vz]
  movsd .body_x, [.body + Body.x]
  movsd .body_y, [.body + Body.y]
  movsd .body_z, [.body + Body.z]

  lea .other_body, [.body + Body.size]
  jmp .loop_cond
  .loop_body:
    %define .magnitude xmm3
    %define .dx        xmm0
    %define .dy        xmm1 
    %define .dz        xmm2 
    %define .tmp1      xmm5
    %define .distance  xmm6

    ;; calculating deltas
    movapd .dx, .body_x
    movapd .dy, .body_y
    movapd .dz, .body_z
    subsd .dx, [.other_body + Body.x]
    subsd .dy, [.other_body + Body.y]
    subsd .dz, [.other_body + Body.z]

    ;; calculating distance
    mulsdx .distance, .dx, .dx
    mulsdx .tmp1, .dy, .dy
    addsd .distance, .tmp1 
    mulsdx .tmp1, .dz, .dz
    addsd .distance, .tmp1 
    sqrtsd .distance, .distance

    ;; calculating magnitude
    movapd .magnitude, .dt_coeff
    movapd .tmp1, .distance
    mulsd .tmp1, .distance
    mulsd .distance, .tmp1
    divsd .magnitude, .distance  

    %define .mass_x_magnitude .distance
    %define .tmp2             xmm7

    movapd .mass_x_magnitude, .magnitude
    mulsd .mass_x_magnitude, [.other_body + Body.mass]

    mulsdx .tmp1, .dx, .mass_x_magnitude
    subsd .body_vx, .tmp1
    mulsdx .tmp1, .dy, .mass_x_magnitude
    subsd .body_vy, .tmp1
    mulsd .mass_x_magnitude, .dz 
    subsd .body_vz, .mass_x_magnitude

    movapd .mass_x_magnitude, .magnitude
    mulsd .mass_x_magnitude, [.body + Body.mass]

    mulsd .dx, .mass_x_magnitude
    mulsd .dy, .mass_x_magnitude
    mulsd .dz , .mass_x_magnitude,     
    addsd .dx, [.other_body + Body.vx]
    addsd .dy, [.other_body + Body.vy]
    addsd .dz, [.other_body + Body.vz]
    movsd [.other_body + Body.vx], .dx
    movsd [.other_body + Body.vy], .dy
    movsd [.other_body + Body.vz], .dz

    add .other_body, Body.size
  .loop_cond:
    cmp .other_body, $system_end
    jne .loop_body
    
  movsd [.body + Body.vx], .body_vx
  movsd [.body + Body.vy], .body_vy
  movsd [.body + Body.vz], .body_vz

  %define .tmp xmm1

  mulsd .body_vx, .dt_coeff
  addsd .body_x, .body_vx  
  movsd [.body + Body.x], .body_x

  mulsd .body_vy, .dt_coeff
  addsd .body_y, .body_vy  
  movsd [.body + Body.y], .body_y

  mulsd .body_vz, .dt_coeff
  addsd .body_z, .body_vz  
  movsd [.body + Body.z], .body_z

  ret

;;  initialize $system
init_system:
  %define .body rdi
  %define .px   xmm0
  %define .py   xmm1 
  %define .pz   xmm2

  pxor .px, .px
  pxor .py, .py
  pxor .pz, .pz

  mov .body, $system
  .loop_body:
    %define .body_mass xmm3
    %define .tmp       xmm4
    
    movsd .body_mass, [.body + Body.mass]
    
    movsd .tmp, [.body + Body.vx]
    mulsd .tmp, .body_mass 
    addsd .px, .tmp

    movsd .tmp, [.body + Body.vy]
    mulsd .tmp, .body_mass 
    addsd .py, .tmp 

    movsd .tmp, [.body + Body.vz]
    mulsd .tmp, .body_mass 
    addsd .pz, .tmp 

    add .body, Body.size
  .loop_cond:
    cmp .body, $system_end
    jne .loop_body 

  tailcall offset_momentum

;;! @param[xmm0/float64] px
;;! @param[xmm1/float64] py
;;! @param[xmm2/float64] pz
offset_momentum:
  %define .px       xmm0
  %define .py       xmm1
  %define .pz       xmm2
  %define .sol_mass xmm3

  movsd .sol_mass, [$solar_mass]
  negsd .px 
  negsd .py 
  negsd .pz
  divsd .px, .sol_mass 
  divsd .py, .sol_mass 
  divsd .pz, .sol_mass 
  movsd [$sun + Body.vx], .px
  movsd [$sun + Body.vy], .py
  movsd [$sun + Body.vz], .pz

  ret

;;! @return[xmm0/float64] energy value
energy:
  %define .energy xmm4
  %define .body   rdi  

  pxor .energy, .energy

  mov .body, $system
  .loop_body1:
    %define .distance   xmm0       
    %define .tmp1       xmm1
    %define .tmp2       xmm2 
    %define .body_x     xmm15
    %define .body_y     xmm14
    %define .body_z     xmm13
    %define .body_mass  xmm12    
    %define .other_body rsi    

    ;; unpack struct to decrease memory accessing
    ;; inside inner loop
    movsd .body_mass, [.body + Body.mass]
    movsd .body_x, [.body + Body.x]
    movsd .body_y, [.body + Body.y]
    movsd .body_z, [.body + Body.z]

    movsd .tmp1, [.body + Body.vx]
    sqrsd .tmp1 
    movsd .tmp2, [.body + Body.vy]
    sqrsd .tmp2 
    addsd .tmp1, .tmp2 
    movsd .tmp2, [.body + Body.vz]
    sqrsd .tmp2 
    addsd .tmp1, .tmp2 
    mulsd .tmp1, .body_mass
    mulsd .tmp1, [$half]
    addsd .energy, .tmp1 

    lea .other_body, [.body + Body.size]
    jmp .loop_cond2
    .loop_body2:
      ;; adhoc distance calcuation along with dx, dy & dz
      movsd .distance, .body_x
      subsd .distance, [.other_body + Body.x]
      mulsd .distance, .distance
      movsd .tmp1, .body_y
      subsd .tmp1, [.other_body + Body.y]
      mulsd .tmp1, .tmp1
      addsd .distance, .tmp1
      movsd .tmp1, .body_z
      subsd .tmp1, [.other_body + Body.z]
      mulsd .tmp1, .tmp1 
      addsd .distance, .tmp1
      sqrtsd .distance, .distance 

      ;; energy evaluation step
      ;; e = e - (body.mass * other_body.mass) / distance
      movapd .tmp1, .body_mass
      mulsd .tmp1, [.other_body + Body.mass]
      divsd .tmp1, .distance
      subsd .energy, .tmp1

      add .other_body, Body.size 
    .loop_cond2:
      cmp .other_body, $system_end
      jne .loop_body2

    add .body, Body.size
  .loop_cond:
    cmp .body, $system_end
    jne .loop_body1

  movapd xmm0, .energy
  ret