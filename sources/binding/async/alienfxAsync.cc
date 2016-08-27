#include <node.h>
#include <uv.h>
#include <string>

#include "../contracts.h"
#include "../async/alienfxAsync.h"
#include "../objects/alienfxObjects.h"
#include "../../api/alienfxApi.h"

using namespace v8;
using namespace std;



void Empty(const FunctionCallbackInfo<Value>& args)
{
    args.GetReturnValue().SetUndefined();
}

Local<Function> GetCallback(const FunctionCallbackInfo<Value>& args, int callbackArgumentIndex)
{
    Local<Function> callback;

    if (callbackArgumentIndex < args.Length())
    {
        callback = Local<Function>::Cast(args[callbackArgumentIndex]);
    }
    else
    {
        callback = FunctionTemplate::New(args.GetIsolate(), Empty)->GetFunction();
    }

    return callback;
}



void GetVersionAsync(uv_work_t* request)
{
    GetVersionBaton* baton = static_cast<GetVersionBaton*>(request->data);

    string version(LFX_DEF_STRING_SIZE, 0);

    LFX_RESULT result = ALIENFX_API.GetVersion(
        const_cast<char*>(version.c_str()), 
        version.size());

    baton->Result = result;
    baton->Version = version;
}

void GetVersionAsyncAfter(uv_work_t* request, int status)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    GetVersionBaton* baton = static_cast<GetVersionBaton*>(request->data);

    Local<Value> error = Null(isolate);
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "result"), Number::New(isolate, baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        data->Set(String::NewFromUtf8(isolate, "version"), String::NewFromUtf8(isolate, baton->Version.c_str()));
    }


    Local<Value> argv[2] { error, data };
    Local<Function>::New(isolate, baton->Callback)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    baton->Callback.Reset();
    
    delete baton;
}

void GetVersion(const FunctionCallbackInfo<Value>& args)
{
    OPTIONAL_FUNCTION(args, 0);


    Local<Function> callback = GetCallback(args, 0);

    GetVersionBaton* baton = new GetVersionBaton();
    baton->Request.data = baton;
    baton->Callback.Reset(Isolate::GetCurrent(), callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetVersionAsync, GetVersionAsyncAfter);

    args.GetReturnValue().SetUndefined();
}



void InitializeAsync(uv_work_t* request)
{
    InitializeBaton* baton = static_cast<InitializeBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.Initialize();

    baton->Result = result;
}

void InitializeAsyncAfter(uv_work_t* request, int status)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    InitializeBaton* baton = static_cast<InitializeBaton*>(request->data);

    Local<Value> error = Null(isolate);
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "result"), Number::New(isolate, baton->Result));

    Local<Value> argv[2] { error, data };
    Local<Function>::New(isolate, baton->Callback)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    baton->Callback.Reset();

    delete baton;
}

void Initialize(const FunctionCallbackInfo<Value>& args)
{
    OPTIONAL_FUNCTION(args, 0);


    Local<Function> callback = GetCallback(args, 0);

    InitializeBaton* baton = new InitializeBaton();
    baton->Request.data = baton;
    baton->Callback.Reset(args.GetIsolate(), callback);

    uv_queue_work(uv_default_loop(), &baton->Request, InitializeAsync, InitializeAsyncAfter);

    args.GetReturnValue().SetUndefined();
}



void ReleaseAsync(uv_work_t* request)
{
    InitializeBaton* baton = static_cast<InitializeBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.Release();

    baton->Result = result;
}

void ReleaseAsyncAfter(uv_work_t* request, int status)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    ReleaseBaton* baton = static_cast<ReleaseBaton*>(request->data);

    Local<Value> error = Null(isolate);
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "result"), Number::New(isolate, baton->Result));

    Local<Value> argv[2] { error, data };
    Local<Function>::New(isolate, baton->Callback)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    baton->Callback.Reset();

    delete baton;
}

void Release(const FunctionCallbackInfo<Value>& args)
{
    OPTIONAL_FUNCTION(args, 0);


    Local<Function> callback = GetCallback(args, 0);

    ReleaseBaton* baton = new ReleaseBaton();
    baton->Request.data = baton;
    baton->Callback.Reset(args.GetIsolate(), callback);

    uv_queue_work(uv_default_loop(), &baton->Request, ReleaseAsync, ReleaseAsyncAfter);

    args.GetReturnValue().SetUndefined();
}



void GetNumDevicesAsync(uv_work_t* request)
{
    GetNumDevicesBaton* baton = static_cast<GetNumDevicesBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.GetNumDevices(&baton->NumberOfDevices);

    baton->Result = result;
}

void GetNumDevicesAsyncAfter(uv_work_t* request, int status)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    GetNumDevicesBaton* baton = static_cast<GetNumDevicesBaton*>(request->data);

    Local<Value> error = Null(isolate);
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "result"), Number::New(isolate, baton->Result));
    
    if (baton->Result == LFX_SUCCESS)
    {
        data->Set(String::NewFromUtf8(isolate, "numberOfDevices"), Number::New(isolate, baton->NumberOfDevices));
    }


    Local<Value> argv[2] { error, data };
    Local<Function>::New(isolate, baton->Callback)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    baton->Callback.Reset();

    delete baton;
}

void GetNumDevices(const FunctionCallbackInfo<Value>& args)
{
    OPTIONAL_FUNCTION(args, 0);


    Local<Function> callback = GetCallback(args, 0);

    GetNumDevicesBaton* baton = new GetNumDevicesBaton();
    baton->Request.data = baton;
    baton->Callback.Reset(args.GetIsolate(), callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetNumDevicesAsync, GetNumDevicesAsyncAfter);

    args.GetReturnValue().SetUndefined();
}



void GetDeviceDescriptionAsync(uv_work_t* request)
{
    GetDeviceDescriptionBaton* baton = static_cast<GetDeviceDescriptionBaton*>(request->data);
    
    string deviceDescription(LFX_DEF_STRING_SIZE, 0);

    LFX_RESULT result = ALIENFX_API.GetDeviceDescription(
        baton->DeviceIndex,
        const_cast<char*>(deviceDescription.c_str()),
        deviceDescription.size(),
        &baton->DeviceType);

    baton->Result = result;
    baton->DeviceModel = deviceDescription;
}

void GetDeviceDescriptionAsyncAfter(uv_work_t* request, int status)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    GetDeviceDescriptionBaton* baton = static_cast<GetDeviceDescriptionBaton*>(request->data);

    Local<Value> error = Null(isolate);
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "result"), Number::New(isolate, baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        data->Set(String::NewFromUtf8(isolate, "model"), String::NewFromUtf8(isolate, baton->DeviceModel.c_str()));
        data->Set(String::NewFromUtf8(isolate, "type"), Number::New(isolate, baton->DeviceType));
    }


    Local<Value> argv[2] { error, data };
    Local<Function>::New(isolate, baton->Callback)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    baton->Callback.Reset();

    delete baton;
}

void GetDeviceDescription(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 1);
    REQUIRE_NUMBER(args, 0);
    OPTIONAL_FUNCTION(args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    Local<Function> callback = GetCallback(args, 1);

    GetDeviceDescriptionBaton* baton = new GetDeviceDescriptionBaton();
    baton->Request.data = baton;
    baton->DeviceIndex = deviceIndex;
    baton->Callback.Reset(args.GetIsolate(), callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetDeviceDescriptionAsync, GetDeviceDescriptionAsyncAfter);

    args.GetReturnValue().SetUndefined();
}



void GetNumLightsAsync(uv_work_t* request)
{
    GetNumLightsBaton* baton = static_cast<GetNumLightsBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.GetNumLights(baton->DeviceIndex, &baton->NumberOfLights);

    baton->Result = result;
}

void GetNumLightsAsyncAfter(uv_work_t* request, int status)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    GetNumLightsBaton* baton = static_cast<GetNumLightsBaton*>(request->data);

    Local<Value> error = Null(isolate);
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "result"), Number::New(isolate, baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        data->Set(String::NewFromUtf8(isolate, "numberOfLights"), Number::New(isolate, baton->NumberOfLights));
    }


    Local<Value> argv[2] { error, data };
    Local<Function>::New(isolate, baton->Callback)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    baton->Callback.Reset();

    delete baton;
}

void GetNumLights(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 1);
    REQUIRE_NUMBER(args, 0);
    OPTIONAL_FUNCTION(args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    Local<Function> callback = GetCallback(args, 1);

    GetNumLightsBaton* baton = new GetNumLightsBaton();
    baton->Request.data = baton;
    baton->DeviceIndex = deviceIndex;
    baton->Callback.Reset(args.GetIsolate(), callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetNumLightsAsync, GetNumLightsAsyncAfter);

    args.GetReturnValue().SetUndefined();
}



void GetLightDescriptionAsync(uv_work_t* request)
{
    GetLightDescriptionBaton* baton = static_cast<GetLightDescriptionBaton*>(request->data);


    string lightDescription(LFX_DEF_STRING_SIZE, 0);

    LFX_RESULT result = ALIENFX_API.GetLightDescription(
        baton->DeviceIndex,
        baton->LightIndex,
        const_cast<char*>(lightDescription.c_str()),
        lightDescription.size());

    baton->Result = result;
    baton->LightDescription = lightDescription;
}

void GetLightDescriptionAsyncAfter(uv_work_t* request, int status)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    GetLightDescriptionBaton* baton = static_cast<GetLightDescriptionBaton*>(request->data);

    Local<Value> error = Null(isolate);
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "result"), Number::New(isolate, baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        data->Set(String::NewFromUtf8(isolate, "lightDescription"), String::NewFromUtf8(isolate, baton->LightDescription.c_str()));
    }


    Local<Value> argv[2] { error, data };
    Local<Function>::New(isolate, baton->Callback)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    baton->Callback.Reset();

    delete baton;
}

void GetLightDescription(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 1);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    OPTIONAL_FUNCTION(args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    Local<Function> callback = GetCallback(args, 2);

    GetLightDescriptionBaton* baton = new GetLightDescriptionBaton();
    baton->Request.data = baton;
    baton->DeviceIndex = deviceIndex;
    baton->LightIndex = lightIndex;
    baton->Callback.Reset(args.GetIsolate(), callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetLightDescriptionAsync, GetLightDescriptionAsyncAfter);

    args.GetReturnValue().SetUndefined();
}



void GetLightLocationAsync(uv_work_t* request)
{
    GetLightLocationBaton* baton = static_cast<GetLightLocationBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.GetLightLocation(
        baton->DeviceIndex, 
        baton->LightIndex, 
        &baton->LightLocation);

    baton->Result = result;
}

void GetLightLocationAsyncAfter(uv_work_t* request, int status)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    GetLightLocationBaton* baton = static_cast<GetLightLocationBaton*>(request->data);

    Local<Value> error = Null(isolate);
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "result"), Number::New(isolate, baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        Local<Object> location = Object::New(isolate);
        PositionToObject(baton->LightLocation, location);

        data->Set(String::NewFromUtf8(isolate, "lightLocation"), location);
    }


    Local<Value> argv[2] { error, data };
    Local<Function>::New(isolate, baton->Callback)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    baton->Callback.Reset();

    delete baton;
}

void GetLightLocation(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 1);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    OPTIONAL_FUNCTION(args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    Local<Function> callback = GetCallback(args, 2);

    GetLightDescriptionBaton* baton = new GetLightDescriptionBaton();
    baton->Request.data = baton;
    baton->DeviceIndex = deviceIndex;
    baton->LightIndex = lightIndex;
    baton->Callback.Reset(args.GetIsolate(), callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetLightDescriptionAsync, GetLightDescriptionAsyncAfter);

    args.GetReturnValue().SetUndefined();
}



void GetLightColorAsync(uv_work_t* request)
{
    GetLightColorBaton* baton = static_cast<GetLightColorBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.GetLightColor(
        baton->DeviceIndex,
        baton->LightIndex,
        &baton->LightColor);

    baton->Result = result;
}

void GetLightColorAsyncAfter(uv_work_t* request, int status)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    GetLightColorBaton* baton = static_cast<GetLightColorBaton*>(request->data);

    Local<Value> error = Null(isolate);
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "result"), Number::New(isolate, baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        Local<Object> color = Object::New(isolate);
        ColorToObject(baton->LightColor, color);

        data->Set(String::NewFromUtf8(isolate, "lightColor"), color);
    }


    Local<Value> argv[2] { error, data };
    Local<Function>::New(isolate, baton->Callback)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    baton->Callback.Reset();

    delete baton;
}

void GetLightColor(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 1);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    OPTIONAL_FUNCTION(args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    Local<Function> callback = GetCallback(args, 2);

    GetLightColorBaton* baton = new GetLightColorBaton();
    baton->Request.data = baton;
    baton->DeviceIndex = deviceIndex;
    baton->LightIndex = lightIndex;
    baton->Callback.Reset(args.GetIsolate(), callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetLightColorAsync, GetLightColorAsyncAfter);

    args.GetReturnValue().SetUndefined();
}




void InitAsyncBindings(Local<Object> exports, Local<Object> module)
{
    NODE_SET_METHOD(exports, "getVersion", GetVersion);
    NODE_SET_METHOD(exports, "initialize", Initialize);
    NODE_SET_METHOD(exports, "release", Release);
    NODE_SET_METHOD(exports, "getNumDevices", GetNumDevices);
    NODE_SET_METHOD(exports, "getDeviceDescription", GetDeviceDescription);
    NODE_SET_METHOD(exports, "getNumLights", GetNumLights);
    NODE_SET_METHOD(exports, "getLightDescription", GetLightDescription);
    NODE_SET_METHOD(exports, "getLightLocation", GetLightLocation);
    NODE_SET_METHOD(exports, "getLightColor", GetLightColor);
}
