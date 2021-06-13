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

int sh_execute(char ***args){
  	int i;

	if (*args[0] == NULL) {
		// An empty command was entered.
		return 1;
	}
	int argc = 0;
	for (size_t i = 0; *(*args+i) != NULL; i++){
        argc++;
    }

	for(i = 0; i < current->aliases->nb_alias; i++){
		if (strcmp(*args[0], current->aliases->aliases[i]->alias) == 0){
			char ** new = malloc((current->aliases->aliases[i]->cmd_size  + (argc + 1)) * sizeof(char*));
			memcpy(new,current->aliases->aliases[i]->cmd,current->aliases->aliases[i]->cmd_size * sizeof(char*));
			memcpy(new + current->aliases->aliases[i]->cmd_size,*args+1,(argc + 1) * sizeof(char*));
			free(*args);
			*args = new;
		}
	}
	for (i = 0; i < sh_nb_builtins; i++) {
		if (strcmp(*args[0], list_builtins[i]) == 0) {
			return (*builtins_func[i])(*args);
		}
	}

	return sh_launch(*args);
}

void main_loop(int pipe_fds){
	char* line;
	char **args;
	int status = 1;
	char **args1;
	
	shell_init(pipe_fds);
	//printf("\e[1;1H\e[2J");

	if (file_exist(".config")){
		FILE * config = fopen(".config","r");
		char* line1 = sh_read_line(config);
		while (line1 != NULL){
			args = sh_split_line(line1);
			status = sh_execute(&args);

			free(line1);
			if (args){
				free(args);
			}
			line1 = sh_read_line(config);
		}
		fclose(config);
	}
	else{
		sh_change_color(NULL);
		printf("\e[1;1H\e[2J");
	}
	if (pipe_fds){
		int flags = fcntl(current->pipe_fds, F_GETFL, 0);
		fcntl(current->pipe_fds, F_SETFL, flags | O_NONBLOCK);
	}
	do {
		set_prompt();
		printf("%s ",current->prompt);
		line = sh_read_line(stdin);
		char* line_gtk = malloc(13 * sizeof(char));
		if (current->pipe_fds && read(current->pipe_fds,line_gtk,13) >0){
			printf("%s",line_gtk);
			add_to_hist(current->history,line_gtk);
			args1 = sh_split_line(line_gtk);
			sh_execute(&args1);
		}
		free(line_gtk);
		if (line == NULL){
			continue;
		}
		add_to_hist(current->history,line);
		args = sh_split_line(line);
		status = sh_execute(&args);

		free(line);
		if (args){
			free(args);
		}
	} while (status);
	printf("\e[1;1H\e[2J");
	shell_destroy();
}