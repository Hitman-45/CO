# RIPE SIMULATION-CPP
## Team :- Wushangclan
#### CS22B005 Ambaliya Shankheshkumar M
#### CS22B016 Chatse Siddhant M
## About

Date:- 7-March-2024
Members : Shankhesh and siddhant
Decisions : we will separate out the memory and write back stage from the execution function and we'll calculate the stall and IPC for without data forwading stages.Here we face so many difficulties while calculating and manipulating stalls. from here onwards wherever we need to change anything in stall we will change functions accordingly.

Date:- 5-March-2024
Members : Shankhesh and siddhant
Decisions : we separated excution stage also. we will calculate retired instructions.Here we saperated instructions into four parts arithmetic, memory, branch and bitwise instruction on that behave it'll execute the instructions.

Date:- 2-March-2024
Members : Shankhesh and siddhant
Decisions : we have decide to seprate 5 stages of pipeline in next 3 days in which we will separate it from entire function of five stages. But starting was very hard so just IF and decode took 2 days in seprating.

---
This C++ program simulates a basic RISC-V-like processor architecture. It includes a simple processor class (Processor) and a core class (Core) that executes RISC-V-like instructions. The simulation is designed to mimic the behavior of a RISC-V processor using the Ripes simulator.
---
## Code Overveiw
The C++ code consists of two important classes: Core and Processor and a main function. This program simulates a processor with multiple cores executing a program represented as a sequence of instructions. The Processor class manages the cores and memory, while the Core class represents individual cores responsible for executing instructions.
- #### Core Class-
  The Core class represents a single core of the Ripes processor. It contains registers, a program counter (pc), and a program memory (program). The execute method interprets and executes instructions from the program memory. There are Various Functions in Core Class -
  - Constructor : Initializes the core with 32 registers and sets the program counter to 0. It Automatically called when an object of type Core is created.
  - execute() : Executes instructions from the program stored in the core's memory. It is Called to execute instructions. It takes a reference to the memory vector to potentially interact with external memory.
  - loadProgram() : Loads a program into the core's memory. It is Used to set the program that the core will execute.
  - getRegisters():It Returns a reference to the core's registers. It is Used to access or modify the registers of the core.
- #### Processor Class-
  The Processor class manages multiple cores and program execution. It contains a memory, multiple cores, and a clock. The run method iterates over each core, executing its program until completion. Additionally, it provides methods to set the program for a specific core, retrieve core registers, and access memory.
  There are Various Functions in Processor Class -
  - Constructor : Initializes the processor with memory and a specified number of cores. Automatically called when an object of type Processor is created.
  - maxProgramLength():: Determines the maximum program length among all cores. Used to determine the length of the longest program among all cores.
  - run(): Executes programs on all cores until completion. Initiates the execution of programs on all cores.
  - setCoreProgram(): Sets the program for a specified core. Used to load a program into a specific core.
  - getCore(): Retrieves a reference to a specific core. Used to access a particular core for operations or data retrieval.
  - getCoreRegisters(): Retrieves the registers of a specific core. Used to access the registers of a particular core.
  - getMemory(): Retrieves a reference to the processor's memory. Used to access or modify the processor's memory.
   
- #### main() function-
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
- srli: Logical right shift a register by a specified amount.
- slli: Logical left shift a register by a specified amount.
- slt: Set a register to 1 if one register is less than another, otherwise set it to 0.
- li: Load an immediate value into a register.
- lw: Load a word from memory into a register.
- la: Load a address of given label into given register.
- sw: Store a word from a register into memory.
---
## Challenges 
- First of all while writing the code we got stuck in how can we load program such that it can be accesable in core class. In core class we have written methods and diffrent instruction hendling as example add, addi, la, lw slli, sw etc. after than we have to use registers for given program and their instructions.
- After core class we started processor class in which we have memory and through this class we are sending memory into core class and handling it. But the problem was that how can we send it but after all we were ale to manage it through run function. In processor we have given option for multiple cores. So from Processor class we are handling multiple cores.
- First of all through setCoreProgram we are loading the program in core class withj help of core no. As an example if you type (core no i, program) that program will load in ith core.
- we are facing difficuties so we decided not to write x before any register so as per our design no need to write x before each and every registers that's the main point.
- After loading the program we have to differentiate .data part and .text part. Here .data part stored in memory segment. It was a bit confusing like how can we store but after an idea we are sending memory as an address such that our processor class should have same memory that has been worked through core class. After all it was a efficiently working.
- Now we stuck at place like how can we know that la is searching for that thing only which is required to manage it we needed another vector which will store memory's specific things lables and their address.
- By that we started lw and sw function after all it was working and that was motivating to complete it.After that we are passing just direct instruction through main and they were working. Then we modifed it witha minor changes.
- Now there was a time to load a code through file and we load it through file but file was not loading properly so we have to study little bit about it after all that Our code was ready for single core and it was working.
- Last part of code just trasfer single core to dualcore we just changed number of core as an input from one to two.But the problem was that it was mixing memory of both cores that was a bit surpising so we started finding an error. It was a small error but it took almost half day on saturday.After all this we load file in both cores and Our code is working so good.

---
## Note
- Due to simplify code we are not writing x before any register and if you write x before register it won't work as per our simulator design.
---

---
## Learnings
- Object-Oriented Design:
  - The project demonstrates a clear understanding of object-oriented design principles by organizing functionality into classes (Core and Processor) with well-defined responsibilities.
  - Each class encapsulates related data (e.g., registers, program counter) and behavior (e.g., executing instructions, loading programs) within its own scope, promoting modularity and reusability.
- Memory Management:
  - The project demonstrates memory management techniques through the use of vectors to represent memory (Processor's memory) and programs (Core's program).
  - By utilizing vectors, the program efficiently manages memory allocation and deallocation, ensuring dynamic storage needs are met while maintaining performance.
- Instruction Set Simulation:
  - The project simulates the execution of a simplified instruction set architecture (ISA) through the Core class's execute function, which interprets and executes instructions based on opcode.
  - By implementing various arithmetic (add, subtract), logical (shift), and control (branch) instructions, the project provides a practical example of how processors interpret and execute instructions, aiding in understanding low-level computing concepts.
- Error Handling:
  - The project demonstrates basic error handling techniques by checking for out-of-bounds accesses (e.g., in the execute function) and ensuring proper bounds checking to prevent memory access violations.
  - This promotes robustness and reliability in the simulation, preventing potential crashes or undefined behavior due to accessing memory or program instructions beyond their bounds.

---