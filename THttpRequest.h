/* 
 * File:   THttpRequest.h
 * Author: mschwartz
 *
 * Created on July 22, 2010, 4:45 PM
 */

#ifndef THTTPREQUEST_H
#define	THTTPREQUEST_H

class THttpRequest {
protected:
    bool alive;
protected:
    THeaderList headers;
    THeaderList env;
public:
    char *method;
    char *uri;
    char *protocol;
protected:
    char firstLine[512];
    bool ParseRequest(TSocket *s);
    bool ParseHeaders(TSocket *s);
public:
    THttpRequest(TSocket *s);
    virtual ~THttpRequest();
    bool IsAlive() { return alive; }
    const char *GetFirstLine() { return firstLine; }
    const char *GetMethod() { return method; }
    const char *GetURI() { return uri; }
    const char *GetProtocol() { return protocol; }
    const char *GetHeader(const char *key);
    const char *GetEnv(const char *key);
public:
    JSObject *GetObjectJS(JSContext *cx) {
        return headers.GetObjectJS(cx);
    }
    void Dump();
};

#endif	/* THTTPREQUEST_H */

