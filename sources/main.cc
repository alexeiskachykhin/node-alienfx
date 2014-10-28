#include <node.h>
#include <v8.h>
#include "lightfx.h"

using namespace v8;

Handle<Value> Initialize(const Arguments& args) {
    HandleScope scope;
    
    LFX_RESULT result = LIGHTFX_API.Initialize();

    return scope.Close(Number::New(result));
}

Handle<Value> Release(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = LIGHTFX_API.Release();

    return scope.Close(Number::New(result));
}

Handle<Value> Reset(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = LIGHTFX_API.Reset();

    return scope.Close(Number::New(result));
}

Handle<Value> Update(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = LIGHTFX_API.Update();

    return scope.Close(Number::New(result));
}

Handle<Value> Light(const Arguments& args) {
    HandleScope scope;

    if (args.Length() < 2)
    {
        Local<Value> exception = Exception::TypeError(String::New("Function expects 2 parameters."));
        ThrowException(exception);
    }

    if (!args[0]->IsUint32())
    {
        Local<Value> exception = Exception::TypeError(String::New("First argument must be an integer"));
        ThrowException(exception);
    }

    if (!args[1]->IsUint32())
    {
        Local<Value> exception = Exception::TypeError(String::New("Second argument must be an integer"));
        ThrowException(exception);
    }


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int colorValue = args[1]->Uint32Value();

    LFX_RESULT result = LIGHTFX_API.Light(locationMask, colorValue);

    return scope.Close(Number::New(result));
}



void Init(Handle<Object> target) {
    NODE_SET_METHOD(target, "initialize", Initialize);
    NODE_SET_METHOD(target, "release", Release);
    NODE_SET_METHOD(target, "reset", Reset);
    NODE_SET_METHOD(target, "update", Update);
    NODE_SET_METHOD(target, "light", Light);
}

NODE_MODULE(alienfx, Init)
