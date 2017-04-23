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
	DIR *d=opendir(path);
	struct dirent *ent;
	
	if(d ==NULL){
		fprintf(stderr, "%s", strerror(errno));
	return false;
	}
	int count;
	while (ent = readdir(d)){
		count++;
	}
	closedir(d);
	return count <= 2;//see the comment below.
	//n in this case ... . and .. if n is less than or equal to two, return true, else return false.
}

/**
 * Retrieve the modification time of the given file.
 * @param   path        Path to file of directory.
 * @return  The modification time of the given file.
 */
time_t      get_mtime(const char *path) {
    struct stat s;
    if (lstat(path, &s) != 0){
        fprintf(stderr, "%s", strerror(errno));
        return 0;
	}
    return s.st_mtime;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
