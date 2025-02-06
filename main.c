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
void printAllReg(uint32_t regs[32] );

// Function Prototypes
uint32_t readByte(uint32_t array[], int size, int address);
uint32_t readHalfWord(uint32_t array[], int size, int address);
uint32_t readWord(uint32_t array[], int size, int address);
int writeByte(uint32_t array[], int size, int address, uint32_t value);
int writeHalfWord(uint32_t array[], int size, int address, uint32_t value);
int writeWord(uint32_t array[], int size, int address, uint32_t value);

void fetch_and_decode(uint32_t array[], uint32_t pc, uint32_t* opcode);

void r_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]);
void i_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]);
void s_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]);
void b_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]);
void u_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]);
void j_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]);

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

    // Register declarations
    uint32_t x[32];
    x[0] = 0;
    x[1] = 0;
    x[2] = 0;

    // Set default mode
    int mode = 0;

    // Memory & Stack Starting Addresses
    uint32_t stack_address = STACK_ADDRESS, prog_start = START_ADDRESS;

    // Set default filename
    char *default_filename = "Test Memory Files/prog.mem";
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

    // Begin fetching and decoding instructions

    while(continue_program){
        fetch_and_decode(MainMem, pc, &current_opcode);


        switch (current_opcode) {
            case REGS_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is a Register Instruction\n", current_opcode);
                #endif
                break;
            case IMMS_OP:
            case JALR_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is an Immediate Instruction\n", current_opcode);
                #endif
                break;
            case LOAD_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is a Load Instruction\n", current_opcode);
                #endif
                break;
            case STOR_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is a Store Instruction\n", current_opcode);
                #endif
                break;
            case BRAN_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is a Branch Instruction\n", current_opcode);
                #endif
                break;
            case JAL_OP:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is a Jump Instruction\n", current_opcode);
                #endif
                break;
            case LUI_OP:
            case AUIPC:
                #ifdef DEBUG
                fprintf(stderr, "0x%02X is an 'Upper Immediate' Instruction\n", current_opcode);
                #endif
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
        pc += 4;

    }


  
    printAllReg(x);
    printAllMem(MainMem, MemWords);


    return 0;

}

// Memory dump function for debugging (using a log file)
void printAllMem(uint32_t array[], int size){
#ifdef DEBUG
fprintf(stderr,"\n");
for (int i = 0; i < size; i++){

    printf( "Array Member: %4d     Memory Address: 0x%08X     Contents: 0x%08X\n", i, 4*i, array[i]);

}
#endif
    return;
}

// Function to display all register values
void printAllReg(uint32_t regs[32] ){

    for (int i = 0; i < 32; i++){
        printf("Register: x%02d   Contents: ", i);
        if (regs[i] == -1) printf("NULL\n");
        else printf("%08X\n", regs[i]);

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

    *opcode = selected_instruction & 0x7F;

    return;
}


void r_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]){

    return;
}
void i_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]){

    return;
}
void s_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]){

    return;
}
void b_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]){

    return;
}
void u_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]){

    return;
}
void j_type(uint32_t mem_array[], int size, uint32_t pc, uint32_t reg_array[32]){

    return;
}