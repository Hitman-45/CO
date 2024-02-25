.data
arr: .word 1 2 16 6 25 
.text
addi 29 0 5
addi 25 29 -1
la 8 arr
addi 15 0 0
Loop1:
beq 15 25 exit
add 16 0 15
addi 6 15 1
Loop2:
beq 6 25 swap
slli 7 6 2
slli 28 16 2
add 5 8 28
lw 31 0(5)
add 5 8 7
lw 30 0(5)
bgt 30 31 nochange
add 16 0 6
nochange:
addi 6 6 1
addi 9 0 5
ble 6 9 Loop2
swap:
slli 29 15 2
add 5 29 8
lw 30 0(5)
slli 28 16 2
add 5 28 8
lw 31 0(5)
add 5 29 8
sw 31 0(5)
add 5 28 8
sw 30 0(5)
addi 1 0 4
addi 15 15 1
ble 15 1 Loop1
exit:
addi 0 0 0
