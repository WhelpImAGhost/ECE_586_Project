/****
 ECE 586 Final Project
 Team 2

 Objective: Simulate a RISCV-32I processor Instruction Set Architecture

 */


int main(int argc, char *argv[]){
       // Set default filename
    char *default_filename = "Other_dins/Default.din";
    char *filename = default_filename;

    // Cache usage and tracking variables
    int cache_size = CACHE_SIZE;
    int tag, set_index, byte_select;
    int CacheResult;
    int SnoopReply;


    // Flags for setting non-default variable vvalues
    for( argc--, argv++; argc > 0; argc-=2, argv+=2 ) {
        if (strcmp(argv[0], "-m" ) == 0 ) 
            mode = atoi(argv[1]); // Set normal operation
        else if (strcmp(argv[0], "-f" ) == 0 ) 
            filename = argv[1]; // Set input file
        else if (strcmp(argv[0], "-c") == 0)
            cache_size = atoi(argv[1]);
        else { 
            printf("\nInvalid Arguments\n"); exit(-1); 
        }
    }
    return 0;
}