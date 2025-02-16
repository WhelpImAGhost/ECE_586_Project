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

// Debug function to print memory info
void printAllMem(uint32_t array[], int size);
void printAllReg(uint32_t regs[32], char regnames[32][8]);

// Function Prototypes
uint32_t readByte(uint32_t array[], int size, int address);
uint32_t readHalfWord(uint32_t array[], int size, int address);
uint32_t readWord(uint32_t array[], int size, int address);
int writeByte(uint32_t array[], int size, int address, uint32_t value);
int writeHalfWord(uint32_t array[], int size, int address, uint32_t value);
int writeWord(uint32_t array[], int size, int address, uint32_t value);

void fetch_and_decode(uint32_t array[], uint32_t pc, uint32_t* opcode);

//Addressing Mode Function Prototypes
void r_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void i_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void s_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void b_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void u_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);
void j_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]);

//Instruction Function Protoytpes
void load(uint8_t function, uint8_t destination, uint8_t source, int32_t immediate, uint32_t array[], int size, uint32_t reg_array[32]);
void immediateop(uint8_t function, uint8_t destination, uint8_t source, int32_t immediate, uint32_t array[], int size, uint32_t reg_array[32]);

int main(int argc, char *argv[]){

    uint32_t test_word;
    char test_str[10];

    // Local variables for function use
    uint32_t address, instruction, pc = 0;
    uint32_t current_opcode;
    bool continue_program = true;

    // Opcode array
    uint32_t opcodes[10] = {REGS_OP, IMMS_OP,LOAD_OP, STOR_OP, BRAN_OP, 
                            JAL_OP, JALR_OP, LUI_OP, AUIPC, ENVIRO };

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

    // Set default mode
    int mode = 0;

    // Memory & Stack Starting Addresses
    uint32_t stack_address = STACK_ADDRESS, prog_start = START_ADDRESS;

    // Set default filename
    char *default_filename = "Mem_files/prog.mem";
    char *filename = default_filename;

    // Flags for setting non-default variable values
    for( argc--, argv++; argc > 0; argc-=2, argv+=2 ) {
        if (strcmp(argv[0], "-f" ) == 0 ) {
            filename = argv[1]; // Set input file
        }
        else if (strcmp(argv[0], "-m" ) == 0 ) {
            mode = atoi(argv[1]); // Set operation mode
        }
        else if (strcmp(argv[0], "-sp")) {
            stack_address = (uint32_t)atoi(argv[1]);  // Set stack pointer
        }
        else if (strcmp(argv[0], "-s")){
            prog_start = (uint32_t) atoi(argv[1]); // Set starting address
        }
        else { 
            printf("\nInvalid Arguments\n"); exit(-1); 
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
        perror("Error opening file");
        // Exit the program if file opening fails
        return -1;
    }

    // File used for execution
    #ifdef DEBUG
    fprintf(stderr, "Using file: '%s'\n", filename);
    #endif

    // Allocating Memory Size (64KB by default)
    const int MemAlloc = pow(2, MEMORY_SIZE);

    // Load instructions into memory array
    while (fscanf(file, "%x: %x", &address, &instruction ) == 2){

        // Error whem memory address is outside the bounds of memory size declared
        if (address >= MemAlloc){
            fprintf(stderr, "Address 0x%08X is out of memory bounds\n", address);
        }

        // Size of instruction
        MainMem[address / 4] = instruction;

        // Body for parsing lines
        #ifdef DEBUG
        fprintf(stderr, "Extracted memory addresss:      0x%08X\n", address);
        fprintf(stderr, "Extracted instruction contents: 0x%08X\n", instruction);
        #endif

    }

    x[2] = stack_address;

    // Begin fetching and decoding instructions
    while(continue_program){
        fetch_and_decode(MainMem, pc, &current_opcode);

        

        switch (current_opcode) {
            case REGS_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is a Register Instruction\n", current_opcode);
                #endif
                r_type(MainMem, MemWords, &pc, x);
                pc += 4;
                break;
            case IMMS_OP:
            case LOAD_OP:
            case JALR_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is an Immediate Instruction\n", current_opcode);
                #endif
                i_type(MainMem, MemWords, &pc, x);
                if (pc == 0x0) {
                    fprintf(stderr, "End of Program\n");
                    continue_program = false;
                }
                break;
            case STOR_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is a Store Instruction\n", current_opcode);
                #endif
                s_type(MainMem, MemWords, &pc, x);
                pc += 4;
                break;
            case BRAN_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is a Branch Instruction\n", current_opcode);
                #endif
                b_type(MainMem, MemWords, &pc, x);
                break;
            case JAL_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is a Jump Instruction\n", current_opcode);
                #endif
                
                j_type(MainMem,MemWords, &pc, x);
                if (pc == 0x0) {
                    fprintf(stderr, "End of Program\n");
                    continue_program = false;
                }
                break;
            case LUI_OP:
            case AUIPC:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is an 'Upper Immediate' Instruction\n", current_opcode);
                #endif
                u_type(MainMem, MemWords, &pc, x);
                pc += 4;
                break;
            case ZERO_OP:
                fprintf(stderr, "End of Program\n");
                continue_program = false;
                break;
            case ENVIRO:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is an Environment Instruction\n", current_opcode);
                fprintf(stderr, "Not implemented yet\n");
                #endif
            default:
                fprintf(stderr, "0x%02X is an invalid op code.\n", current_opcode);
                exit(1);
        }
        // For development purposes only
        

    }
    //printAllReg(x);
    printAllMem(MainMem, MemWords);
    printAllReg(x, regnames);
    return 0;

}

// Memory dump function for debugging (using a log file)
void printAllMem(uint32_t array[], int size){
#ifdef DEBUG
fprintf(stderr,"\n");
for (int i = 0; i < size; i++){
    if (array[i] != 0x0) printf( "Array Member: %4d     Memory Address: 0x%08X     Contents: 0x%08X\n", i, 4*i, array[i]);
}
#endif
    return;
}

// Function to display all register values
void printAllReg(uint32_t regs[32], char regnames[32][8] ){

    for (int i = 0; i < 32; i++){
        printf("Register: x%02d %-6sContents: ", i, regnames[i]);
        printf("%08X\n", regs[i]);

    }
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
        fprintf(stderr, "Misaligned reference at 0x%08d\n", address);
        exit(1);
    }
    else{
    int target_block = address / 4;
    int target_hw;
    
    if (address % 4 == 2) {
        target_hw = 2;
    } else {
        target_hw = 0;
    }

    uint32_t selected_word = array[target_block];
    selected_word = selected_word >> (8 * target_hw);
    uint32_t selected_hw = selected_word & 0x0000FFFF;

    return selected_hw;
    }

}

// Function to read a specific word from memory
uint32_t readWord(uint32_t array[], int size, int address){

    int target_block = address / 4;
    uint32_t selected_word = array[target_block];

    return selected_word;

}

// Function to write to a specific byte from memory
int writeByte(uint32_t array[], int size, int address, uint32_t value) {

    int target_block = address / 4;
    int target_byte = address % 4;

    array[target_block] = (array[target_block] & ~(0xFF << (8 * target_byte)));
    array[target_block] = array[target_block] | (value << (8 * target_byte));

    return 0;

}

// Function to write to a specific half-word in memory
int writeHalfWord(uint32_t array[], int size, int address, uint32_t value) {

    if (address % 2 != 0) {
        fprintf(stderr, "Misaligned reference at 0x%08d\n", address);
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
        
    } else {
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

    int target_block = address / 4;
    array[target_block] = value;

    return 0;

}

void fetch_and_decode(uint32_t array[], uint32_t pc, uint32_t *opcode){

    uint32_t selected_instruction = array[pc / 4];

    *opcode = selected_instruction & 0x0000007F;

    return;
}

void r_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]){

    uint8_t func7, rs2, rs1, func3, rd, opcode;
    uint32_t instruction = mem_array[*pc / 4];

    opcode = instruction & 0x7F;
    rd = (instruction >> 7 ) & 0x1F;
    func3 = (instruction >> 12) & 0x7;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    func7 = (instruction >> 25) & 0x7F;

    int32_t rs1_signed = reg_array[rs1];
    int32_t rs2_signed = reg_array[rs2];

    #ifdef DEBUG
    fprintf(stderr, "R-Type instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    R_S2: 0x%02X\n    Func7: 0x%02X\n", opcode, rd, func3, rs1, rs2, func7);
    #endif

    switch(func3){

        case 0x0: // add and sub
            switch(func7){
                case 0x00: // add
                    #ifdef DEBUG
                    fprintf(stderr, "Adding 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd] = reg_array[rs1] + reg_array[rs2];
                    break;
                case 0x20: // sub
                    #ifdef DEBUG
                    fprintf(stderr, "Subtracting 0x%08X (the contents of register x%d) from 0x%08X (the contents of register x%d) and placing the result in register x%d \n",   reg_array[rs2], rs2, reg_array[rs1], rs1, rd);
                    #endif
                    reg_array[rd] = reg_array[rs1] - reg_array[rs2];
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid Add/Sub FUNC7 code\n", func7);
                    exit(1);
            }
            break;
        case 0x4: // xor
            #ifdef DEBUG
            fprintf(stderr, "XOR 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
            #endif
            reg_array[rd] = reg_array[rs1] ^ reg_array[rs2];
            break;
        case 0x6: // or
            #ifdef DEBUG
            fprintf(stderr, "OR 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
            #endif
            reg_array[rd] = reg_array[rs1] | reg_array[rs2];
            break;
        case 0x7: // and
            #ifdef DEBUG
            fprintf(stderr, "AND 0x%08X (the contents of register x%d) and 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
            #endif
            reg_array[rd] = reg_array[rs1] & reg_array[rs2];
            break;
        case 0x1: // Shift Left Logical
            #ifdef DEBUG
            fprintf(stderr, "Shift Left 0x%08X (the contents of register x%d) by 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
            #endif
            reg_array[rd] = reg_array[rs1] << (reg_array[rs2] & 0x1F);
            break;
        case 0x5: // Shift Right
            switch (func7){
                case 0x00: // Shift Right Logical
                    #ifdef DEBUG
                    fprintf(stderr, "Shift Right (Logical) 0x%08X (the contents of register x%d) by 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd] = reg_array[rs1] >> (reg_array[rs2] & 0x1F);
                    break;
                case 0x20: // Shift Right Arithmetic
                    #ifdef DEBUG
                    fprintf(stderr, "Shift Right (Arithmetic) 0x%08X (the contents of register x%d) by 0x%08X (the contents of register x%d) and placing the result in register x%d \n",  reg_array[rs1], rs1, reg_array[rs2], rs2, rd);
                    #endif
                    reg_array[rd] = rs1_signed >> (reg_array[rs2] & 0x1F);
                    break;
                default:
                    fprintf(stderr, "0x%X is not a valid Shift Right FUNC7 code\n", func7);
                    exit(1);
            }
            break;
        case 0x2: // Set Less Than
            #ifdef DEBUG
            fprintf(stderr, "Set register x%d to 1 if 0x%08X (the contents of x%d) is less than 0x%08X (the contents of x%d), otherwise set it to 0\n",rd, reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            reg_array[rd] = (rs1_signed < rs2_signed) ? 1 : 0;
            break;
        case 0x3: // Set Less Than Unsigned
            #ifdef DEBUG
            fprintf(stderr, "(UNSIGNED) Set register x%d to 1 if 0x%08X (the contents of x%d) is less than 0x%08X (the contents of x%d), otherwise set it to 0\n",rd, reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            reg_array[rd] = (reg_array[rs1] < reg_array[rs2]) ? 1 : 0;
            break;
        default:
        fprintf(stderr, "0x%X is not a valid Register FUNC3 code\n", func3);
        exit(1);
    }

    return;
}

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

    #ifdef DEBUG
    fprintf(stderr, "I-Type instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    Immediate: 0x%03X\n", opcode, rd, func3, rs1, imm);
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
            reg_array[rd] = *pc + 4;
            *pc = reg_array[rs1] + imm;
            break;
        default:
            fprintf(stderr, "0x%02X is not a valid I-type opcode.\n", opcode);
            exit(1);
    }

    return;
}
void immediateop(uint8_t function, uint8_t destination, uint8_t source, int32_t immediate, uint32_t array[], int size, uint32_t reg_array[32]){
    uint8_t func7 = (immediate >> 5) & 0x7F; 
    uint8_t shamt = immediate & 0x1F;
    int32_t signedsource = reg_array[source];
    switch (function)
    {
    case 0x0: //addi
        #ifdef DEBUG
        fprintf(stderr, "Adding 0x%08X (the contents of register x%d) and 0x%08X and placing the result in register x%d \n", reg_array[source], source, immediate, destination);
        #endif
        reg_array[destination] = signedsource + immediate;
        break;
    case 0x4: //xori
        #ifdef DEBUG
        fprintf(stderr, "Bitwise XORing 0x%08X (the contents of register x%d) and 0x%08X and placing the result in register x%d\n", reg_array[source], source, immediate, destination);
        #endif
        reg_array[destination] = signedsource ^ immediate;
        break;
    case 0x6: //ori
        #ifdef DEBUG
        fprintf(stderr, "Bitwise ORing 0x%08X (the contents of register x%d) and 0x%08X and placing the result in register x%d\n", reg_array[source], source, immediate, destination);
        #endif  
        reg_array[destination] = signedsource | immediate;      
        break;
    case 0x7: //andi
        #ifdef DEBUG
        fprintf(stderr, "Bitwise ANDing 0x%08X (the contents of register x%d) and 0x%08X and placing the result in register x%d\n", reg_array[source], source, immediate, destination);
        #endif
        reg_array[destination] = signedsource & immediate;
        break;
    case 0x1: //slli
        #ifdef DEBUG
        fprintf(stderr, "Logical Shifting 0x%08X Left (the contents of register x%d) by %d and placing the result in register x%d\n", reg_array[source], source, shamt, destination);
        #endif
        reg_array[destination] = reg_array[source] << shamt;
        break;
    case 0x5:
        switch (func7)
        {
        case 0x00: //srli
            #ifdef DEBUG
            fprintf(stderr, "Logical Shifting 0x%08X Right (the contents of register x%d) by %d and placing the result at 0x%08X (register x%d)\n", reg_array[source], source, shamt, reg_array[destination], destination);
            #endif
            reg_array[destination] = reg_array[source] >> shamt;
            break;
        case 0x20: //srai
            #ifdef DEBUG
            fprintf(stderr, "Arithmetic Shifting 0x%08X Right (the contents of register x%d) by %d and placing the result at 0x%08X (register x%d)\n", reg_array[source], source, shamt, reg_array[destination], destination);
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
        fprintf(stderr, "Set register x%d to 1 if 0x%08X (the contents of x%d) is less than 0x%08X, otherwise set it to 0\n",rd, reg_array[destination], destination, immediate);
        #endif
        reg_array[destination] = (signedsource < immediate) ? 1 : 0;
        break; 
    case 0x3: // Set Less Than Unsigned
        #ifdef DEBUG
        fprintf(stderr, "Set register x%d to 1 if 0x%08X (the contents of x%d) is less than 0x%08X, otherwise set it to 0\n",rd, reg_array[destination], destination, immediate);
        #endif    
        uint32_t unsignedimmediate = immediate;
        reg_array[destination] = (reg_array[source] < unsignedimmediate) ? 1 : 0;
        break;   
    default:
        fprintf(stderr,"The provided immediate instruction is invalid.\n");
        exit(1);
    }
}

void load(uint8_t function, uint8_t destination, uint8_t source, int32_t immediate, uint32_t array[], int size, uint32_t reg_array[32]){
    uint32_t StoredWord;
    int sign;
    switch (function){
        case 0x0: //lb
            StoredWord = readByte(array, size, (reg_array[source] + immediate));
            sign = (StoredWord >> 7) & 0x00000001;
            if (sign == 1){
                StoredWord = StoredWord | 0xFFFFFF00;
            }else{
                StoredWord = StoredWord & ~(0xFFFFFF00);
            }
            #ifdef DEBUG
            fprintf(stderr, "Loading 0x%08X from memory location 0x%08X to register x%d\n", StoredWord, reg_array[source] + immediate, destination);
            #endif
            reg_array[destination] = StoredWord;
            break;
        case 0x1: //lh
            StoredWord = readHalfWord(array, size, (reg_array[source] + immediate));
            sign = (StoredWord >> 15) & 0x00000001;
            if (sign == 1){
                StoredWord = StoredWord | 0xFFFF0000;
            }else{
                StoredWord = StoredWord & ~(0xFFFF0000);
            }
            #ifdef DEBUG
            fprintf(stderr, "Loading 0x%08X from memory location 0x%08X to register x%d\n", StoredWord, reg_array[source] + immediate, destination);
            #endif
            reg_array[destination] = StoredWord;
            break;
        case 0x2: //lw
            #ifdef DEBUG
            fprintf(stderr, "Loading 0x%08X from memory location 0x%08X to register x%d\n", readWord(array, size, (reg_array[source] + immediate)), reg_array[source] + immediate, destination);
            #endif
            reg_array[destination] = readWord(array, size, (reg_array[source] + immediate));
            break;
        case 0x4: //lbu
            StoredWord = readByte(array, size, (reg_array[source] + immediate));
            #ifdef DEBUG
            fprintf(stderr, "Loading 0x%08X from memory location 0x%08X to register x%d\n", StoredWord, reg_array[source] + immediate, destination);
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
            printf("The provided load instruction is invalid.\n");
           return exit(1);
    }
    return;
};

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
    if (immmsb == 1){
        imm = imm | 0xFFFFF000;
    }else{
        imm = imm & ~(0xFFFFF000);
    }

    #ifdef DEBUG
    fprintf(stderr, "S-Type instruction breakdown:\n    Opcode: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    R_S2: 0x%02X\n    Immediate: 0x%04X\n", opcode, func3, rs1, rs2, imm);
    #endif

    // Run different stores depending on func3 value;
    switch(func3){
        case 0x0:
            #ifdef DEBUG
            fprintf(stderr, "Storing 0x%02X @ 0x%08X\n", reg_array[rs2], reg_array[rs1] + imm);
            #endif
            writeByte(mem_array, size, reg_array[rs1] + imm, reg_array[rs2]);
            break;
        case 0x1:
            #ifdef DEBUG
            fprintf(stderr, "Storing 0x%04X @ 0x%08X\n", reg_array[rs2], reg_array[rs1] + imm);
            #endif
            writeHalfWord(mem_array, size, reg_array[rs1] + imm, reg_array[rs2]);
            break;
        case 0x2:
            #ifdef DEBUG
            fprintf(stderr, "Storing 0x%08X @ 0x%08X\n", reg_array[rs2], reg_array[rs1] + imm);
            #endif
            writeWord(mem_array, size, reg_array[rs1] + imm, reg_array[rs2]);
            break;
        default:
            fprintf(stderr, "0x%02X is not a valid S-type Function3 value.\n", func3);
            exit(1);
    }

    return;
}

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
    if (immmsb == 1){
        imm = imm | 0xFFFFE000;
    }else{
        imm = imm & ~(0xFFFFE000);
    }

    int32_t rs1_signed = reg_array[rs1];
    int32_t rs2_signed = reg_array[rs2];

    #ifdef DEBUG
    fprintf(stderr, "B-Type instruction breakdown:\n    Opcode: 0x%02X\n    Func3: 0x%02X\n    R_S1: 0x%02X\n    R_S2: 0x%02X\n    Immediate: 0x%04X\n", opcode, func3, rs1, rs2, imm);
    #endif


    switch (func3){

        case 0x0: // ==
            #ifdef DEBUG
            fprintf(stderr, "Comparing 0x%08X (contents of register x%d) == 0x%08X (contents of register x%d)\n", reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            if (reg_array[rs1] == reg_array[rs2]){ 
                #ifdef DEBUG
                fprintf(stderr, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stderr, "Branch not take\n");
                #endif
            }
            break;
        case 0x1: // !=
            #ifdef DEBUG
            fprintf(stderr, "Comparing 0x%08X (contents of register x%d) != 0x%08X (contents of register x%d)\n", reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            if (reg_array[rs1] != reg_array[rs2]) {
                #ifdef DEBUG
                fprintf(stderr, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stderr, "Branch not take\n");
                #endif
            }
            break;
        case 0x4: // <
            #ifdef DEBUG
            fprintf(stderr, "Comparing (signed) 0x%08X (contents of register x%d) < (signed) 0x%08X (contents of register x%d)\n", rs1_signed, rs1, rs2_signed, rs2);
            #endif
            if (rs1_signed < rs2_signed) {
                #ifdef DEBUG
                fprintf(stderr, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stderr, "Branch not take\n");
                #endif
            }
            break;
        case 0x5: // >=
            #ifdef DEBUG
            fprintf(stderr, "Comparing (signed) 0x%08X (contents of register x%d) >= (signed) 0x%08X (contents of register x%d)\n", rs1_signed, rs1, rs2_signed, rs2);
            #endif
            if (rs1_signed >= rs2_signed) {
                #ifdef DEBUG
                fprintf(stderr, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stderr, "Branch not take\n");
                #endif
            }
            break;
        case 0x6: // < unsigned
            #ifdef DEBUG
            fprintf(stderr, "Comparing 0x%08X (contents of register x%d) < 0x%08X (contents of register x%d)\n", reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            if (reg_array[rs1] < reg_array[rs2]) {
                #ifdef DEBUG
                fprintf(stderr, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stderr, "Branch not take\n");
                #endif
            }
            break;
        case 0x7: // >= unsigned
            #ifdef DEBUG
            fprintf(stderr, "Comparing 0x%08X (contents of register x%d) >= 0x%08X (contents of register x%d)\n", reg_array[rs1], rs1, reg_array[rs2], rs2);
            #endif
            if (reg_array[rs1] >= reg_array[rs2]) {
                #ifdef DEBUG
                fprintf(stderr, "Branch taken, adding 0x%03X to PC\n", imm);
                #endif
                pc += imm;
            }
            else{
                #ifdef DEBUG
                fprintf(stderr, "Branch not take\n");
                #endif
            }
            break;
        default:
            fprintf(stderr, "0x%X is not a valid Branch FUNC3 code\n", func3);
            exit(1);
    }

    return;
}
void u_type(uint32_t mem_array[], int size, uint32_t *pc, uint32_t reg_array[32]){

    uint32_t instruction = mem_array[*pc/4];

    uint8_t opcode = instruction & 0x0000007F;
    uint8_t rd = (instruction >> 7) & 0x0000001F;
    int32_t imm = (instruction & 0xFFFFF000) >> 12;

    #ifdef DEBUG
    fprintf(stderr, "U-Type instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Immediate: 0x%08X\n", opcode, rd, imm);
    #endif

    switch (opcode)
    {
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

    return;
}

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
    if (immmsb == 1){
        imm = imm | 0xFFE00000;
    }else{
        imm = imm & ~(0xFFE00000);
    }

    #ifdef DEBUG
    fprintf(stderr, "J-Type instruction breakdown:\n    Opcode: 0x%02X\n    R_Des: 0x%02X\n    Immediate: 0x%06X\n", opcode, rd, imm);
    fprintf(stderr, "Storing 0x%08X into register x%d, then adding 0x%05X to PC\n", *pc + 4, rd, imm);
    #endif


    reg_array[rd] = *pc + 4;
    *pc += imm;
    
    return;
}