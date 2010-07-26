/* 
 * File:   THeader.h
 * Author: mschwartz
 *
 * Created on July 22, 2010, 5:20 PM
 */

#ifndef THEADER_H
#define	THEADER_H

struct THeader {
    THeader *next;
    char *key;
    char *value;
    THeader(const char *s);
    THeader(const char *k, const char *v) {
        key = new char[strlen(k)+1];
        strcpy(key, k);
        value = new char[strlen(v)+1];
        strcpy(value, v);
        next = NULL;
    }
    virtual ~THeader();
    void Append(const char *s);
    void Append(const char *key, const char *value);
};

class THeaderList {
protected:
    int count;
    THeader *list;
    THeader *last;
public:

    THeaderList() {
        count = 0;
        list = NULL;
    }

    ~THeaderList() {
        while (list) {
            THeader *next = list->next;
            delete list;
            list = next;
        }
    }

    int GetCount() {
        return count;
    }

    const char *Find(const char *key) {
        for (THeader *p = list; p != NULL; p = p->next) {
            if (!strcmp(p->key, key)) {
                return p->value;
            }
        }
        return NULL;
    }

    void Append(const char *s) {
        THeader *h = new THeader(s);
        if (list == NULL) {
            list = h;
            last = h;
        }
        else {
            last->next = h;
            last = h;
        }
        count++;
    }

    void Append(const char *key, const char *value) {
        THeader *h = new THeader(key, value);
        if (list == NULL) {
            list = h;
            last = h;
        }
        else {
            last->next = h;
            last = h;
        }
        count++;
    }

    void Dump() {
        printf("------ Dump\n");
        for (THeader *h = list; h; h=h->next) {
            printf("%-16s %s\n", h->key, h->value);
        }
    }

    JSObject *GetObjectJS(JSContext *cx) {
        JSObject *o = TInterpreter::NewObject(cx);
        for (THeader *h = list; h; h=h->next) {
            TInterpreter::SetProperty(cx, o, h->key, h->value);
        }
        return o;
    }
};

#endif	/* TLINE_H */

