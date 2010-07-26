/* 
 * File:   TServerSocket.h
 * Author: mschwartz
 *
 * Created on July 22, 2010, 11:30 AM
 */

#ifndef TSERVERSOCKET_H
#define	TSERVERSOCKET_H

class TServerSocket {
protected:
    int fd;
    bool isValid;

public:
    TServerSocket(int port);
    virtual ~TServerSocket();

    bool Alive() {
        return isValid;
    }
    TSocket *Accept();
};

#endif	/* TSERVERSOCKET_H */

