#ifndef CACHE_H
#define CACHE_H

#include <zlib.h>

/*
 * Basic data structures for the directory cache
 *
 * NOTE NOTE NOTE! This is all in the native CPU byte format. It's
 * not even trying to be portable. It's trying to be efficient. It's
 * just a cache, after all.
 */

#define CACHE_SIGNATURE 0x44495243  /* "DIRC" */
struct cache_header {
    unsigned int signature;
    unsigned int version;
    unsigned int entries;
    unsigned char sha1[20];
};

/*
 * The "cache_time" is just the low 32 bits of the
 * time. It doesn't matter if it overflows - we only
 * check it for equality in the 32 bits we save.
 */
struct cache_time {
    unsigned int sec;
    unsigned int nsec;
};

/*
 * dev/ino/uid/gid/size are also just tracked to the low 32 bits
 * Again - this is just a (very strong in practice) heuristic that
 * the inode hasn't changed.
 */
struct cache_entry {
    struct cache_time ctime;
    struct cache_time mtime;
    unsigned int st_dev;
    unsigned int st_ino;
    unsigned int st_mode;
    unsigned int st_uid;
    unsigned int st_gid;
    unsigned int st_size;
    unsigned char sha1[20];
    unsigned short namelen;
    unsigned char name[0];
};


#endif
