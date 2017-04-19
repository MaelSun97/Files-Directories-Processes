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
    struct dirent *ent;
    DIR *d = opendir(root);
    char *str;
    if(d = NULL){
        fprintf(stderr, "Unable to opendir on %s: %s\n", path, strerror(errno));
        return EXIT_FAILURE;
    }
    for (ent = readdir(d); ent; ent = readdir(d)){
        if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0)            
            continue;

        strcpy(str, root);
        strcat(str, '/');
        strcat(str, ent->d_name);

        if (ent->d_type == DT_DIR){
            search(str, settings);
        }
        else if (filter(str, settings) == 0) execute(str, settings);
        }
    closedir(d);   
    return 0;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
