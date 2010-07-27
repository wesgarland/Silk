/* 
 * File:   TSocket.h
 * Author: mschwartz
 *
 * Created on July 22, 2010, 11:18 AM
 */

#ifndef TSOCKET_H
#define	TSOCKET_H

#include "Silk.h"

#define SOCKET_BUFFER_SIZE 16384

class TSocket {
protected:
    int fd;
    char remote_addr[16];
    int putback_char;
    unsigned char input[SOCKET_BUFFER_SIZE];
    ssize_t indx, inlen;

public:
    TSocket(int fd, sockaddr_in *their_addr);
    TSocket(const char *hostname, int port); // to connect to remote host
    virtual ~TSocket();

    bool Alive() {
        return fd > 0;
    }
public:
    bool Write(const unsigned char *data, int len);
    bool WriteLine(const char *s) {
        return Write((unsigned char*)s, strlen(s));
    }
    bool ReadLine(char *line);
    int Read();
    int Read(unsigned char *buf, int len);

    void Putback(int c) {
        putback_char = c;
    }
public:

    const char *RemoteIP() {
        return remote_addr;
    }
    void SetTimeout(int seconds);
};

#endif	/* TSOCKET_H */
