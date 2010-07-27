/* 
 * File:   main.cpp
 * Author: mschwartz
 *
 * Created on July 22, 2010, 11:11 AM
 */

#include "Silk.h"

/*
 * 
 */

#define NUM_CHILDREN 50
//#define NOTHREADS

void help(char *name) {
    printf("Usage:\n");
    printf("\t%s jsfile.js\n", name);
    printf("Where:\n");
    printf("\tjsfile.js is the script to execute per http child\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        help(argv[0]);
    }
    TInterpreter::jsfile = Util::FileGetContents(argv[1]);
    printf("%s\n", TInterpreter::jsfile);
    TServerSocket *server = new TServerSocket(9090);

#ifdef NOTHREADS
    THttpChild *child = new THttpChild(server);
    child->Run();
    exit(0);
#endif
    
    int childCount = 0;
    for (int n=0; n<NUM_CHILDREN; n++) {
        pid_t pid = fork();
        if (pid == 0) {
            THttpChild *child = new THttpChild(server);
            child->Run();
        }
        else if (pid == -1) {
            perror("fork()");
        }
        else {
            childCount++;
        }
    }
    printf("Spawned 10\n");
    while (1) {
        int statx;
        waitpid(-1, &statx, 0);
        if (WIFEXITED(statx)) {
            childCount--;
            if (childCount < 1) {
                break;
            }
        }
    }
    return 0;
}
