#include "Silk.h"

char *TInterpreter::jsfile;

JSClass TInterpreter::globalClass = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

JSRuntime *TInterpreter::rt = rt = JS_NewRuntime(8L * 1024L * 1024L);

void TInterpreter::reportError(JSContext *cx, const char *message, JSErrorReport *report) {
    fprintf(stderr, "%s:%u:%s\n",
            report->filename ? report->filename : "<no filename>",
            (unsigned int) report->lineno,
            message);
}

TInterpreter::TInterpreter() {
    ctx = JS_NewContext(rt, 8192);
    JS_SetOptions(ctx, JSOPTION_VAROBJFIX);
    JS_SetVersion(ctx, JSVERSION_LATEST);
    JS_SetErrorReporter(ctx, reportError);
    globalObject = JS_NewObject(ctx, &globalClass, NULL, NULL);
    JS_InitStandardClasses(ctx, globalObject);

    SetProperty(globalObject, "abc", "abc property");
    SetProperty(globalObject, "global", globalObject);
}

TInterpreter::~TInterpreter() {
    JS_ClearScope(ctx, globalObject);
    JS_SetGlobalObject(ctx, NULL);
    JS_GC(ctx);
    JS_DestroyContext(ctx);
}

char *TInterpreter::Run(THttpRequest *req, THttpResponse *res) {
    // Set up global req object for JavaScript
    JSObject *jsReq = NewObject();
    SetProperty(jsReq, "abc", "testing req");
    SetProperty(jsReq, "headers", req->GetObjectJS(ctx));
    SetProperty(globalObject, "req", jsReq);

    // Set up global res object for JavaScript
    JSObject *jsRes = NewObject();
    JS_SetContextPrivate(ctx, res);
    JSFunction *w = JS_DefineFunction(ctx, jsRes, "write", TInterpreter::Write, 2, 0);
    SetProperty(globalObject, "res", jsRes);

    jsval rval;
    JS_EvaluateScript(ctx, globalObject, jsfile, strlen(jsfile), "eval", 0, &rval);
    return JS_GetStringBytes(JS_ValueToString(ctx, rval));
}

JSBool TInterpreter::Write(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
    const char *data;
    if (!JS_ConvertArguments(cx, argc, argv, "s", &data)) {
        return JS_FALSE;
    }
    THttpResponse *res = (THttpResponse *) JS_GetContextPrivate(cx);
    res->Print(data);
}

