/****
 ECE 586 Final Project
 Team 2

 Objective: Simulate a RISCV-32I processor Instruction Set Architecture

 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "defines.c"

#ifdef _WIN32
    #include <io.h>
    #define _READ _read
    #define _WRITE _write
    #define EXPORT __declspec(dllexport)
#else
    #include <unistd.h>
    #define _READ read
    #define _WRITE write
    #define EXPORT __attribute__((visibility("default")))
#endif



// Function prototypes for printing Mem and Reg values
void printAllMem(uint32_t array[], int size);
void printAllReg(uint32_t regs[32], char regnames[32][8]);
void printAllFPReg(float regs[32]);

// Base function prototypes
uint32_t readByte(uint32_t array[], int size, int address);
uint32_t readHalfWord(uint32_t array[], int size, int address);
uint32_t readWord(uint32_t array[], int size, int address);
int writeByte(uint32_t array[], int size, int address, uint32_t value);
int writeHalfWord(uint32_t array[], int size, int address, uint32_t value);
int writeWord(uint32_t array[], int size, int address, uint32_t value);
void fetch_and_decode(uint32_t array[], uint32_t pc, uint32_t* opcode, int mode);

// Addressing Mode Function Prototypes
void r_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void i_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void load(uint8_t function, uint8_t destination, uint8_t source, int32_t immediate, uint32_t array[], int size, uint32_t reg_array[32]);
void immediateop(uint8_t function, uint8_t destination, uint8_t source, int32_t immediate, uint32_t array[], int size, uint32_t reg_array[32]);
void s_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void b_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void u_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void j_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void e_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);

// Floating Point functions
void f1_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32], float flt_array[32]);
void f2_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32], float flt_array[32]);
void f3_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32], float flt_array[32]);
float flt_round(float value, int rm);
void fclass_s(float value, uint32_t *out);

// Extra credit functions for Step, Breakpoint, and Watching
int breakpointInput(int array[]);
int breakpointCheck(int bppc[], int numBPs, uint32_t instruction, uint32_t array[], int size, uint32_t regs[32], char regnames[32][8], float fregs[32], int MemWords, int step);
int singleStep(uint32_t instruction, uint32_t array[], int size, uint32_t regs[32], char regnames[32][8], float fregs[32], int MemWords, int step);
void watchingUserInput(uint32_t regindex[], uint32_t fregindex[], uint32_t memindex[], int *numRegs, int *numFregs, int *numMems);
void watchingOutput(int numIntRegs, int numFloatRegs, int numMemLocals, uint32_t watchedRegs[], uint32_t watchedFregs[], uint32_t watchedMem[], uint32_t reg[32], char names[32][8], float freg[32], uint32_t mem[32]);


// Set default mode
int mode = 0;  // 0 is silent
                // 1 is verbose
                // 2 is step through

// Default to Breakpoints Off
int breakpoints = 0;

// Default to watching to Off
int watching = 0;

// Default to step Off
int step = 0;

// Main
int main(int argc, char *argv[]){

    uint32_t test_word;
    char test_str[10];

    // Local variables for function use
    uint32_t address, instruction, pc = START_ADDRESS;
    uint32_t current_opcode;
    bool continue_program = true;    

    char regnames[32][8] = {
                    "(zero)", "(ra)", "(sp)", "(gp)", "(tp)", "(t0)", "(t1)", "(t2)",
                    "(s0)", "(s1)", "(a0)", "(a1)", "(a2)", "(a3)", "(a4)", "(a5)",
                    "(a6)", "(a7)", "(s2)", "(s3)", "(s4)", "(s5)", "(s6)", "(s7)",
                    "(s8)", "(s9)", "(s10)", "(s11)", "(t3)", "(t4)", "(t5)", "(t6)"
    };

    // Register declarations
    uint32_t x[32];
    x[0] = 0; //zero
    x[1] = 0; //ra
    x[2] = 0; //sp

    // Floating point Register Declarations
    float f[32];

    uint32_t old_pc = 0;

    
    int numMemoryLocals = 0;
    int numRegs = 0;
    int numFregs = 0;
    uint32_t watchReg[32];
    uint32_t watchFreg[32];
    uint32_t watchMem[100];

    // Memory & Stack Starting Addresses
    uint32_t stack_address = STACK_ADDRESS;

    // Set default filename
    char *default_filename = "Mem_files/Float_mem/flw.mem";
    char *filename = default_filename;

    // Flags for setting non-default variable values
    for (argc--, argv++; argc > 0; argc -= 2, argv += 2)
    {
        if (strcmp(argv[0], "-f") == 0) filename = argv[1]; // Set input file
        
        else if (strcmp(argv[0], "-m") == 0) mode = atoi(argv[1]); // Set operation mode
        
        else if (strcmp(argv[0], "-step") == 0) step = atoi(argv[1]); // Set operation mode
        
        else if (strcmp(argv[0], "-bp" ) == 0 ) breakpoints = atoi(argv[1]); // Set breakpoint mode
        
        else if (strcmp(argv[0], "-w" ) == 0 ) watching = atoi(argv[1]); // Set watching mode
        
        else if (strcmp(argv[0], "-p") == 0) {
            if ((strtol(argv[1], NULL, 16) % 4) != 0) fprintf(stderr, "Invalid stack pointer delcaration. Defaulting to 0x10000\n");
            else stack_address = (uint32_t)strtol(argv[1], NULL, 16); // Set stack pointer
        }

        else if (strcmp(argv[0], "-s") == 0) {
            if ((strtol(argv[1], NULL, 16) % 4) != 0) fprintf(stderr, "Invalid starting PC delcaration. Defaulting to 0\n");
            else pc = (uint32_t)strtol(argv[1], NULL, 16);   // Set starting address
        }

        else {
            fprintf(stderr, "\nInvalid Argument(s)\n");
            exit(-1);
        }
    }
    FILE *file = fopen(filename, "r");

    // Number of words that can be stored in memory array (2048 by default)
    const int MemWords = (int) (pow(2,MEMORY_SIZE) / 32);

    // Initialization of memory array
    uint32_t MainMem[MemWords];
    for (int i = 0; i < MemWords; i++){
        MainMem[i] = 0;
    }

    // If the provided file can't be opened, try the default file
    if (file == NULL){
        fprintf(stderr, "The '%s' file provided can't be opened. Attempting to open defult file '%s'. \n", filename, default_filename);
        filename = default_filename;
        file = fopen(filename, "r");
    }

    // Check if the file (either provided or default) was successfully opened
    if (file == NULL) {
        perror("Error opening file"); // Exit the program if file opening fails
        exit(-1);
    }

    // File used for execution
    #ifdef DEBUG
    fprintf(stdout, "Using file: '%s'\n", filename);
    #endif

    // Allocating Memory Size (64KB by default)
    const int MemAlloc = pow(2, MEMORY_SIZE);

    // Load instructions into memory array
    while (fscanf(file, "%x: %x", &address, &instruction ) == 2){

        // Error whem memory address is outside the bounds of memory size declared
        if (address >= MemAlloc) fprintf(stderr, "Address 0x%08X is out of memory bounds\n", address);

        // Size of instruction
        MainMem[address / 4] = instruction;

        // Body for parsing lines
        #ifdef DEBUG
        fprintf(stdout, "Extracted memory addresss:      0x%08X\n", address);
        fprintf(stdout, "Extracted instruction contents: 0x%08X\n", instruction);
        #endif

    }

    x[2] = stack_address;


    int BreakPC[20];
    int numBreakpoints = 0;
    if(breakpoints == 1) numBreakpoints = breakpointInput(BreakPC);

    // Check if PC is outside of our memory range
    if (pc > (MemWords * 4)) {
        fprintf(stderr, "PC was set to an address larger than the program size. Exiting...");
        exit(-1);
    }  

    // Check if stack address is outside of memory range
    else if (x[2] > (MemWords * 4)){
        fprintf(stderr, "Stack Address was set to an address larger than the program size. Exiting...");
        exit(-1);
    }

    if (watching == 1)
    {
        for (int i = 0; i < 32; i++)
        {
            watchReg[i] = -1;
            watchFreg[i] = -1;
        }
        for (int i = 0; i < 100; i++)
        {
            watchMem[i] = -1;
        }

        watchingUserInput(watchReg, watchFreg, watchMem, &numRegs, &numFregs, &numMemoryLocals);
    }

    // Begin fetching and decoding instructions
    while(continue_program){        
        fetch_and_decode(MainMem, pc, &current_opcode, mode);
        old_pc = pc;
        switch (current_opcode) {
            case REGS_OP:
                #ifdef DEBUG
                fprintf(stdout, "0x%02X is a Register Instruction\n", current_opcode);
                #endif
                r_type(MainMem, MemWords, &pc, x);
                pc += 4;
                break;

            case IMMS_OP:
            case LOAD_OP:
            case JALR_OP:
                #ifdef DEBUG
                fprintf(stdout, "0x%02X is an Immediate Instruction\n", current_opcode);
                #endif
                i_type(MainMem, MemWords, &pc, x);
                if (pc == 0x0) {
                    #ifdef DEBUG
                    fprintf(stdout, "End of Program\n");
                    #endif
                    continue_program = false;
                }
                break;

            case STOR_OP:
                #ifdef DEBUG
                fprintf(stdout, "0x%02X is a Store Instruction\n", current_opcode);
                #endif
                s_type(MainMem, MemWords, &pc, x);
                pc += 4;
                break;

            case BRAN_OP:
                #ifdef DEBUG
                fprintf(stdout, "0x%02X is a Branch Instruction\n", current_opcode);
                #endif
                b_type(MainMem, MemWords, &pc, x);
                break;

            case JAL_OP:
                #ifdef DEBUG
                fprintf(stdout, "0x%02X is a Jump Instruction\n", current_opcode);
                #endif
                j_type(MainMem,MemWords, &pc, x);
                if (pc == 0x0) {
                    #ifdef DEBUG
                    fprintf(stdout, "End of Program\n");
                    #endif
                    continue_program = false;
                }
                break;

            case LUI_OP:
            case AUIPC:
                #ifdef DEBUG
                fprintf(stdout, "0x%02X is an 'Upper Immediate' Instruction\n", current_opcode);
                #endif
                u_type(MainMem, MemWords, &pc, x);
                pc += 4;
                break;

            case FLW:
            case FSW:
                f2_type(MainMem, MemWords, &pc, x, f);
                break;
                
            case FMADDS:
            case FMSUBS:
            case FNMSUBS:
            case FNMADDS:
                f3_type(MainMem, MemWords, &pc, x, f);
                break;
            
            case FL_OP:
                f1_type(MainMem, MemWords, &pc, x, f);
                break;

            case ENVIRO:
                #ifdef DEBUG
                fprintf(stdout, "E-type Instruction");
                #endif 
                e_type(MainMem, MemWords, &pc, x);
                break;
            default:
                fprintf(stderr, "0x%02X is an invalid op code.\n", current_opcode);
                exit(1);
        }

        if (breakpoints == 1 && step == 0) step = breakpointCheck(BreakPC, numBreakpoints, old_pc, MainMem, MemWords, x, regnames, f, MemWords, step);
        else if (breakpoints == 1 && step == 1) step = singleStep(old_pc, MainMem, MemWords, x, regnames, f, MemWords, step);
        else if (breakpoints == 0 && step == 1) step = singleStep(old_pc, MainMem, MemWords, x, regnames, f, MemWords, step);
        if (watching == 1) watchingOutput(numRegs, numFregs, numMemoryLocals, watchReg, watchFreg, watchMem, x, regnames, f, MainMem);
        if (mode == 1) printAllReg(x, regnames);
        if (mode == 1) printAllFPReg(f);
    }


    // Silent mode prints
    if (mode == 0) printAllReg(x, regnames);
    if (mode == 0) printAllFPReg(f);
    if (mode == 0) fprintf(stdout, "PC at final instruction: 0x%08X\n", old_pc);

    
    #ifdef DEBUG
    printAllMem(MainMem, MemWords);
    #endif

    return 0;
}

// Memory dump function for debugging
void printAllMem(uint32_t array[], int size){

    fprintf(stdout, "\n");
    for (int i = 0; i < size; i++)
    {
        if (array[i] != 0x0) printf(/*Array Member: %4d*/ "Memory Address: 0x%08X     Contents: 0x%08X\n", /*i,*/ 4 * i, array[i]);
    }
    return;
}

// Function to display all register values
void printAllReg(uint32_t regs[32], char regnames[32][8] ){

    for (int i = 0; i < 32; i++){
        printf("Register: x%02d %-6sContents: ", i, regnames[i]);
        printf("%08X", regs[i]);
        #ifdef DEBUG
        printf(" (%d)", regs[i]);
        #endif
        printf("\n");

    }
    printf("\n");
    fflush(stdout);
}

// Function to read a specific byte from memory
uint32_t readByte(uint32_t array[], int size, int address) {

    int target_block = address / 4;
    int target_byte = address % 4;

    uint32_t selected_word = array[target_block];
    selected_word = selected_word >> (8 * target_byte);
    uint32_t selected_byte = selected_word & 0x000000FF;

    return selected_byte;
}

// Function to read a specific half-word (alligned) from memory
uint32_t readHalfWord(uint32_t array[], int size, int address){

    if (address % 2 != 0) {
        fprintf(stderr, "Misaligned reference at 0x%08x\n", address);
        exit(1);
    }
    else{
        int target_block = address / 4;
        int target_hw;
        
        if (address % 4 == 2)  target_hw = 2;
        else if (address % 4 == 0)target_hw = 0; 
        else {
            fprintf(stderr, "Misaligned reference at 0x%08x\n", address);
            exit(1);
        }

        uint32_t selected_word = array[target_block];
        selected_word = selected_word >> (8 * target_hw);
        uint32_t selected_hw = selected_word & 0x0000FFFF;

        return selected_hw;
    }

}

// Function to read a specific word from memory
uint32_t readWord(uint32_t array[], int size, int address){

    if (address % 4 != 0) {
        fprintf(stderr, "Misaligned reference at 0x%08x\n", address);
        exit(1);
    }

    int target_block = address / 4;
    uint32_t selected_word = array[target_block];

    return selected_word;

}

// Function to write to a specific byte from memory
int writeByte(uint32_t array[], int size, int address, uint32_t value) {

    int target_block = address / 4;
    int target_byte = address % 4;

    array[target_block] = (array[target_block] & ~(0xFF << (8 * target_byte)));
    array[target_block] = array[target_block] | ((value & 0xFF) << (8 * target_byte));
    return 0;

}

// Function to write to a specific half-word in memory
int writeHalfWord(uint32_t array[], int size, int address, uint32_t value) {

    if (address % 2 != 0) {
        fprintf(stderr, "Misaligned reference at 0x%08x\n", address);
        exit(1);
    }
    else{
        int target_block = address / 4;
        int target_hw;
        
        if (address % 4 == 2) {
            target_hw = 2;
            uint32_t selected_word = array[target_block];
            selected_word = selected_word & 0x0000FFFF;
            value = value << 16;
            array[target_block] = value | selected_word;
            
        } 
        else {
            target_hw = 0;
            uint32_t selected_word = array[target_block];
            selected_word = selected_word & 0xFFFF0000;
            array[target_block] = value | selected_word;
        }
        return 0;
    }

}

// Function to write to a specific word in memory
int writeWord(uint32_t array[], int size, int address, uint32_t value) {

    if (address % 4 != 0) {
        fprintf(stderr, "Misaligned reference at 0x%08x\n", address);
        exit(1);
    }
    int target_block = address / 4;
    array[target_block] = value;

    return 0;

}

// Function to fetch the current instruction and reurn the opcode for parsing
void fetch_and_decode(uint32_t array[], uint32_t pc, uint32_t *opcode, int mode){

    uint32_t selected_instruction = array[pc / 4];
    *opcode = selected_instruction & 0x0000007F;

    if (mode == 1)fprintf(stdout, "Current PC:          0x%08X\n", pc);
    if (mode == 1)fprintf(stdout, "Current Instruction: 0x%08X\n", selected_instruction);
    return;
}

// R-type function breakdown and execution, including the Mult extension
void r_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]){

    uint8_t func7, rs2, rs1, func3, rd, opcode;
    uint32_t instruction = mem_array[*pc / 4];

    opcode = instruction & 0x7F;
    rd = (instruction >> 7 ) & 0x1F;
    func3 = (instruction >> 12) & 0x7;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    func7 = (instruction >> 25) & 0x7F;

    int64_t reg_64;
    uint64_t ureg_64;

    int32_t rs1_signed = reg_array[rs1];
    int32_t rs2_signed = reg_array[rs2];

    #ifdef DEBUG
    fprintf(stdout, "R-Type instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    R_S2: 0x%02X\n    Func7: 0x%02X\n", opcode, rd, func3, rs1, rs2, func7);
    #endif

    switch(func3){

        case 0x0: 
            switch(func7){
                case 0x00: // add
                    #ifdef DEBUG
                    fprintf(stdout, "Adding 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd] = reg_array[rs1] + reg_array[rs2];
                    break;
                case 0x01: // mul
                    #ifdef DEBUG
                    fprintf(stdout, "Multiplying 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd]= rs1_signed * rs2_signed;
                    break;
                case 0x20: // sub
                    #ifdef DEBUG
                    fprintf(stdout, "Subtracting 0x%08X (the contents of register x%d) from 0x%08X (the contents of register x%d) and placing the result in register x%d \n",   reg_array[rs2], rs2, reg_array[rs1], rs1, rd);
                    #endif
                    reg_array[rd] = reg_array[rs1] - reg_array[rs2];
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC7 code for FUNC3 code 0x%X\n", func7, func3);
                    exit(1);
            }
            break;
        case 0x4: 
            switch (func7) {
            case 0x00: // xor
                #ifdef DEBUG
                fprintf(stdout, "XOR 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                #endif
                reg_array[rd] = reg_array[rs1] ^ reg_array[rs2];
                break;
            case 0x01: // div
                #ifdef DEBUG
                fprintf(stdout, "Dividing 0x%08X (the contents of register x%d) by 0x%08X (the  contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                #endif
                if (rs2_signed == 0) {
                    fprintf(stderr, "Division by zero error\n");
                    exit(1);
                }
                reg_array[rd] = rs1_signed / rs2_signed;
                break;
            default:
                fprintf(stderr, "0x%X is not a valid FUNC7 code for FUNC3 code 0x%X\n", func7, func3);
                exit(1);
            }
            break;
        case 0x6: 
            switch(func7){
                case 0x00: // or
                    #ifdef DEBUG
                    fprintf(stdout, "OR 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd] = reg_array[rs1] | reg_array[rs2];
                    break;
                case 0x01: // rem
                    #ifdef DEBUG
                    fprintf(stdout, "Dividing 0x%08X (the contents of register x%d) by 0x%08X (the contents of register x%d) and placing the remainder in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    if (rs2_signed == 0) {
                        fprintf(stderr, "Division by zero error\n");
                        exit(1);
                    }
                    reg_array[rd] = rs1_signed % rs2_signed;
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC7 code for FUNC3 code 0x%X\n", func7, func3);
                    exit(1);  
            }
            break;
        case 0x7: // and
            switch(func7){
                case 0x00:
                    #ifdef DEBUG
                    fprintf(stdout, "AND 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd] = reg_array[rs1] & reg_array[rs2];
                    break;
                case 0x01: // remu
                    #ifdef DEBUG
                    fprintf(stdout, "Dividing 0x%08X (the unsigned contents of register x%d) by 0x%08X (the unsigned contents of register x%d) and placing the remainder in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    if (reg_array[rs2] == 0) {
                        fprintf(stderr, "Division by zero error\n");
                        exit(1);
                    }
                    reg_array[rd] = reg_array[rs1] % reg_array[rs2];
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC7 code for FUNC3 code 0x%X\n", func7, func3);
                    exit(1);  
            }
            break;
        case 0x1: 
            switch(func7){
                case 0x00: // Shift Left Logical 
                    #ifdef DEBUG
                    fprintf(stdout, "Shift Left 0x%08X (the contents of register x%d) by 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd] = reg_array[rs1] << (reg_array[rs2] & 0x1F);
                    break;
                case 0x01: // mul high
                    #ifdef DEBUG
                    fprintf(stdout, "Multiplying 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the higer 32 bits in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_64 = ((int64_t)rs1_signed *(int64_t)rs2_signed);
                    reg_array[rd] = reg_64 >> 32;
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC7 code for FUNC3 code 0x%X\n", func7, func3);
                    exit(1);
            }
            break;
        case 0x5: // Shift Right
            switch (func7){
                case 0x00: // Shift Right Logical
                    #ifdef DEBUG
                    fprintf(stdout, "Shift Right (Logical) 0x%08X (the contents of register x%d) by 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd] = reg_array[rs1] >> (reg_array[rs2] & 0x1F);
                    break;
                case 0x01: // div U
                    #ifdef DEBUG
                    fprintf(stdout, "Dividing 0x%08X (the contents of register x%d) by 0x%08X (the  contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    if (reg_array[rs2] == 0) {
                        fprintf(stderr, "Division by zero error\n");
                        exit(1);
                    }
                    reg_array[rd] = reg_array[rs1] / reg_array[rs2];
                    break;
                case 0x20: // Shift Right Arithmetic
                    #ifdef DEBUG
                    fprintf(stdout, "Shift Right (Arithmetic) 0x%08X (the contents of register x%d) by 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd] = rs1_signed >> (reg_array[rs2] & 0x1F);
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC7 code for FUNC3 code 0x%X\n", func7, func3);
                    exit(1);
            }
            break;
        case 0x2: 

            switch (func7){
                case 0x00: // Set Less Than
                    #ifdef DEBUG
                    fprintf(stdout, "Set register x%d to 1 if 0x%08X (the contents of x%d) is less than 0x%08X (the contents of x%d), otherwise set it to 0\n",rd, reg_array[rs1], rs1, reg_array[rs2], rs2);
                    #endif
                    reg_array[rd] = (rs1_signed < rs2_signed) ? 1 : 0;
                    break;
                case 0x01: // mulh S U
                    #ifdef DEBUG
                    fprintf(stdout, "Multiplying 0x%08X (the contents of register x%d) and 0x%08X (the unsigned contents of register x%d) and placing the higer 32 bits in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_64 = ((int64_t)rs1_signed * (uint64_t)reg_array[rs2]);
                    reg_array[rd] = reg_64 >> 32;
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC7 code for FUNC3 code 0x%X\n", func7, func3);
                    exit(1);
            }
            break;
        case 0x3:
            switch (func7){
                case 0x00: // Set Less Than Unsigned
                    #ifdef DEBUG
                    fprintf(stdout, "(UNSIGNED) Set register x%d to 1 if 0x%08X (the contents of x%d) is less than 0x%08X (the contents of x%d), otherwise set it to 0\n",rd, reg_array[rs1], rs1, reg_array[rs2], rs2);
                    #endif
                    reg_array[rd] = (reg_array[rs1] < reg_array[rs2]) ? 1 : 0;
                    break;
                case 0x01: // mul u
                    #ifdef DEBUG
                    fprintf(stdout, "Multiplying 0x%08X (the unsigned contents of register x%d) and 0x%08X (the unsigned contents of register x%d) and placing the higer 32 bits in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    ureg_64 = ((uint64_t)reg_array[rs1] * (uint64_t)reg_array[rs2]);
                    reg_array[rd] = ureg_64 >> 32;
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC7 code for FUNC3 code 0x%X\n", func7, func3);
                    exit(1);
            }
            break;
        default:
        fprintf(stderr, "0x%X is not a valid Register FUNC3 code\n", func3);
        exit(1);
    }
    if(rd == 0 ){
        reg_array[0] = 0x00000000;
    }

    return;

}

// Function to break down different I-type instructions and react accordingly
void i_type(uint32_t mem_array[], int size, uint32_t* pc, uint32_t reg_array[32]){

    uint8_t rs1, func3, rd, opcode;
    int32_t imm;
    uint32_t instruction = mem_array[*pc / 4];

    opcode = instruction & 0x7F;
    rd = (instruction >> 7 ) & 0x1F;
    func3 = (instruction >> 12) & 0x7;
    rs1 = (instruction >> 15) & 0x1F;
    imm = (instruction >> 20) & 0xFFF;

    int immmsb = (imm >> 11) & 0x00000001;
    if (immmsb == 1){
        imm = imm | 0xFFFFF000;
    }else{
        imm = imm & ~(0xFFFFF000);
    }

    uint32_t ex_address = *pc + imm;
    #ifdef DEBUG
    fprintf(stdout, "I-Type instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    Immediate: 0x%03X\n", opcode, rd, func3, rs1, imm);
    #endif

    // Split up function call for different I-type opcodes
    switch (opcode){
        case LOAD_OP:
            load(func3, rd, rs1, imm, mem_array, size, reg_array);
            *pc += 4;
            break;
        case IMMS_OP:
            immediateop(func3, rd, rs1, imm, mem_array, size, reg_array);
            *pc += 4;
            break;
        case JALR_OP:
        #ifdef DEBUG
            fprintf(stdout, "pc before jump: 0x%08x \n", *pc);
        #endif
            if ((ex_address % 4) != 0){
                fprintf(stderr, "Error: computed address 0x%08X is not word aligned\n", ex_address);
                exit(1);
            }
            else if ((ex_address > (size * 4)) || ex_address < 0){
                fprintf(stderr, "Error: computed address 0x%08X is out of program range\n", ex_address);
                exit(1);
            }
            reg_array[rd] = *pc + 4;
            reg_array[0] = 0x00000000;
            *pc = (reg_array[rs1] + imm) & 0xFFFFFFFE;
        #ifdef DEBUG
            fprintf(stdout, "pc after jump: 0x%08x \n", *pc);
        #endif
            break;
        default:
            fprintf(stderr, "0x%02X is not a valid I-type opcode.\n", opcode);
            exit(1);
    }

    if(rd == 0 ) reg_array[0] = 0x00000000;

    return;

}

// Function to implement the remainder of the I-type instructions
void immediateop(uint8_t function, uint8_t destination, uint8_t source, int32_t immediate, uint32_t array[], int size, uint32_t reg_array[32]){
    uint8_t func7 = (immediate >> 5) & 0x7F; 
    uint8_t shamt = immediate & 0x1F;
    int32_t signedsource = reg_array[source];
    uint32_t unsignedimmediate = immediate;
    switch (function){
    case 0x0: //addi
        #ifdef DEBUG
        fprintf(stdout, "Adding 0x%08X (the contents of register x%d) and 0x%08X and placing the result in register x%d \n", reg_array[source], source, immediate, destination);
        #endif
        reg_array[destination] = signedsource + immediate;
        break;
    case 0x4: //xori
        #ifdef DEBUG
        fprintf(stdout, "Bitwise XORing 0x%08X (the contents of register x%d) and 0x%08X and placing the result in register x%d\n", reg_array[source], source, immediate, destination);
        #endif
        reg_array[destination] = signedsource ^ immediate;
        break;
    case 0x6: //ori
        #ifdef DEBUG
        fprintf(stdout, "Bitwise ORing 0x%08X (the contents of register x%d) and 0x%08X and placing the result in register x%d\n", reg_array[source], source, immediate, destination);
        #endif  
        reg_array[destination] = signedsource | immediate;      
        break;
    case 0x7: //andi
        #ifdef DEBUG
        fprintf(stdout, "Bitwise ANDing 0x%08X (the contents of register x%d) and 0x%08X and placing the result in register x%d\n", reg_array[source], source, immediate, destination);
        #endif
        reg_array[destination] = signedsource & immediate;
        break;
    case 0x1: //slli
        #ifdef DEBUG
        fprintf(stdout, "Logical Shifting 0x%08X Left (the contents of register x%d) by %d and placing the result in register x%d\n", reg_array[source], source, shamt, destination);
        #endif
        reg_array[destination] = reg_array[source] << shamt;
        break;
    case 0x5:
        switch (func7)
        {
        case 0x00: //srli
            #ifdef DEBUG
            fprintf(stdout, "Logical Shifting 0x%08X Right (the contents of register x%d) by %d and placing the result at 0x%08X (register x%d)\n", reg_array[source], source, shamt, reg_array[destination], destination);
            #endif
            reg_array[destination] = reg_array[source] >> shamt;
            break;
        case 0x20: //srai
            #ifdef DEBUG
            fprintf(stdout, "Arithmetic Shifting 0x%08X Right (the contents of register x%d) by %d and placing the result at 0x%08X (register x%d)\n", reg_array[source], source, shamt, reg_array[destination], destination);
            #endif 
            reg_array[destination] = signedsource >> shamt;
            break;
        default:
            fprintf(stderr, "The provided shift instruction is invalid.\n");
            exit(1);
        }
        break;  
    case 0x2: // Set Less Than
        #ifdef DEBUG
        fprintf(stdout, "Set register x%d to 1 if 0x%08X (the contents of x%d) is less than 0x%08X, otherwise set it to 0\n",destination, reg_array[destination], destination, immediate);
        #endif
        reg_array[destination] = (signedsource < immediate) ? 1 : 0;
        break; 
    case 0x3: // Set Less Than Unsigned
        #ifdef DEBUG
        fprintf(stdout, "Set register x%d to 1 if 0x%08X (the contents of x%d) is less than 0x%08X, otherwise set it to 0\n",destination, reg_array[destination], destination, immediate);
        #endif    
        
        reg_array[destination] = (reg_array[source] < unsignedimmediate) ? 1 : 0;

        break;   
    default:
        fprintf(stderr,"The provided immediate instruction is invalid.\n");
        exit(1);
    }

    if(destination == 0 ) reg_array[0] = 0x00000000;
    
    return;

}

// Sub function for Loading I-type instructions
void load(uint8_t function, uint8_t destination, uint8_t source, int32_t immediate, uint32_t array[], int size, uint32_t reg_array[32]){
    uint32_t StoredWord;
    int sign;
    switch (function){
        case 0x0: //lb
            StoredWord = readByte(array, size, (reg_array[source] + immediate));
            sign = (StoredWord >> 7) & 0x00000001;
            if (sign == 1) StoredWord = StoredWord | 0xFFFFFF00;
            else StoredWord = StoredWord & ~(0xFFFFFF00);
            #ifdef DEBUG
            fprintf(stdout, "Loading 0x%08X from memory location 0x%08X to register x%d\n", StoredWord, reg_array[source] + immediate, destination);
            #endif
            reg_array[destination] = StoredWord;
            break;
        case 0x1: //lh
            StoredWord = readHalfWord(array, size, (reg_array[source] + immediate));
            sign = (StoredWord >> 15) & 0x00000001;
            if (sign == 1) StoredWord = StoredWord | 0xFFFF0000;
            else StoredWord = StoredWord & ~(0xFFFF0000);
            #ifdef DEBUG
            fprintf(stdout, "Loading 0x%08X from memory location 0x%08X to register x%d\n", StoredWord, reg_array[source] + immediate, destination);
            #endif
            reg_array[destination] = StoredWord;
            break;
        case 0x2: //lw
            #ifdef DEBUG
            fprintf(stdout, "Loading 0x%08X from memory location 0x%08X to register x%d\n", readWord(array, size, (reg_array[source] + immediate)), reg_array[source] + immediate, destination);
            #endif
            reg_array[destination] = readWord(array, size, (reg_array[source] + immediate));
            break;
        case 0x4: //lbu
            StoredWord = readByte(array, size, (reg_array[source] + immediate));
            #ifdef DEBUG
            fprintf(stdout, "Loading 0x%08X from memory location 0x%08X to register x%d\n", StoredWord, reg_array[source] + immediate, destination);
            #endif
            reg_array[destination] = StoredWord & 0x000000FF;
            break;
        case 0x5: //lhu
            StoredWord = readHalfWord(array, size, (reg_array[source] + immediate));
            #ifdef DEBUG
            fprintf(stderr, "Loading 0x%08X from memory location 0x%08X to register x%d\n", StoredWord, reg_array[source] + immediate, destination);
            #endif
            reg_array[destination] = StoredWord & 0x0000FFFF;
            break;
        default:
            fprintf(stderr, "The provided load instruction is invalid.\n");
           return exit(1);
    }
    if(destination == 0 ) reg_array[0] = 0x00000000;
    
    return;

};


// Function for Store-Type implementation
void s_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]){

    uint8_t imm11_5, rs2, rs1, func3, imm4_0, opcode;
    int32_t imm;
    uint32_t instruction = mem_array[*pc / 4];

    opcode = instruction & 0x7F;
    imm4_0 = (instruction >> 7 ) & 0x1F;
    func3 = (instruction >> 12) & 0x7;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    imm11_5 = (instruction >> 25) & 0x7F;
    imm = (imm11_5 << 5) + imm4_0;

    int immmsb = (imm >> 11) & 0x00000001;
    if (immmsb == 1)imm = imm | 0xFFFFF000;
    else imm = imm & ~(0xFFFFF000);
    

    #ifdef DEBUG
    fprintf(stdout, "S-Type instruction breakdown:\n    Opcode: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    R_S2: 0x%02X\n    Immediate: 0x%04X\n", opcode, func3, rs1, rs2, imm);
    #endif

    // Run different stores depending on func3 value;
    switch(func3){
        case 0x0:
            #ifdef DEBUG
            fprintf(stdout, "Storing 0x%02X @ 0x%08X\n", reg_array[rs2] & 0xFF, reg_array[rs1] + imm);
            #endif
            writeByte(mem_array, size, reg_array[rs1] + imm, reg_array[rs2]);
            break;
        case 0x1:
            #ifdef DEBUG
            fprintf(stdout, "Storing 0x%04X @ 0x%08X\n", reg_array[rs2] & 0xFFFF, reg_array[rs1] + imm);
            #endif
            writeHalfWord(mem_array, size, reg_array[rs1] + imm, reg_array[rs2]);
            break;
        case 0x2:
            #ifdef DEBUG
            fprintf(stdout, "Storing 0x%08X @ 0x%08X\n", reg_array[rs2], reg_array[rs1] + imm);
            #endif
            writeWord(mem_array, size, reg_array[rs1] + imm, reg_array[rs2]);
            break;
        default:
            fprintf(stderr, "0x%02X is not a valid S-type Function3 value.\n", func3);
            exit(1);
    }

    return;
}


// Function for branching instructions (except jumps)
void b_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]){

    uint8_t imm12, imm10_5, rs2, rs1, func3, imm4_1, imm11, opcode;
    int32_t imm;
    uint32_t instruction = mem_array[*pc / 4];

    opcode = instruction & 0x7F;
    imm4_1 = (instruction >> 8 ) & 0xF;
    imm11 = (instruction >> 7) & 0x1;
    func3 = (instruction >> 12) & 0x7;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    imm10_5 = (instruction >> 25) & 0x3F;
    imm12 = (instruction >> 31) & 0x1;
    imm = (imm12 << 12) + (imm11 << 11) + (imm10_5 << 5) + (imm4_1 << 1);

    int immmsb = (imm >> 12) & 0x00000001;
    if (immmsb == 1) imm = imm | 0xFFFFE000;
    else imm = imm & ~(0xFFFFE000);
    

    int32_t rs1_signed = reg_array[rs1];
    int32_t rs2_signed = reg_array[rs2];
    uint32_t ex_address = *pc + imm;

    #ifdef DEBUG
    fprintf(stdout, "B-Type instruction breakdown:\n    Opcode: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    R_S2: 0x%02X\n    Immediate: 0x%04X\n", opcode, func3, rs1, rs2, imm);
    #endif


    switch (func3){

        case 0x0: // ==
            #ifdef DEBUG
            fprintf(stdout, "Comparing 0x%08X (contents of register x%d) == 0x%08X (contents of register x%d)\n", reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            if (rs1_signed == rs2_signed){ 
                #ifdef DEBUG
                fprintf(stdout, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                if ((ex_address % 4) != 0){
                    fprintf(stderr, "Error: computed address 0x%08X is not word aligned\n", ex_address);
                    exit(1);
                }
                else if ((ex_address > (size * 4)) || ex_address < 0){
                    fprintf(stderr, "Error: computed address 0x%08X is out of program range\n", ex_address);
                    exit(1);
                }
                *pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stdout, "Branch not take\n");
                #endif
                *pc += 4;
            }
            break;
        case 0x1: // !=
            #ifdef DEBUG
            fprintf(stdout, "Comparing 0x%08X (contents of register x%d) != 0x%08X (contents of register x%d)\n", reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            if (rs1_signed != rs2_signed) {
                #ifdef DEBUG
                fprintf(stdout, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                if ((ex_address % 4) != 0){
                    fprintf(stderr, "Error: computed address 0x%08X is not word aligned\n", ex_address);
                    exit(1);
                }
                else if ((ex_address > (size * 4)) || ex_address < 0){
                    fprintf(stderr, "Error: computed address 0x%08X is out of program range\n", ex_address);
                    exit(1);
                }
                *pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stdout, "Branch not take\n");
                #endif
                *pc += 4;
            }
            break;
        case 0x4: // <
            #ifdef DEBUG
            fprintf(stdout, "Comparing (signed) 0x%08X (contents of register x%d) < (signed) 0x%08X (contents of register x%d)\n", rs1_signed, rs1, rs2_signed, rs2);
            #endif
            if (rs1_signed < rs2_signed) {
                #ifdef DEBUG
                fprintf(stdout, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                if ((ex_address % 4) != 0){
                    fprintf(stderr, "Error: computed address 0x%08X is not word aligned\n", ex_address);
                    exit(1);
                }
                else if ((ex_address > (size * 4)) || ex_address < 0){
                    fprintf(stderr, "Error: computed address 0x%08X is out of program range\n", ex_address);
                    exit(1);
                }
                *pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stdout, "Branch not take\n");
                #endif
                *pc += 4;
            }
            break;
        case 0x5: // >=
            #ifdef DEBUG
            fprintf(stdout, "Comparing (signed) 0x%08X (contents of register x%d) >= (signed) 0x%08X (contents of register x%d)\n", rs1_signed, rs1, rs2_signed, rs2);
            #endif
            if (rs1_signed >= rs2_signed) {
                #ifdef DEBUG
                fprintf(stdout, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                if ((ex_address % 4) != 0){
                    fprintf(stderr, "Error: computed address 0x%08X is not word aligned\n", ex_address);
                    exit(1);
                }
                else if ((ex_address > (size * 4)) || ex_address < 0){
                    fprintf(stderr, "Error: computed address 0x%08X is out of program range\n", ex_address);
                    exit(1);
                }
                *pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stdout, "Branch not take\n");
                #endif
                *pc += 4;
            }
            break;
        case 0x6: // < unsigned
            #ifdef DEBUG
            fprintf(stdout, "Comparing 0x%08X (contents of register x%d) < 0x%08X (contents of register x%d)\n", reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            if (reg_array[rs1] < reg_array[rs2]) {
                #ifdef DEBUG
                fprintf(stdout, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                if ((ex_address % 4) != 0){
                    fprintf(stderr, "Error: computed address 0x%08X is not word aligned\n", ex_address);
                    exit(1);
                }
                else if ((ex_address > (size * 4)) || ex_address < 0){
                    fprintf(stderr, "Error: computed address 0x%08X is out of program range\n", ex_address);
                    exit(1);
                }
                *pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stdout, "Branch not take\n");
                #endif
                *pc += 4;
            }
            break;
        case 0x7: // >= unsigned
            #ifdef DEBUG
            fprintf(stdout, "Comparing 0x%08X (contents of register x%d) >= 0x%08X (contents of register x%d)\n", reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            if (reg_array[rs1] >= reg_array[rs2]) {
                #ifdef DEBUG
                fprintf(stdout, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                if ((ex_address % 4) != 0){
                    fprintf(stderr, "Error: computed address 0x%08X is not word aligned\n", ex_address);
                    exit(1);
                }
                else if ((ex_address > (size * 4)) || ex_address < 0){
                    fprintf(stderr, "Error: computed address 0x%08X is out of program range\n", ex_address);
                    exit(1);
                }
                *pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stdout, "Branch not take\n");
                #endif
                *pc += 4;
            }
            break;
        default:
            fprintf(stderr, "0x%X is not a valid Branch FUNC3 code\n", func3);
            exit(1);
    }

    return;
}

// Function for functions with Upper-Immediate type
void u_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]){

    uint32_t instruction = mem_array[*pc/4];

    uint8_t opcode = instruction & 0x0000007F;
    uint8_t rd = (instruction >> 7) & 0x0000001F;
    int32_t imm = (instruction & 0xFFFFF000) >> 12;

    #ifdef DEBUG
    fprintf(stdout, "U-Type instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Immediate: 0x%08X\n", opcode, rd, imm);
    #endif

    switch (opcode){
        case LUI_OP:
            reg_array[rd] =  (imm << 12);
            break;
        case AUIPC:
            reg_array[rd] = *pc + (imm << 12);
            break;
        default:
            fprintf(stderr, "Invalid U-type instruction.\n");
            break;
    }
    if(rd == 0 ) reg_array[0] = 0x00000000;

    return;

}

// Function for Jump and Link instruction
void j_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]){

    uint32_t instruction = mem_array[*pc/4];

    uint8_t opcode = instruction & 0x0000007F;
    uint8_t rd = (instruction >> 7) & 0x0000001F;
    int32_t imm = (instruction >> 12);
    uint32_t imm20 = imm & 0x80000;
    uint32_t immlow = (imm & 0x7FE00) >> 9;
    uint32_t imm11 = ((imm >> 8) & 0x00000001) << 10;
    uint32_t immhigh = (imm & 0x000000FF) << 11;
    imm = ((imm20 + immhigh + imm11 + immlow) << 1);

    int immmsb = (imm >> 20) & 0x00000001;
    if (immmsb == 1) imm = imm | 0xFFE00000;
    else imm = imm & ~(0xFFE00000);
    
    uint32_t ex_address = *pc + imm;

    #ifdef DEBUG
    fprintf(stdout, "J-Type instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Immediate: 0x%06X\n", opcode, rd, imm);
    fprintf(stdout, "Storing 0x%08X into register x%d, then adding 0x%05X to PC\n", *pc + 4, rd, imm);
    #endif

    if ((ex_address % 4) != 0){
        fprintf(stderr, "Error: computed address 0x%08X is not word aligned\n", ex_address);
        exit(1);
    }
    else if ((ex_address > (size * 4)) || ex_address < 0){
        fprintf(stderr, "Error: computed address 0x%08X is out of program range\n", ex_address);
        exit(1);
    }
    reg_array[rd] = *pc + 4;
    *pc += imm;

    if(rd == 0 ) reg_array[0] = 0x00000000;
    
    return;
}

// Function for E-Call 
void e_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]){

    switch(reg_array[17]){
        case 63: // Read
            reg_array[10] = _READ(reg_array[10], (void*)(uintptr_t)reg_array[11], reg_array[12]);
            break;
        case 64: // Write
            reg_array[10] = _WRITE(reg_array[10], (void*)(uintptr_t)reg_array[11], reg_array[12]);
        case 94: // Exit
            exit(reg_array[10]);
        default:
            fprintf(stderr, "Invalid or Unknown syscall val %d\n", reg_array[17]);
            exit(-1);
    }
    return;
}


// Function for majority of floating point instructions
void f1_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32], float flt_array[32]){

    uint8_t func7, rs2, rs1, func3, rd, opcode;
    uint32_t instruction = mem_array[*pc / 4];
    int rm;

    opcode = instruction & 0x7F;
    rd = (instruction >> 7 ) & 0x1F;
    func3 = (instruction >> 12) & 0x7;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    func7 = (instruction >> 25) & 0x7F;

    int32_t rs1_signed = reg_array[rs1];
    int32_t rs2_signed = reg_array[rs2];


    if ((func3 != 5) && (func3 != 6) ) rm = func3;
    else rm = -1;

    #ifdef DEBUG
    fprintf(stdout, "F1-Type instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    R_S2: 0x%02X\n    Func7: 0x%02X\n", opcode, rd, func3, rs1, rs2, func7);
    #endif

    switch (func7){

        case 0x00:  //  FADD.S
            flt_array[rd] = flt_round((flt_array[rs1] + flt_array[rs2]), rm);
            break;
        case 0x04:  //  FSUB.S
            flt_array[rd] = flt_round((flt_array[rs1] - flt_array[rs2]), rm);
            break;
        case 0x08:  //  FMUL.S
            flt_array[rd] = flt_round((flt_array[rs1] * flt_array[rs2]), rm);
            break;
        case 0x0C:  //  FDIV.S
            flt_array[rd] = flt_round((flt_array[rs1] / flt_array[rs2]), rm);
            break;
        case 0x10:  //  FSGNJ.S, FSGNJN.S, FSGNJX.S
            switch(func3){
                case 0x0:   //  FSGNJ.S
                    flt_array[rd] = fabsf(flt_array[rs1]) * ((flt_array[rs2] < 0) ? -1 : 1);
                    break;
                case 0x1:   //  FSGNJN.S
                    flt_array[rd] = fabsf(flt_array[rs1]) * -1 * ((flt_array[rs2] < 0) ? -1 : 1);
                    break;
                case 0x2:   //  FSGNJX.S
                    flt_array[rd] = flt_array[rs1] * ((flt_array[rs2] < 0) ? -1 : 1);
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC3 code for FUNC7 code 0x%X\n", func3, func7);
                    exit(1);
            }
            break;
        case 0x14:  //  FMIN.S, FMAX.S
            switch (func3){
                case 0x0:   //  FMIN.S
                    flt_array[rd] = (flt_array[rs1] < flt_array[rs2]) ? flt_array[rs1] : flt_array[rs2];
                    break;
                case 0x1:   //  FMAX.S
                    flt_array[rd] = (flt_array[rs1] > flt_array[rs2]) ? flt_array[rs1] : flt_array[rs2];
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC3 code for FUNC7 code 0x%X\n", func3, func7);
                    exit(1);
            }
            break;
        case 0x2C:  //  FSQRT.S
            flt_array[rd] = flt_round(sqrt(flt_array[rs1]), rm);
            break;
        case 0x50:  //  FEQ.S, FLT.S, FLE.S
            switch (func3){
                case 0x0:   //  FLE.S
                    #ifdef DEBUG
                    fprintf(stdout, "If f-reg %d contents (%f) is less than or equal to f-reg %d contents (%f), set i-reg %d to 1, else 0\n", rs1, flt_array[rs1], rs2, flt_array[rs2], rd);
                    #endif
                    reg_array[rd] = (flt_array[rs1] <= flt_array[rs2]) ? 1 : 0;
                    break;
                case 0x1:   //  FLT.S
                    #ifdef DEBUG
                    fprintf(stdout, "If f-reg %d contents (%f) is less than to f-reg %d contents (%f), set i-reg %d to 1, else 0\n", rs1, flt_array[rs1], rs2, flt_array[rs2], rd);
                    #endif
                    reg_array[rd] = (flt_array[rs1] < flt_array[rs2]) ? 1 : 0;
                    break;
                case 0x2:   //  FEQ.S
                    #ifdef DEBUG
                    fprintf(stdout, "If f-reg %d contents (%f) is equal to f-reg %d contents (%f), set i-reg %d to 1, else 0\n", rs1, flt_array[rs1], rs2, flt_array[rs2], rd);
                    #endif
                    reg_array[rd] = (flt_array[rs1] == flt_array[rs2]) ? 1 : 0;
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC3 code for FUNC7 code 0x%X\n", func3, func7);
                    exit(1);
            }
            break;
        case 0x60:  //  FCVT.W.S, FCVT.WU.S
            switch (rs2){
                case 0x0:   //  FCVT.W.S
                    reg_array[rd] = (int32_t) flt_round(flt_array[rs1], rm);
                    break;
                case 0x1:   //  FCVT.WU.S
                reg_array[rd] = (uint32_t) flt_round(flt_array[rs1], rm);
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid RS2 code for FUNC7 code 0x%X\n", rs2, func7);
                    exit(1);
            }
        case 0x68:  //  FCVT.S.W, FCVT.S.WU
            switch (rs2){
                case 0x0:   //  FCVT.S.W
                    flt_array[rd] = flt_round((float) rs1_signed, rm);
                    break;
                case 0x1:   //  FCVT.S.WU
                    flt_array[rd] = flt_round((float) reg_array[rs1], rm);
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid RS2 code for FUNC7 code 0x%X\n", rs2, func7);
                    exit(1);
            }
            break;
        case 0x70:  //  FMV.X.W, FCLASS.S
            switch (func3){
                case 0x0:   //  FMV.X.W
                    reg_array[rd] = *((int*) &flt_array[rs1]);
                    break;
                case 0x1:   //  FCLASS.S
                    fclass_s(flt_array[rs1], &reg_array[rd]);
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid FUNC3 code for FUNC7 code 0x%X\n", func3, func7);
                    exit(1);
            }
            break;
        case 0x78:  //  FMV.W.X
            flt_array[rd] = *((float*) &reg_array[rs1]);
            break;

        default:
            fprintf(stderr, "Invalid FP-type instruction.\n");
            exit(1);
    }
    *pc += 4;
    reg_array[0] = 0x00000000;
    return;
}

// Function to round float values as needed
float flt_round(float value, int rm){
    switch (rm) {
        case 0b000: // RNE: Round to Nearest, ties to Even
            return round(value);
        case 0b001: // RTZ: Round towards Zero
            return trunc(value);
        case 0b010: // RDN: Round Down (towards -∞)
            return floor(value);
        case 0b011: // RUP: Round Up (towards +∞)
            return ceil(value);
        case 0b100: // RMM: Round to Nearest, ties to Max Magnitude
            return (value > 0) ? ceil(value) : floor(value);
        case 0b111: // DYN: Dynamic mode (not implemented, placeholder)
            return value;
        default: // Reserved values (101, 110) or invalid input
            fprintf(stderr, "Error: Unsupported rounding mode: %d\n", rm);
            return value;
    }
}

// Function for Float Load and Store
void f2_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32], float flt_array[32]){

    uint8_t func7, rs2, rs1, func3, rd, opcode;
    uint32_t instruction = mem_array[*pc / 4], uint_val;
    float flt_val;

    opcode = instruction & 0x7F;
    rd = (instruction >> 7 ) & 0x1F;
    func3 = (instruction >> 12) & 0x7;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    func7 = (instruction >> 25) & 0x7F;

    #ifdef DEBUG
    fprintf(stdout, "F-Type 2 instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    R_S2: 0x%02X\n    Func7: 0x%02X\n", opcode, rd, func3, rs1, rs2, func7);
    #endif

    switch (opcode){
        case FLW:
            uint_val = readWord(mem_array, size, (reg_array[rs1] + ((func7 << 5 | rs2) )));
            flt_array[rd] = *((float*) &uint_val);
            break;
        case FSW:
            uint_val = *((int*) &flt_array[rs2]);
            writeWord(mem_array, size, (reg_array[rs1] + (func7 << 5 | rd) ), uint_val );
            break;
        default:
            fprintf(stderr, "Invalid FP2-type instruction.\n");
            exit(1);
    }

    *pc += 4;
    reg_array[0] = 0x00000000;
    return;
}

// Function for Float Mult and Float Neg Mult instructions
void f3_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32], float flt_array[32]){


    uint8_t rs3, rs2, rs1, rm, rd, opcode;
    uint32_t instruction = mem_array[*pc / 4];

    opcode = instruction & 0x7F;
    rd = (instruction >> 7 ) & 0x1F;
    rm = (instruction >> 12) & 0x7;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    rs3 = (instruction >> 27) & 0x1F;


    switch (opcode){
        case FMADDS:
            flt_array[rd] = flt_round( flt_array[rs1] * flt_array[rs2] + flt_array[rs3], rm );
            break;
        case FMSUBS:
            flt_array[rd] = flt_round( flt_array[rs1] * flt_array[rs2] - flt_array[rs3], rm );
            break;
        case FNMSUBS:
            flt_array[rd] = flt_round( -1 * flt_array[rs1] * flt_array[rs2] - flt_array[rs3], rm );
            break;
        case FNMADDS:
            flt_array[rd] = flt_round( -1 * flt_array[rs1] * flt_array[rs2] + flt_array[rs3], rm );
            break;
        default:
            fprintf(stderr, "Invalid FP3-type instruction.\n");
            exit(1);
    }
    *pc += 4;
    return;
}

// Function to print out each Float register val (with easy to read val in debug mode)
void printAllFPReg(float regs[32]){

    uint32_t ui;

    for (int i = 0; i < 32; i++){
        memcpy(&ui, &regs[i], sizeof(ui));
        printf("Register: f%02d  Contents: ", i);
        printf("%08X", ui);
        #ifdef DEBUG
        printf(" (%f)", regs[i]);
        #endif
        printf("\n");
    }

    printf("\n");
    fflush(stdout);
    return;
}

// Function to take breakpoint inputs
int breakpointInput(int array[]){
    int numBreaks;
    printf("\nEnter the amount of breakpoints you wish to add in the code (1-20): ");
    fflush(stdout);
    if (scanf("%d", &numBreaks) != 1 || numBreaks < 0 || numBreaks > 20) {
        fprintf(stderr, "\nUnsupported number of breakpoints\n");
        while(getchar() != '\n');
        return 0;
    } 

    else {
        for(int i = 0; i < numBreaks; i++){
            printf("\nEnter the value of the PC where you wish to break (%d): 0x", i+1);
            fflush(stdout);
            if (scanf("%x", &array[i]) != 1 || array[i] < 0 || (array[i] % 4) != 0) {
                fprintf(stderr, "Invalid PC value (must be aligned to 4 bytes)\n");
                i--;
                while(getchar() != '\n');
            }   
        }
    printf("\n");
    while(getchar() != '\n');
    return numBreaks;
    }
}

// Function to check if current mem location is / is not within the breakpoint array
int breakpointCheck(int bppc[], int numBPs, uint32_t instruction, uint32_t array[], int size, uint32_t regs[32], char regnames[32][8], float fregs[32], int MemWords, int step){
    for(int i = 0; i < numBPs; i++){
        if (instruction == bppc[i]){
            printf("Breakpoint at PC: 0x%05x\n\n", bppc[i]);
            step = singleStep(instruction, array, size, regs, regnames, fregs, MemWords, step);
        }
    }
    return step;
}

// Function to set up and initialize watch locations within memory and registers
void watchingUserInput(uint32_t regindex[], uint32_t fregindex[], uint32_t memindex[], int *numRegs, int *numFregs, int *numMems){
    char input = '\0';  
    int numIntRegs = 0;
    int numFloatRegs = 0;
    int numMemLocals = 0;
    char regCommand;

    // Continue loop until given exit command
    while (input != 'C'){

        fprintf(stdout,"\nTo watch a memory location enter: [M]\nTo watch a register enter: [R]\nTo continue enter: [C]\n\n");
        fflush(stdout);   
        scanf(" %c", &input);
        switch (input){

            // Set Integer register watch point
            case 'R':
            case 'r':
                
                fprintf(stdout, "To watch an integer register enter: [X]\nTo watch a floating point register enter: [F]\n\n");
                fflush(stdout);   
                scanf(" %c", &regCommand);
                if (regCommand == 'X' || regCommand == 'x') {
                    fprintf(stdout, "\nEnter the amount of integer registers you wish to watch: ");
                    fflush(stdout);   
                    if (scanf("%d", &numIntRegs) != 1 || numIntRegs < 0 || numIntRegs > 31) fprintf(stderr, "\nInvalid register amount\n");
                    else{
                        for (int i = 0; i < numIntRegs; i++){
                            fprintf(stdout, "\nEnter the integer register you wish to watch: x");
                            fflush(stdout);   
                            if (scanf("%d", &regindex[i]) != 1 || regindex[i] < 0 || regindex[i] > 31) {
                                fprintf(stderr, "Invalid Register Number\n");
                                i--;
                                while (getchar() != '\n');
                            }
                        }
                    }
                }

                // Set Float register watch point
                else if (regCommand == 'F' || regCommand == 'f')
                {
                    fprintf(stdout, "\nEnter the amount of floating point registers you wish to watch: ");
                    fflush(stdout);
                    if (scanf("%d", &numFloatRegs) != 1 || numFloatRegs < 0 || numFloatRegs > 31) fprintf(stderr, "\nInvalid register amount\n");
                    
                    else
                    {
                        for (int i = 0; i < numFloatRegs; i++)
                        {
                            fprintf(stdout, "\nEnter the floating point register you wish to watch: f");
                            fflush(stdout);
                            if (scanf("%d", &fregindex[i]) != 1 || fregindex[i] < 0 || fregindex[i] > 31)
                            {
                                fprintf(stderr, "Invalid Register Number\n");
                                i--;
                                while (getchar() != '\n');
                            }
                        }
                    }
                }
                else fprintf(stderr, "Invalid register command, please try again\n");
                break;

            // Set memory watch point
            case 'M':
            case 'm':
                printf("\nEnter the amount of memory locations you wish to watch (1-100): ");
                fflush(stdout);   
                if (scanf("%d", &numMemLocals) != 1 || numMemLocals < 0 || numMemLocals > 100) fprintf(stderr, "\nInvalid amount\n"); 
                else {
                    for (int i = 0; i < numMemLocals; i++) {
                        printf("Enter the desired memory address (Hexadecimal): 0x");
                        fflush(stdout);   
                        if (scanf("%x", &memindex[i]) != 1 || memindex[i] < 0 || memindex[i] > 0xFFFF) {
                            fprintf(stderr, "\nInvalid memory address\n\n");
                            i--;
                            while (getchar() != '\n');
                        }
                    }
                }
                break;
            
            // Exit setup and start watching
            case 'C':
            case 'c':
                while (getchar() != '\n');
                #ifdef DEBUG
                for (int i = 0; i < 32; i++)
                {
                    printf("numIntReg %d:   %d\n", i, regindex[i]);
                    printf("numFloatReg %d: %d\n", i, fregindex[i]);
                }
                for (int i = 0; i < 100; i++) printf("numMemLocals %d: %d\n", i, memindex[i]);
                
                printf("numInt: %d\nnumFloat: %d\nnumMem: %d\n", numIntRegs, numFloatRegs, numMemLocals);
                #endif
                *numRegs = numIntRegs;
                *numFregs = numFloatRegs;
                *numMems = numMemLocals;
                return;
                break;

            default:
                fprintf(stderr, "Invalid command, please try again\n");
        }
        while (getchar() != '\n');
    }
}

// Function to print actively watched locations and registers
void watchingOutput(int numIntRegs, int numFloatRegs, int numMemLocals, uint32_t watchedRegs[], uint32_t watchedFregs[], uint32_t watchedMem[], uint32_t reg[32], char names[32][8], float freg[32], uint32_t mem[32]){
    
    uint32_t ui;

    // Integer Registers
    if(numIntRegs > 0 ){
        printf("\n\nWatched Integer Registers:\n");
        for(int i = 0; i < numIntRegs; i++){
            if(watchedRegs[i] != -1){
                int registernumber = watchedRegs[i];
                printf("Register x%d %s: 0x%08x\n", registernumber, names[registernumber], reg[registernumber]);
            }
        }
    }

    // Float Registers
    if (numFloatRegs > 0){
        printf("\n\nWatched Floating point Registers:\n");
        for(int i = 0; i < numFloatRegs; i++){
            if(watchedFregs[i] != -1){
                memcpy(&ui, &freg[watchedFregs[i]], sizeof(ui));
                printf("Floating Point Register f%d: 0x%08x\n", watchedFregs[i], ui);
            }
        }
    }

    // Memory Locations
    if (numMemLocals > 0){
        printf("\nWatched Memory Locations:\n");
        for(int i = 0; i < numMemLocals; i++){
            if(watchedMem[i] != -1){
                int memoryaddress = watchedMem[i];
                printf("Memory Location 0x%05x: 0x%08x\n", memoryaddress, mem[memoryaddress/4]);
            }
        }
    }

    return;
}

// Function to set up stepping through the current mem file
int singleStep(uint32_t instruction, uint32_t array[], int size, uint32_t regs[32], char regnames[32][8], float fregs[32], int MemWords, int step) {

    char input = '\0';  // Initialize input variable
    
    while(input != 'C') {
        printf("To display current instruction enter: [I]\nTo print register contents enter: [R]\nTo print memory contents enter: [M]\nTo continue enter: [C]\nTo exit single step mode enter : [D]\n");
        fflush(stdout);
        scanf(" %c", &input);
    
        switch(input) {
            // Register Contents
            case 'R': 
            case 'r': {
                char regCommand;
                printf("To display all integer registers enter: [R]\nTo display all floating point registers enter: [F]\nTo display a specific integer register enter: [X]\nTo display a specific floating point register enter: [P]\n\n");
                fflush(stdout);
                scanf(" %c", &regCommand);
    
                if (regCommand == 'R' || regCommand == 'r') {
                    printf("\n");
                    printAllReg(regs, regnames);
                } 
                else if (regCommand == 'F' || regCommand == 'f') {
                    printf("\n");
                    printAllFPReg(fregs);
                } 
                else if (regCommand == 'X' || regCommand == 'x') {
                    int regNumInt;
                    printf("Enter the integer register number (0-31): ");
                    fflush(stdout);
                    if (scanf("%d", &regNumInt) != 1 || regNumInt < 0 || regNumInt > 31) fprintf(stderr, "Invalid register number\n");
                    else printf("x%d %s: 0x%08x\n\n", regNumInt, regnames[regNumInt], regs[regNumInt]);
                } 
                else if (regCommand == 'P' || regCommand == 'p') {
                    int fregNumInt;
                    printf("Enter the floating-point register number (0-31): ");
                    fflush(stdout);
                    if (scanf("%d", &fregNumInt) != 1 || fregNumInt < 0 || fregNumInt > 31) fprintf(stderr, "Invalid register number\n");
                    else printf("f%d: 0x%08x\n\n", fregNumInt, fregs[fregNumInt]);
                }
                else fprintf(stderr, "Invalid register command, please try again\n");
                break;
            }

            // Memory Contents
            case 'M':
            case 'm': {
                char memCommand;
                printf("To display all nonzero memory locations enter: [M]\nTo display a specific memory address enter: [A]\n\n");
                fflush(stdout);
                scanf(" %c", &memCommand);
                if (memCommand == 'M' || memCommand == 'm') {
                    printf("\n");
                    printAllMem(array, MemWords);
                    printf("\n");
                } 
                else if (memCommand == 'A' || memCommand == 'a') {
                    printf("\n");
                    int memAddress;
                    printf("Enter the desired memory address (Hexadecimal): 0x");
                    fflush(stdout);
                    if (scanf("%x", &memAddress) != 1 || memAddress < 0 || memAddress > 0xFFFF) fprintf(stderr, "\nInvalid register number\n\n");
                    else printf("\nAddress 0x%05x: 0x%08x\n\n", memAddress, array[memAddress / 4]);    
                } 
                else fprintf(stderr, "Invalid memory command, please try again\n");
                    
                break;
            }
            // Current instruction
            case 'I':
            case 'i':
                printf("Current Instruction: 0x%08x\n\n", array[instruction/4]);
                break;
    
            // Step
            case 'C':
            case 'c':
                while(getchar() != '\n');
                step = 1;
                return step;  // Exit the loop when 'C' is entered
                break;
            
            // Exit step mode and return
            case 'D':
            case 'd':
                step = 0;
                while(getchar() != '\n');
                return step;  // Exit the loop when 'C' is entered
                break;
            default:
                fprintf(stderr, "Invalid command, please try again\n");
        }
    
        // Clear the newline left by scanf
        while(getchar() != '\n');
    }
}

void fclass_s(float value, uint32_t *out) {
    uint32_t bits;
    uint32_t result = 0;

    // Convert float to bit values
    bits = *(uint32_t *)&value;

    // Extract sign, exponent, and mantissa
    uint32_t sign = (bits >> 31) & 1;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t mantissa = bits & 0x7FFFFF;

    if (exponent == 0xFF) { // NaN or Infinity
        if (mantissa == 0) { // Infinity
            result = (sign == 1) ? (1 << 0) : (1 << 7); // -Inf or +Inf
        } else { // NaN
            result = (mantissa & (1 << 22)) ? (1 << 9) : (1 << 8); // Signaling or Quiet NaN
        }
    } else if (exponent == 0) { // Zero or Subnormal
        if (mantissa == 0) {
            result = (sign == 1) ? (1 << 3) : (1 << 4); // -Zero or +Zero
        } else {
            result = (sign == 1) ? (1 << 2) : (1 << 5); // -Subnormal or +Subnormal
        }
    } else { // Normal numbers
        result = (sign == 1) ? (1 << 1) : (1 << 6); // -Normal or +Normal
    }

    *out = result;
    return;
}


