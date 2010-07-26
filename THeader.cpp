#include "Silk.h"

THeader::THeader(const char *s) {
    char k[512], v[512];
    const char *src = s;
    char *dst = &k[0];
    while (*src != ':') {
        *dst++ = *src++;
    }
    *dst = '\0';
    src++;

    dst = &v[0];
    while (*src == ' ') src++;
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
    key = new char[strlen(k) + 1];
    strcpy(key, k);
    value = new char[strlen(v) + 1];
    strcpy(value, v);
    next = NULL;
}

THeader::~THeader() {
    delete[] key;
    delete[] value;
}

