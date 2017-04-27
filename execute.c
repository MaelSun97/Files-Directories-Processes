/* expression.c */

#include "search.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Executes the -print or -exec expressions (or both) on the specified path.
 * @param   path        Path to a file or directory
 * @param   settings    Settings structure.
 * @return  Whether or not the execution was successful.
 */
int	    execute(const char *path, const Settings *settings) {
	int status = EXIT_SUCCESS;
	if(settings->exec_argc != 0 && settings->print){
		puts(path);
	}
	if(settings->exec_argc != 0){
		char *array[settings->exec_argc+1];//array needs to be +1 of argc b/c last things has to be a NULL
		for(int i=0; i < settings->exec_argc;i++){
			if(streq(settings-> exec_argv[i], "{}")){
				array[i] = (char *)path;//we need to make sure this needs to be a path with curly brackets.
			}
			else{
				array[i] = settings-> exec_argv[i];//exec_argv is an array as well.
			}
		}
		array[settings->exec_argc] = NULL;//the way exec_VP is written. It requires the arguments null terminated.
		pid_t pid = fork();
		if(pid == 0){
			if(execvp(array[0], array) < 0)
				_exit(EXIT_FAILURE);
		}
		while (wait(&status) != pid);
	}
	else{
	puts(path);
	}
	
	//if(settings->exec_argc != 0 && settings->print){//in order for this to be triggered, first one is true so all u need is the second if statement.
	//puts(path);
	//}
	
    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
