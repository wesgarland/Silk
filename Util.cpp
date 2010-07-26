#include "Silk.h"

char *Util::FileGetContents(char *filename) {
    int fd = open(filename, O_RDONLY);
    long size = lseek(fd, 0, 2);
    lseek(fd, 0, 0);
    char *contents = new char[size+1];
    read(fd, contents, size);
    close(fd);
    contents[size] = '\0';
    return contents;
}

long Util::CurrentTimeMillis() {
    struct timeval t;
    gettimeofday(&t, NULL);
    long sec = (long)t.tv_sec;
    long usec = (long)t.tv_usec;
    long v = sec*1000000 + usec;
    return v;
}

