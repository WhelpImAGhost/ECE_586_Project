# ECE 586 FINAL PROJECT (Winter 2026) <br /> RISC-V ISA Simulation 
### Chris Kane-Pardy & Violet Monti

## Description of main.c
The purpose of this code is to simulate the RISC-V 32I Instruction Set Architecture, demonstrating how literal data is moved around between simulated memory locations and the simulated registers. The input program has a limit of 64K bytes, but this can be changed with the MEMORY_SIZE define in the defines.c file. 

## Simulation Usage
- This program was compiled using GCC via command-line tools within a terminal. Nothing special is needed to compile.
- At compile time, the argument -DDEBUG can be added for a high verbosity output for debugging and testing/reporting
- This program can be run with no arguments. The default options will operate in a silent mode, where only the Program Counter and the value of each register is outputted, and the default input file is [flw.mem](https://github.com/WhelpImAGhost/ECE_586_Project/blob/main/Mem_files/Float_mem/flw.mem).
- The input file can be changed with the argument "-f <path to file>"
- The detailed verbosity (excluding debug statements) can be changed with the argument "-m 1", which will print the current instruction, the PC for that instruction, and the current values of each register before running the current instruction
- The program can be put into step-through mode by using the argument "-step 1"
- Break points can be added to the loaded memory file by using the argument "-bp 1"
- The program can be set to watch locations in memory or specific registers, printing the values after each instruction for each position that is watched, using the arguments "-w 1"

## Changing Parameters
Default parameters, such as memory size, input starting address, and stack starting address, can all be changed within the defines.C program. The memory size value is stored as the "power of two" number of bits for the program. For example, 19 corresponds to 2^19 bits, or 2^16 bytes, which is 64K bytes. The other two values must be contained within 0 to 2^(Memory Size value), otherwise the program will terminate wtih an error. 

## Additional features
A GUI has been included for use with this simulation. While rudimentary and basic, it allows for easily switching between input files and runtime arugments, without having to retype entire commands into the command line. Based on the PyQT GUI documentation, PyQT 6 (or newer) must be installed. After installation, the GUI can be launched by running the [main.py](https://github.com/WhelpImAGhost/ECE_586_Project/main.py) file. The file to run must be entered in the topmost bar, with the runtime arguments in the bar below it. The bar at the bottom of the GUI is for responding to prompts from the program or providing inputs for tasks such as breakpoints or location watching. 

## Test cases
The .mem memory files used for testing our program can be found in the [Mem_files](https://github.com/WhelpImAGhost/ECE_586_Project/tree/main/Mem_files) folder. These memory files are formatted to show the memory location of each instruction as well as the hexadecimal encoding of the instruction at that location. However, this does make reading and understanding the files difficult, so the .s assembly files can be found in the [Test_Progs](https://github.com/WhelpImAGhost/ECE_586_Project/tree/main/Test_Progs) folder. Each folder has the instructions separated largely based on format, with the exception being the Float instructions and the Multiply Extension instructions, which have their own folders. More information can be found regarding the contents and the testing of the program and of these files in our Test Plan document, linked below.

## Documentation

### Project Report
([ECE 586 RISC-V ISA Simulation Final Report](https://www.overleaf.com/read/fvhgtfznjnkt#011c4b))

### Test Plan
([ECE 586 RISC-V ISA Simulation Test Plan (Team #2)](https://www.overleaf.com/read/pkxwrkrxyvph#52e191))
