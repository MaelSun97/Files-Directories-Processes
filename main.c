/* driver.c */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

/* Functions */

void	    usage(const char *program_name, int status) {
    fprintf(stderr, "Usage: %s PATH [OPTIONS] [EXPRESSION]\n", program_name);
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "    -executable     File is executable or directory is searchable to user\n");
    fprintf(stderr, "    -readable       File readable to user\n");
    fprintf(stderr, "    -writable       File is writable to user\n\n");
    fprintf(stderr, "    -type [f|d]     File is of type f for regular file or d for directory\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -name  pattern  Base of file name matches shell pattern\n");
    fprintf(stderr, "    -path  pattern  Path of file matches shell pattern\n\n");
    fprintf(stderr, "    -perm  mode     File's permission bits are exactly mode (octal)\n");
    fprintf(stderr, "    -newer file     File was modified more recently than file\n\n");
    fprintf(stderr, "    -uid   n        File's numeric user ID is n\n");
    fprintf(stderr, "    -gid   n        File's numeric group ID is n\n");
    fprintf(stderr, "\nExpressions:\n\n");
    fprintf(stderr, "    -print          Display file path (default)\n");
    fprintf(stderr, "    -exec cmd {} ;  Execute command on path\n");
    exit(status);
}

/* Main Execution */

int	    main(int argc, char *argv[]) {
    Settings settings = {
        .access = 0,
        .uid = -1,
        .gid = -1,
    };
    int argind =2;
    //PORGRAM_NAME=argv[0];
    char *program_name=argv[0];
    char *root = ".";
    root = argv[1];
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
        char *arg = argv[argind++];
        //you have to find the type first. next argument
        if (streq(arg, "-executable")){
            settings.access |= X_OK;
        }
        else if(streq(arg, "-readable")){
            settings.access |= R_OK;
        }
        else if(streq(arg, "-writable")){
            settings.access |= W_OK;
        }
        else if(streq(arg, "-type")){
        	//printf("hello\n");
            char *perrier = argv[argind++];
            //printf("%s\n", perrier);
            if(streq(perrier, "f")){
                settings.type = S_IFREG;
            }
            else{
                settings.type = S_IFDIR;
            }
        }
        else if(streq(arg, "-empty")){
            settings.empty = true;
        }
        else if(streq(arg, "-name")){
            settings.name = argv[argind++];//next argument
        }
        else if(streq(arg, "-path")){
            settings.path = argv[argind++];//matches the next argument
        }
        else if(streq(arg, "-perm")){
            settings.perm = strtol(argv[argind++], NULL, 8);//special option is NULL, no special option
        }
        else if(streq(arg, "-newer")){
            settings.newer = get_mtime(argv[argind++]);//function get mtime gets the time in miliseconds.//LOOKUP!!!!!!!!
        }
        else if(streq(arg, "-uid")){
            settings.uid = strtol(argv[argind++], NULL, 10);//base 10
        }
        else if(streq(arg, "-gid")){
            settings.gid = strtol(argv[argind++], NULL, 10);//base 10
        }
        else if(streq(arg, "-print")){
            settings.print = true;//doesnt have boolean built in C++, somewhere true is 1 in C...P Bui specified it.
        }
        else if(streq(arg, "-exec")){
            settings.exec_argv = &argv[argind];
            for(settings.exec_argc = 0; argind < argc && !streq(argv[argind], ";"); argind++){
                settings.exec_argc++;
            } 
        }
        else if(streq(arg, "-help")){
            usage(program_name, EXIT_SUCCESS);
        }
    }
    if(!filter(root, &settings)){
    	execute(root, &settings);
    }
    
    return search(root, &settings);
    //return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
