/* 
 * File:   TOutputBuffer.h
 * Author: mschwartz
 *
 * Created on July 24, 2010, 8:21 PM
 */

#ifndef TOUTPUTBUFFER_H
#define	TOUTPUTBUFFER_H

class TOutputBuffer {
protected:
    char *buffer;
    long pos, size;
public:
    TOutputBuffer();
    virtual ~TOutputBuffer();
    void Write(const char *data, int len);
    const char *GetBuffer() { return buffer; }
    long GetSize() { return pos; }
};

#endif	/* TOUTPUTBUFFER_H */

