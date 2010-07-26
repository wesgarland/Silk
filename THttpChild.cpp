#include "Silk.h"

//#define LOGIT

THttpChild::THttpChild(TServerSocket *ss) {
    printf("Construct HttpChld\n");
    sock = ss;
}

THttpChild::~THttpChild() {

}

void THttpChild::Run() {
    pid_t pid = getpid();
    TInterpreter *rt = new TInterpreter();
    while (true) {
        TSocket *s = sock->Accept();
#ifdef LOGIT
        long start = Util::CurrentTimeMillis();
#endif
        THttpRequest *req = new THttpRequest(s);
#ifdef LOGIT
        printf("%d Begin %s from %s\n", pid, req->GetFirstLine(), s->RemoteIP());
#endif
        THttpResponse *res = new THttpResponse(s);
        rt->Run(req, res);
        res->Flush();
        delete res;
        delete req;
        delete s;
#ifdef LOGIT
        long end = Util::CurrentTimeMillis();
        printf("%d Completed in %ld\n", pid, end - start);
#endif
    }
    delete rt;
}
