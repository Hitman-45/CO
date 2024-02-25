# RIPE SIMULATION-CPP
#### _Team WuShangClan_

## About
This C++ program simulates a basic RISC-V-like processor architecture. It includes a simple processor class (Processor) and a core class (Core) that executes RISC-V-like instructions. The simulation is designed to mimic the behavior of a RISC-V processor using the Ripes simulator.

---
## Code Overveiw
The C++ code consists of two important classes: Core and Processor and a main function. This program simulates a processor with multiple cores executing a program represented as a sequence of instructions. The Processor class manages the cores and memory, while the Core class represents individual cores responsible for executing instructions.

- #### _Processor Class_-
  The Processor class manages multiple cores and program execution. It contains a memory, multiple cores, and a clock. The run method iterates over each core, executing its program until completion. Additionally, it provides methods to set the program for a specific core, retrieve core registers, and access memory.
  There are Various Functions in Processor Class -
  - Constructor : Initializes the processor with memory and a specified number of cores. Automatically called when an object of type Processor is created.
  - maxProgramLength():: Determines the maximum program length among all cores. Used to determine the length of the longest program among all cores.
  - run(): Executes programs on all cores until completion. Initiates the execution of programs on all cores.
  - setCoreProgram(): Sets the program for a specified core. Used to load a program into a specific core.
  - getCore(): Retrieves a reference to a specific core. Used to access a particular core for operations or data retrieval.
  - getCoreRegisters(): Retrieves the registers of a specific core. Used to access the registers of a particular core.
  - getMemory(): Retrieves a reference to the processor's memory. Used to access or modify the processor's memory.
   
- #### _main() function-_
  The entry point of the program where the simulation is configured and executed. Initializes the processor, sets the program for a core, runs the simulation, and prints the registers of the core after execution.

---
## Instructions
The C++ code simulates a processor executing a series of instructions. Each instruction corresponds to a specific operation in a simplified instruction set architecture (ISA).The supported instructions are as follows:
- add: Add two registers and store the result in another register.
- addi: Add an immediate value to a register and store the result in another register.
- sub: Subtract one register from another and store the result in another register.
- beq: Branch if two registers are equal.
- ble: Branch if one register is less than or equal to another.
- bgt: Branch if one register is greater than another.
- j: Unconditional jump to a label.
- srl: Logical right shift a register by a specified amount.
- sll: Logical left shift a register by a specified amount.
- slt: Set a register to 1 if one register is less than another, otherwise set it to 0.
- li: Load an immediate value into a register.
- lw: Load a word from memory into a register.
- sw: Store a word from a register into memory.

---
## Example
An example program is provided in the main function of the code. It sets up a single-core processor, loads a program into the core, and runs the simulation. The program performs a simple loop with arithmetic and shifting operations.

Processor sim(1);
sim.setCoreProgram(0, {
    .data
    .text
    addi 4 0 0
    addi 5 0 8
    addi 1 0 20
    loop:
    beq 4 5 exit
    addi 1 1 1
    addi 2 1 3
    add 3 1 2
    addi 4 4 1
    j loop
    exit:
    srl 5 5 1
    sll 4 4 1
});
sim.run();
for (int i = 0; i < 1; ++i) {
    const vector<int>& regs = sim.getCoreRegisters(i);
    for (int reg : regs) {
        cout << reg << " ";
    }
    cout << endl;
}
first of all we just make base code to check wheather every instructions that we made are working properly or not. It was mainly checking branch instruction and jump instructions for given base code. At the end it was working properly so our base was perfect at that time now after that we tried to manipulation of memory to work code properly.
