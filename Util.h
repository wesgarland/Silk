/* 
 * File:   Util.h
 * Author: mschwartz
 *
 * Created on July 24, 2010, 12:48 PM
 */

#ifndef UTIL_H
#define	UTIL_H

class Util {
public:
    static char *FileGetContents(char *filename);
    static long CurrentTimeMillis();
};

#endif	/* UTIL_H */

