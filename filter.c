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
    if (settings->access != 0){//correct...we dont have the pointer.
        if (access(path, settings->access) != 0) return true;
    }
    if (settings->type != 0){//this is corrrecg
        if ((s.st_mode & S_IFMT) != settings->type) return true;
    } 
    if (settings->empty != 0){//this is tricky...
        if ((s.st_size != 0)) return true;
    }
    if (settings->name != 0){//98%right
        if (fnmatch(settings->name, basename(path), 0) != 0) return true;
    }
    if (settings->path != 0){//correct
        if (fnmatch(settings->path, path, 0) != 0) return true;
    }
    if (settings->perm != 0){//fine
        if ((s.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) != settings->perm) return true;
    }
    if (settings->newer != 0){//
        if (s.st_mtime <= settings->newer) return true;
    }
    if (settings->uid != 0){
        if (s.st_uid != (uid_t)settings->uid) return true;
    }
    if (settings->gid != 0){
        if (s.st_gid != (gid_t)settings->gid) return true;
    }
    return false;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
