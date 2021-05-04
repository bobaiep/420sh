#include "exec.h"

int sh_launch(char **args){
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
        	perror("420sh");
        }
        exit(EXIT_FAILURE);
    } 
	else if (pid < 0) {
        // Error forking
        perror("420sh");
    } 
	else {
        // Parent process
        do {
        	waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int sh_execute(char **args){
  	int i;

	if (args[0] == NULL) {
		// An empty command was entered.
		return 1;
	}

	for (i = 0; i < sh_nb_builtins; i++) {
		if (strcmp(args[0], list_builtins[i]) == 0) {
			return (*builtins_func[i])(args);
		}
	}

	return sh_launch(args);
}

void main_loop(){
	char *line;
	char **args;
	int status;
	shell_init();
	sh_change_color(NULL);
	printf("\e[1;1H\e[2J");
	do {
		set_prompt();
		printf("%s ",current->prompt);
		line = sh_read_line();
		add_to_hist(current->history,line);
		args = sh_split_line(line);
		status = sh_execute(args);

		free(line);
		free(args);
	} while (status);
	printf("\e[1;1H\e[2J");
	shell_destroy();
}