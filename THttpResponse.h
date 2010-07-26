/* 
 * File:   THttpResponse.h
 * Author: mschwartz
 *
 * Created on July 22, 2010, 4:46 PM
 */

#ifndef THTTPRESPONSE_H
#define	THTTPRESPONSE_H

#include "TOutputBuffer.h"


class THttpResponse {
protected:
    int status;
    TSocket *sock;
    TOutputBuffer buffer;
public:
    THttpResponse(TSocket *s) {
        sock = s;
    };
    virtual ~THttpResponse(){
        
    };
public:
    void Write(const char *data, int len) {
        buffer.Write(data, len);
    }
    void Print(const char *s) {
        Write((const char *)s, strlen(s));
    }
    void PrintLn(const char *s) {
        Print(s);
        Print("\n");
    }
public:
    void Flush() {
        struct tm tm;
        bzero(&tm, sizeof(tm));
        time_t now = time(NULL);
        gmtime_r(&now, &tm);
        char date_string[256];
        strftime(date_string, 512, "%a, %d %b %Y %H:%M:%S %Z", &tm);
        char line[512];
        sprintf(line, "Date: %s\n", date_string);
        sock->WriteLine("HTTP/1.1 200 OK\n");
        sock->WriteLine(line);
        sock->WriteLine("Content-Type: text/html\n");
        sock->WriteLine("Connection: close\n");
        sprintf(line, "Content-Length: %ld\n\n", buffer.GetSize());
        sock->WriteLine(line);
        sock->Write((const unsigned char *)buffer.GetBuffer(), buffer.GetSize());
    }
};

#endif	/* THTTPRESPONSE_H */
