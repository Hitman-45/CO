.data
base: .word 5 9 4 3 6 10 2 7 8 1 11 19 18 16 12 15 13 17 20 14 
.text
la 16 base
addi 1 0 20
addi 17 1 -1
addi 2 0 0
loop:
beq 2 17 Exit
addi 3 0 0
la 16 base
loop2:
beq 3 1 end2
lw 4 0(16)
lw 5 4(16)
ble 4 5 no_swap
sw 5 0(16)
sw 4 4(16)
no_swap:
addi 16 16 4
addi 3 3 1
j loop2
end2:
addi 2 2 1
j loop
Exit:
addi 0 0 0