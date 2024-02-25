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