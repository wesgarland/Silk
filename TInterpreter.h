/* 
 * File:   TInterpreter.h
 * Author: mschwartz
 *
 * Created on July 22, 2010, 12:10 PM
 */

#ifndef TINTERPRETER_H
#define	TINTERPRETER_H

#include "Silk.h"

class THttpRequest;
class THttpResponse;

class TInterpreter {
public:
    static char * jsfile;
protected:
#ifndef GPSEE
    static JSClass globalClass;
    static JSRuntime *rt;
    JSObject *globalObject;
#else
    static gpsee_runtime_t     *grt;
    gpsee_realm_t               *realm;
#endif
    JSContext *ctx;

    static void reportError(JSContext *cx, const char *message, JSErrorReport *report);
public:
    TInterpreter();
    virtual ~TInterpreter();
    JSContext *GetContext();
    void ReleaseContext(JSContext *ctx);

    char *Run(THttpRequest *req, THttpResponse *res);
public:
    // SpiderMonkey helper functions
    JSObject *NewObject() {
        return JS_NewObject(ctx, NULL, NULL, NULL);
    }
    jsval String(const char *s) {
        return STRING_TO_JSVAL(JS_NewString(ctx, JS_strdup(ctx, s), strlen(s)));
    }
    void SetProperty(JSObject *o, const char *name, const char *s) {
        jsval v = String(s);
        JS_SetProperty(ctx, o, name, &v);
    }
    void SetProperty(JSObject *o, const char *name, JSObject *oo) {
        jsval v = OBJECT_TO_JSVAL(oo);
        JS_SetProperty(ctx, o, name, &v);
    }
    // static versions
    static JSObject *NewObject(JSContext *ctx) {
        return JS_NewObject(ctx, NULL, NULL, NULL);
    }
    static jsval String(JSContext *ctx, const char *s) {
        return STRING_TO_JSVAL(JS_NewString(ctx, JS_strdup(ctx, s), strlen(s)));
    }
    static void SetProperty(JSContext *ctx, JSObject *o, const char *name, const char *s) {
        jsval v = TInterpreter::String(ctx, s);
        JS_SetProperty(ctx, o, name, &v);
    }
    static void SetProperty(JSContext *ctx, JSObject *o, const char *name, JSObject *oo) {
        jsval v = OBJECT_TO_JSVAL(oo);
        JS_SetProperty(ctx, o, name, &v);
    }
    // Exposed functions
    static JSBool Write(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
};

#endif	/* TINTERPRETER_H */

