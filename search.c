/* search.c */

#include "search.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>

/**
 * Recursively search through the provided root directory
 * @param   root        Path to directory
 * @param   settings    Settings structure
 * @return  Whether or not the search was successful.
 */
int	    search(const char *root, const Settings *settings) {
    //struct dirent *ent;
    //printf("%s\n",root);
    DIR *d = opendir(root);
    char *str;
    if(d == NULL){
        fprintf(stderr, "Unable to opendir on %s: %s\n", root, strerror(errno));
        return EXIT_FAILURE;
    }
    for (struct dirent *ent = readdir(d); ent; ent = readdir(d)){
    	if (streq(ent->d_name, ".") || streq(ent->d_name, ".."))
            continue;
            //printf("asfjalksj\n");
		char buff[BUFSIZ];
		sprintf(buff, "%s/%s", root, ent->d_name);
        //strcpy(str, root);
        //strcat(str, '/');
        //strcat(str, ent->d_name);
       //printf("%s\n", str);

        if (!filter(buff, settings)){
        	execute(buff, settings);
       }
       //printf("please\n");
        if (ent->d_type == DT_DIR){
        	search(buff, settings);
        }
    }
    closedir(d);
    return EXIT_SUCCESS;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
