/****
 ECE 586 Final Project
 Team 2

 Objective: Simulate a RISCV-32I processor Instruction Set Architecture

 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "defines.c"

// Function to load memory image from file into memory 
int loadMemImage(const char *filename, uint32_t *memory, size_t mem_size){
    FILE *file = fopen(filename, "r");

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
        return 1;
    }

};

int main(){

    return 0;
}