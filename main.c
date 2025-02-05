/****
 ECE 586 Final Project
 Team 2

 Objective: Simulate a RISCV-32I processor Instruction Set Architecture

 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "defines.c"

// Debug function to print memory table
void printAllMem(uint32_t array[], int size);

// Function to load in an individual byte from memory
uint32_t readByte(uint32_t array[], int size, int address);
uint32_t readHalfWord(uint32_t array[], int size, int address);
uint32_t readWord(uint32_t array[], int size, int address);
int writeByte(uint32_t array[], int size, int address, uint32_t value);
int writeHalfWord(uint32_t array[], int size, int address, uint32_t value);
int writeWord(uint32_t array[], int size, int address, uint32_t value);

int main(int argc, char *argv[]){

    uint32_t test_word;

    // Local variables for function use
    uint32_t address, instruction, pc = 0, sp = 0, ra = 0;

    // Set default mode
    int mode = 0;

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

    // Function to calculate number of words that can be stored in memory array
    const int MemWords = (int) (pow(2,MEMORY_SIZE) / 32);

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

    #ifdef DEBUG
    fprintf(stderr, "Using file: '%s'\n", filename);
    #endif

    const int MemAlloc = pow(2, MEMORY_SIZE);

    // Begin parsing instructions
    while (fscanf(file, "%x: %x", &address, &instruction ) == 2){

        if (address >= MemAlloc){
            fprintf(stderr, "Address 0x%08X is out of memory bounds\n", address);
        }

        MainMem[address / 4] = instruction;

        // Body for parsing lines
        #ifdef DEBUG
        fprintf(stderr, "Extracted memory addresss:      0x%08X\n", address);
        fprintf(stderr, "Extracted instruction contents: 0x%08X\n", instruction);
        #endif

    }
    

    test_word = readHalfWord(MainMem, MemWords, 2);
    printf("Extracted byte: 0x%08X\n", test_word);

    writeHalfWord(MainMem, MemWords, 14, 0xDEAD);
    printAllMem(MainMem, MemWords);
    
    return 0;

}

void printAllMem(uint32_t array[], int size){
#ifdef DEBUG
fprintf(stderr,"\n");
for (int i = 0; i < size; i++){

    printf( "Array Member: %4d     Memory Address: 0x%08X     Contents: 0x%08X\n", i, 4*i, array[i]);

}
#endif
    return;
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

/*    #ifdef DEBUG
    if (address % 2 != 0) {
        fprintf(stderr, "Loading unaligned value\n");
    }
    #endif */

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