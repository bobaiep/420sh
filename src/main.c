#include <string.h>
#include <stdlib.h>
#include "cmd/cmd.h"

int main(int argc, char** argv){
    if (strcmp(argv[1],"--help") || strcmp(argv[1],"-h")){
        print_main_help();
    }

    if (argc == 1){
        main_loop();
    }

    if (strcmp(argv[1],"--voice") || strcmp(argv[1],"-v")){
        // TODO: Implémenter la reconnaisance vocale.
        //voice_recognition();
        return 0;
    }
    
    return EXIT_SUCCESS;
}