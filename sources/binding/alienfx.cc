#include <node.h>

#include "sync/alienfxSync.h"
#include "async/alienfxAsync.h"
#include "objects/alienfxObjects.h"

using namespace v8;


void Init(Local<Object> exports, Local<Object> module) {
    InitAsyncBindings(exports, module);
    InitSyncBindings(exports, module);
    InitObjectBindings(exports, module);
}

NODE_MODULE(alienfx, Init)
