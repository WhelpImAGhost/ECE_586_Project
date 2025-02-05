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


int main(int argc, char *argv[]){

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
            stack_address = atoi(argv[1]);  // Set stack pointer
        }
        else if (strcmp(argv[0], "-s")){
            prog_start = atoi(argv[1]); // Set starting address
        }
        else { 
            printf("\nInvalid Arguments\n"); exit(-1); 
        }

    }
    FILE *file = fopen(filename, "r");

    
    // Function to calculate number of words that can be stored in memory array
    const int MemWords = (pow(2,MEMORY_SIZE) / 32);

    uint32_t MainMem[MemWords];
    for (int i = 0; i < MemWords; i++){
        MainMem[i] = 0;
    }

    #ifdef DEBUG

    #endif

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

        // Body for parsing lines
        #ifdef DEBUG

        fprintf(stderr, "Extracted memory addresss:      0x%08X\n", address);
        fprintf(stderr, "Extracted instruction contents: 0x%08X\n", instruction);

        #endif

    }

    return 0;

}

