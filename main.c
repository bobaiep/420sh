#include <string.h>
#include <stdlib.h>
#include "src/cmd/cmd.h"
#include "src/exec/exec.h"

int main(int argc, char** argv){
    if (argc == 1){
        main_loop();
    }

    if (argc > 1){
        if (strcmp(argv[1],"--help") || strcmp(argv[1],"-h")){
            print_main_help();
        }
        
        if (strcmp(argv[1],"--voice") || strcmp(argv[1],"-v")){
            // TODO: Implémenter la reconnaisance vocale.
            //voice_recognition();
            return 0;
        }
    }

    
    return EXIT_SUCCESS;
}