/* utilities.c */

#include "search.h"

#include <errno.h>
#include <string.h>
#include <time.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Test whether or not a directory is empty.
 * @param   path        Path to directory.
 * @return  Whether or not a directory is empty.
 */
bool        is_directory_empty(const char *path) {
//	DIR *path;
	struct dirent *ent;
	
	if((path = opendir(".")) != NULL){
		if ((ent=readdir(path)) != NULL){
			return true;
			closedir(path);
		}
		else{
    		return false;
    	}
    }
    else{
    	fprintf(stderr, "%s", strerror(errno));
    	return EXIT_FAILURE;
    }
}

/**
 * Retrieve the modification time of the given file.
 * @param   path        Path to file of directory.
 * @return  The modification time of the given file.
 */
time_t      get_mtime(const char *path) {
    struct stat s;
    if (stat(path, &s)<0){
        fprintf(stderr, "%s", strerror(errno));
        return EXIT_FAILURE;
}
    return s.st_mtim;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
