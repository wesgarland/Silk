#include "Silk.h"

TOutputBuffer::TOutputBuffer() {
    size = 4096;
    pos = 0;
    buffer = new char[size];
}

TOutputBuffer::~TOutputBuffer() {
    delete [] buffer;
}

void TOutputBuffer::Write(const char *data, int len) {
    if (pos + len >= size) {
        size *= 2;
        char *newBuffer = new char[size];
        memcpy(newBuffer, buffer, pos);
        delete [] buffer;
        buffer = newBuffer;
    }
    memcpy(&buffer[pos], data, len);
    pos += len;
    buffer[pos] = '\0';
}
