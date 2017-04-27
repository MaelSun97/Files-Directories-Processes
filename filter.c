/* filter.c */

#include "search.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Test whether or not the given path should be filtered out of the output.
 * @param   path        Path to file or directory.
 * @param   settings    Settings structure.
 * @return  Whether or not the path should be excluded from the output (true to
 * exclude, false to include).
 */
bool        filter(const char *path, const Settings *settings) {
    struct stat s;
    lstat(path, &s);
    if (settings->access){
        if (access(path, settings->access) != 0) return true;
    }
    if (settings->type){
        if ((s.st_mode & S_IFMT) != settings->type) return true;
    } 
    if (settings->empty){
    	switch (s.st_mode & S_IFMT){
    		case S_IFREG:
    			if(s.st_size >0){
    				return true;
    			}
    			break;
    		case S_IFDIR:
    			//printf("weird\n");
    			if (!is_directory_empty(path)){
    				//printf("found director\n");
    				return true;
    			}
    			break;
    		default:
    			return true;
    			break;
    	}
    	
    	/*if ((s.st_mode & S_IFMT) == S_IFREG){
        	if (s.st_size > 0){
        		 return true;
        	}
        }
        else if((s.st_mode & S_IFMT) == S_IFDIR){
        	if (!is_directory_empty(path)){
        		return true;
        	}
        }
        else{
        	return true;
        }
        */
    }
    
    if (settings->name){
    	char *basename=strrchr(path, '/');
        if (fnmatch(settings->name, basename, 0) != 0) return true;
    }
    if (settings->path){
        if (fnmatch(settings->path, path, 0) != 0) return true;
    }
    if (settings->perm){
        if ((s.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) != settings->perm) return true;
    }
    if (settings->newer){
        if (s.st_mtime <= settings->newer) return true;
    }
    if (settings->uid >=0){
        if (s.st_uid != settings->uid) return true;
    }
    if (settings->gid >= 0){
        if (s.st_gid != settings->gid) return true;
    }
    
    return false;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
