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

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::TypeError(String::New("First argument must be a number."));
        ThrowException(exception);
    }

    if (!args[1]->IsNumber())
    {
        Local<Value> exception = Exception::TypeError(String::New("Second argument must be a number."));
        ThrowException(exception);
    }


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int colorValue = args[1]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.Light(locationMask, colorValue);

    return scope.Close(Number::New(result));
}


Handle<Value> CreateColorObject()
{
    HandleScope scope;

    Local<Object> color = Object::New();
    color->Set(String::NewSymbol("OFF"), Number::New(LFX_OFF));
    color->Set(String::NewSymbol("BLACK"), Number::New(LFX_BLACK));
    color->Set(String::NewSymbol("RED"), Number::New(LFX_RED));
    color->Set(String::NewSymbol("GREEN"), Number::New(LFX_GREEN));
    color->Set(String::NewSymbol("BLUE"), Number::New(LFX_BLUE));
    color->Set(String::NewSymbol("WHITE"), Number::New(LFX_WHITE));
    color->Set(String::NewSymbol("YELLOW"), Number::New(LFX_YELLOW));
    color->Set(String::NewSymbol("ORANGE"), Number::New(LFX_ORANGE));
    color->Set(String::NewSymbol("PINK"), Number::New(LFX_PINK));
    color->Set(String::NewSymbol("CYAN"), Number::New(LFX_CYAN));

    return scope.Close(color);
}

Handle<Value> CreateBrightnessObject()
{
    HandleScope scope;

    Local<Object> brightness = Object::New();
    brightness->Set(String::NewSymbol("FULL"), Number::New(LFX_FULL_BRIGHTNESS));
    brightness->Set(String::NewSymbol("HALF"), Number::New(LFX_HALF_BRIGHTNESS));
    brightness->Set(String::NewSymbol("MIN"), Number::New(LFX_MIN_BRIGHTNESS));

    return scope.Close(brightness);
}


void Init(Handle<Object> target) {
    NODE_SET_METHOD(target, "initialize", Initialize);
    NODE_SET_METHOD(target, "release", Release);
    NODE_SET_METHOD(target, "reset", Reset);
    NODE_SET_METHOD(target, "update", Update);
    NODE_SET_METHOD(target, "light", Light);

    Handle<Value> color = CreateColorObject();
    target->Set(String::NewSymbol("Color"), color);

    Handle<Value> brightness = CreateBrightnessObject();
    target->Set(String::NewSymbol("Brightness"), brightness);
}

NODE_MODULE(alienfx, Init)
