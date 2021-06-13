#include <string.h>
#include <stdlib.h>
#include "src/cmd/cmd.h"
#include "src/exec/exec.h"
#include "src/gui/gui.h"

int main(int argc, char** argv){
    if (argc == 1){
        main_loop(0);
    }

    if (argc > 1){
        if (strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"-h") == 0){
            print_main_help();
        }
        
        if (strcmp(argv[1],"--voice") == 0 || strcmp(argv[1],"-v") == 0){
            pid_t pid;
            int pipe_fds[2];

            pipe(pipe_fds);

            pid = fork();
            if (pid == 0) {
                dup2(pipe_fds[1],STDOUT_FILENO);
                close(pipe_fds[0]);
                InitGUI(argc,argv);
            } 
            else if (pid < 0) {
                // Error forking
                perror("420sh");
            } 
            else {
                close(pipe_fds[1]);
                main_loop(pipe_fds[0]);
            }
        }
    }

    return EXIT_SUCCESS;
}