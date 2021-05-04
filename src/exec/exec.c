#include "exec.h"

#define RESET_COLOR "\e[m"
#define GREEN "\e[32m"
#define BLUE "\e[36m" 
#define RED "\e[31m"

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
	int color = 0;
	shell_init();
	printf("Choose the color of the prompt : \n");
	printf(RED" - RED : 0\n"RESET_COLOR);
	printf(BLUE" - BLUE : 1\n"RESET_COLOR);
	printf(GREEN" - GREEN : 2\n"RESET_COLOR);
    scanf("%i", &color);
	getchar();
	printf("\e[1;1H\e[2J");
	do {
		set_prompt(color);
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