/* 
 * File:   THttpChild.h
 * Author: mschwartz
 *
 * Created on July 22, 2010, 12:56 PM
 */

#ifndef THTTPCHILD_H
#define	THTTPCHILD_H

class THttpChild {
protected:
    TServerSocket *sock;
public:
    THttpChild(TServerSocket *ss);
    virtual ~THttpChild();
    void Run();
};

#endif	/* THTTPCHILD_H */

