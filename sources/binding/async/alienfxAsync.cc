#include <node.h> 

#include "../contracts.h"
#include "../async/alienfxAsync.h"
#include "../../api/alienfxApi.h"

using namespace v8;



void InitializeAsync(uv_work_t* request)
{
    InitializeBaton* baton = static_cast<InitializeBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.Initialize();

    baton->Result = result;
}

void InitializeAsyncAfter(uv_work_t* request, int status)
{
    InitializeBaton* baton = static_cast<InitializeBaton*>(request->data);

    Handle<Value> error = Null();
    Handle<Object> data = Object::New();
    data->Set(String::NewSymbol("result"), Number::New(baton->Result));

    Handle<Value> argv[2] { error, data };
    baton->Callback->Call(Context::GetCurrent()->Global(), 2, argv);
    baton->Callback.Dispose();

    delete baton;
}

Handle<Value> Initialize(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 1);
    REQUIRE_FUNCTION(scope, args, 0);


    Handle<Function> callback = Handle<Function>::Cast(args[0]);

    InitializeBaton* baton = new InitializeBaton();
    baton->Request.data = baton;
    baton->Callback = Persistent<Function>::New(callback);

    uv_queue_work(uv_default_loop(), &baton->Request, InitializeAsync, InitializeAsyncAfter);

    return scope.Close(Undefined());
}



void InitAsyncBindings(const v8::Handle<v8::Object>& target)
{
    NODE_SET_METHOD(target, "initialize", Initialize);
}
