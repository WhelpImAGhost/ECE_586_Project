#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "defines.c"

int main(int argc, char *argv[]){

    uint32_t func7, rs2, rs1, func3, rd, opcode, imm_21, imm_13, imm_12, instruction;


    for( argc--, argv++; argc > 0; argc-=2, argv+=2 ) {
        if (strcmp(argv[0], "-r" ) == 0 ) {
            printf("Register Mode\n");
            printf("Func7 val: "); scanf("%x", &func7);
            printf("Rs2 val: "); scanf("%x", &rs2);
            printf("RS1 val: "); scanf("%x", &rs1);
            printf("Func3 val: "); scanf("%x", &func3);
            printf("Rd val: "); scanf("%x", &rd);
            printf("Opcode val: "); scanf("%x", &opcode);

            instruction = (func7 << 25) + (rs2 << 20) + (rs1 << 15) + (func3 << 12) + (rd << 7) + opcode;
            printf("Register instruction: 0X%08X\n", instruction);
        }
        else if (strcmp(argv[0], "-i" ) == 0 ) {
            printf("Immediate Mode\n");
            printf("11:0 IMM val: "); scanf("%x", &imm_12);
            printf("RS1 val: "); scanf("%x", &rs1);
            printf("Func3 val: "); scanf("%x", &func3);
            printf("Rd val: "); scanf("%x", &rd);
            printf("Opcode val: "); scanf("%x", &opcode);

            instruction = (imm_12 << 20) | (rs1 << 15) | (func3 << 12) | (rd << 7) | opcode;
            printf("Immediate instruction: 0x%08X\n", instruction);
        }
        else if (strcmp(argv[0], "-s" ) == 0 ) {
            printf("Store Mode\n");
            printf("11:0 IMM val: "); scanf("%x", &imm_12);
            printf("Rs2 val: "); scanf("%x", &rs2);
            printf("RS1 val: "); scanf("%x", &rs1);
            printf("Func3 val: "); scanf("%x", &func3);
            printf("Opcode val: "); scanf("%x", &opcode);

            
            instruction = ((imm_12 & 0xFE0) << 20)  // Upper 7 bits of immediate (bits 31-25)
                        | (rs2 << 20)               // Rs2 (bits 24-20)
                        | (rs1 << 15)               // Rs1 (bits 19-15)
                        | (func3 << 12)             // Func3 (bits 14-12)
                        | ((imm_12 & 0x1F) << 7)    // Lower 5 bits of immediate (bits 11-7)
                        | opcode;                   // Opcode (bits 6-0)

            printf("Store instruction: 0x%08X\n", instruction);
        }
        else if (strcmp(argv[0], "-b" ) == 0 ) {
            printf("Branch Mode\n");
            printf("12:0 IMM val: "); scanf("%x", &imm_13);
            printf("Rs2 val: "); scanf("%x", &rs2);
            printf("RS1 val: "); scanf("%x", &rs1);
            printf("Func3 val: "); scanf("%x", &func3);
            printf("Opcode val: "); scanf("%x", &opcode);

            // B-type instruction encoding
            instruction = ((imm_13 & 0x1000) << 19)  // Bit 12 (MSB) -> bit 31
                        | ((imm_13 & 0x7E0) << 20)   // Bits 10:5 -> bits 30:25
                        | (rs2 << 20)               // Rs2 (bits 24-20)
                        | (rs1 << 15)               // Rs1 (bits 19-15)
                        | (func3 << 12)             // Func3 (bits 14-12)
                        | ((imm_13 & 0x1E) << 7)    // Bits 4:1 -> bits 11:8
                        | ((imm_13 & 0x800) >> 4)   // Bit 11 -> bit 7
                        | opcode;                   // Opcode (bits 6-0)

            printf("Branch instruction: 0x%08X\n", instruction);

        }
        else if (strcmp(argv[0], "-u" ) == 0 ) {
            printf("Upper Mode\n");
            printf("31:12 IMM val: "); scanf("%x", &imm_21);
            printf("Rd val: "); scanf("%x", &rd);
            printf("Opcode val: "); scanf("%x", &opcode);

            instruction = (imm_21 << 12) // Immediate (bits 31-12)
                | (rd << 7)      // Destination register (bits 11-7)
                | opcode;        // Opcode (bits 6-0)

            printf("Upper instruction: 0x%08X\n", instruction);

        }
        else if (strcmp(argv[0], "-j" ) == 0 ) {
            printf("Jump Mode\n");
            printf("20:0 IMM val: "); scanf("%x", &imm_21);
            printf("Rd val: "); scanf("%x", &rd);
            printf("Opcode val: "); scanf("%x", &opcode);


            instruction = ((imm_21 & 0x100000) << 11) // Bit 20 -> bit 31
                        | ((imm_21 & 0x7FE) << 20)    // Bits 10:1 -> bits 30:21
                        | ((imm_21 & 0x800) << 9)     // Bit 11 -> bit 20
                        | ((imm_21 & 0xFF000) << 0)   // Bits 19:12 -> bits 19:12
                        | (rd << 7)                   // Destination register (bits 11-7)
                        | opcode;                     // Opcode (bits 6-0)

            printf("Jump instruction: 0x%08X\n", instruction);
        }
        else { 
            printf("\nInvalid Arguments\n"); exit(-1); 
        }

    }    

    return 0;
}