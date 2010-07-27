#include "Silk.h"

bool THttpRequest::ParseRequest(TSocket *s) {
    char buf[512];
    if (!s->ReadLine(firstLine)) {
        return false;
    }
    char *src = firstLine;
    char *dst = &buf[0];
    
    // method
    while (*src != ' ') {
        *dst++ = toupper(*src++);
    }
    *dst = '\0';
    method = new char[strlen(buf) + 1];
    strcpy(method, buf);

    // uri
    while (*src == ' ') src++;
    dst = &buf[0];
    while (*src != ' ') {
        *dst++ = *src++;
    }
    *dst = '\0';
    uri = new char[strlen(buf) + 1];
    strcpy(uri, buf);

    // protocol
    while (*src == ' ') src++;
    dst = &buf[0];
    while (*src) {
        *dst++ = toupper(*src++);
    }
    *dst = '\0';
    protocol = new char[strlen(buf) + 1];
    strcpy(protocol, buf);

    return true;
}

bool THttpRequest::ParseHeaders(TSocket *s) {
    char line[512];
    while (s->ReadLine(line)) {
        if (strlen(line) == 0) {
            return false;
        }
        headers.Append(line);
    }
    return true;
}

THttpRequest::THttpRequest(TSocket *s) {
    alive = false;
    // process method, uri, protocol
    alive = ParseRequest(s) && ParseHeaders(s);
}

THttpRequest::~THttpRequest() {
}

const char *THttpRequest::GetHeader(const char *key) {
    return headers.Find(key);
}

void THttpRequest::Dump() {
    headers.Dump();
}
