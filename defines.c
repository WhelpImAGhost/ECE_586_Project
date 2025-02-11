#define MEMORY_SIZE 19 // 64KB memory size, 2^16 bytes, 2^19 bits
#define START_ADDRESS 0 // Starting address
#define STACK_ADDRESS 65536 // Stack address

// Opcodes
#define REGS_OP 0b0110011
#define IMMS_OP 0b0010011
#define LOAD_OP 0b0000011
#define STOR_OP 0b0100011
#define BRAN_OP 0b1100011
#define JAL_OP  0b1101111
#define JALR_OP 0b1100111
#define LUI_OP  0b0110111
#define AUIPC   0b0010111
#define ENVIRO  0b1110011
#define ZERO_OP 0b0000000