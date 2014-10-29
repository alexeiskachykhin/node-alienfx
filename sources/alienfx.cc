#include <node.h>
#include <v8.h>
#include "alienfxApi.h"

using namespace v8;

Handle<Value> Initialize(const Arguments& args) {
    HandleScope scope;
    
    LFX_RESULT result = ALIENFX_API.Initialize();

    return scope.Close(Number::New(result));
}

Handle<Value> Release(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Release();

    return scope.Close(Number::New(result));
}

Handle<Value> Reset(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Reset();

    return scope.Close(Number::New(result));
}

Handle<Value> Update(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Update();

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
        Local<Value> exception = Exception::TypeError(String::New("First argument must be an integer."));
        ThrowException(exception);
    }

    if (!args[1]->IsUint32())
    {
        Local<Value> exception = Exception::TypeError(String::New("Second argument must be an integer."));
        ThrowException(exception);
    }


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int colorValue = args[1]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.Light(locationMask, colorValue);

    return scope.Close(Number::New(result));
}


Handle<Value> CreateColorsObject() 
{
    HandleScope scope;

    Local<Object> colors = Object::New();
    colors->Set(String::NewSymbol("OFF"), Number::New(LFX_OFF));
    colors->Set(String::NewSymbol("BLACK"), Number::New(LFX_BLACK));
    colors->Set(String::NewSymbol("RED"), Number::New(LFX_RED));
    colors->Set(String::NewSymbol("GREEN"), Number::New(LFX_GREEN));
    colors->Set(String::NewSymbol("BLUE"), Number::New(LFX_BLUE));
    colors->Set(String::NewSymbol("WHITE"), Number::New(LFX_WHITE));
    colors->Set(String::NewSymbol("YELLOW"), Number::New(LFX_YELLOW));
    colors->Set(String::NewSymbol("ORANGE"), Number::New(LFX_ORANGE));
    colors->Set(String::NewSymbol("PINK"), Number::New(LFX_PINK));
    colors->Set(String::NewSymbol("CYAN"), Number::New(LFX_CYAN));

    return scope.Close(colors);
}


void Init(Handle<Object> target) {
    NODE_SET_METHOD(target, "initialize", Initialize);
    NODE_SET_METHOD(target, "release", Release);
    NODE_SET_METHOD(target, "reset", Reset);
    NODE_SET_METHOD(target, "update", Update);
    NODE_SET_METHOD(target, "light", Light);

    Handle<Value> colors = CreateColorsObject();
    target->Set(String::NewSymbol("Colors"), colors);
}

NODE_MODULE(alienfx, Init)
