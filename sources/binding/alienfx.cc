#include <node.h>

#include "sync/alienfxSync.h"
#include "async/alienfxAsync.h"

using namespace v8;


void Init(Handle<Object> target) {
    InitAsyncBindings(target);
    InitSyncBindings(target);
}

NODE_MODULE(alienfx, Init)
