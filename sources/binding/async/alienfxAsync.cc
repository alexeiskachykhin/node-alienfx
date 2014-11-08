#include <node.h>
#include <string>

#include "../contracts.h"
#include "../async/alienfxAsync.h"
#include "../../api/alienfxApi.h"

using namespace v8;
using namespace std;



Handle<Value> Empty(const Arguments& args)
{
    HandleScope scope;
    return scope.Close(Undefined());
}

Handle<Function> GetCallback(const Arguments& args, int callbackArgumentIndex)
{
    HandleScope scope;
    Handle<Function> callback;

    if (callbackArgumentIndex < args.Length())
    {
        callback = Handle<Function>::Cast(args[callbackArgumentIndex]);
    }
    else
    {
        callback = FunctionTemplate::New(Empty)->GetFunction();
    }

    return scope.Close(callback);
}



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

    OPTIONAL_FUNCTION(scope, args, 0);


    Handle<Function> callback = GetCallback(args, 0);

    InitializeBaton* baton = new InitializeBaton();
    baton->Request.data = baton;
    baton->Callback = Persistent<Function>::New(callback);

    uv_queue_work(uv_default_loop(), &baton->Request, InitializeAsync, InitializeAsyncAfter);

    return scope.Close(Undefined());
}



void ReleaseAsync(uv_work_t* request)
{
    InitializeBaton* baton = static_cast<InitializeBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.Release();

    baton->Result = result;
}

void ReleaseAsyncAfter(uv_work_t* request, int status)
{
    ReleaseBaton* baton = static_cast<ReleaseBaton*>(request->data);

    Handle<Value> error = Null();
    Handle<Object> data = Object::New();
    data->Set(String::NewSymbol("result"), Number::New(baton->Result));

    Handle<Value> argv[2] { error, data };
    baton->Callback->Call(Context::GetCurrent()->Global(), 2, argv);
    baton->Callback.Dispose();

    delete baton;
}

Handle<Value> Release(const Arguments& args)
{
    HandleScope scope;

    OPTIONAL_FUNCTION(scope, args, 0);


    Handle<Function> callback = GetCallback(args, 0);

    ReleaseBaton* baton = new ReleaseBaton();
    baton->Request.data = baton;
    baton->Callback = Persistent<Function>::New(callback);

    uv_queue_work(uv_default_loop(), &baton->Request, ReleaseAsync, ReleaseAsyncAfter);

    return scope.Close(Undefined());
}



void GetNumDevicesAsync(uv_work_t* request)
{
    GetNumDevicesBaton* baton = static_cast<GetNumDevicesBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.GetNumDevices(&baton->NumberOfDevices);

    baton->Result = result;
}

void GetNumDevicesAsyncAfter(uv_work_t* request, int status)
{
    GetNumDevicesBaton* baton = static_cast<GetNumDevicesBaton*>(request->data);

    Handle<Value> error = Null();
    Handle<Object> data = Object::New();
    data->Set(String::NewSymbol("result"), Number::New(baton->Result));
    
    if (baton->Result == LFX_SUCCESS)
    {
        data->Set(String::NewSymbol("numberOfDevices"), Number::New(baton->NumberOfDevices));
    }


    Handle<Value> argv[2] { error, data };
    baton->Callback->Call(Context::GetCurrent()->Global(), 2, argv);
    baton->Callback.Dispose();

    delete baton;
}

Handle<Value> GetNumDevices(const Arguments& args)
{
    HandleScope scope;

    OPTIONAL_FUNCTION(scope, args, 0);


    Handle<Function> callback = GetCallback(args, 0);

    GetNumDevicesBaton* baton = new GetNumDevicesBaton();
    baton->Request.data = baton;
    baton->Callback = Persistent<Function>::New(callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetNumDevicesAsync, GetNumDevicesAsyncAfter);

    return scope.Close(Undefined());
}



void GetDeviceDescriptionAsync(uv_work_t* request)
{
    GetDeviceDescriptionBaton* baton = static_cast<GetDeviceDescriptionBaton*>(request->data);
    
    string deviceDescription(LFX_DEF_STRING_SIZE, 0);

    LFX_RESULT result = ALIENFX_API.GetDeviceDescription(
        baton->DeviceIndex,
        (char *)deviceDescription.c_str(),
        deviceDescription.size(),
        &baton->DeviceType);

    baton->Result = result;
    baton->DeviceModel = deviceDescription;
}

void GetDeviceDescriptionAsyncAfter(uv_work_t* request, int status)
{
    GetDeviceDescriptionBaton* baton = static_cast<GetDeviceDescriptionBaton*>(request->data);

    Handle<Value> error = Null();
    Handle<Object> data = Object::New();
    data->Set(String::NewSymbol("result"), Number::New(baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        data->Set(String::NewSymbol("model"), String::New(baton->DeviceModel.c_str()));
        data->Set(String::NewSymbol("type"), Number::New(baton->DeviceType));
    }


    Handle<Value> argv[2] { error, data };
    baton->Callback->Call(Context::GetCurrent()->Global(), 2, argv);
    baton->Callback.Dispose();

    delete baton;
}

Handle<Value> GetDeviceDescription(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 0);
    OPTIONAL_FUNCTION(scope, args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    Handle<Function> callback = GetCallback(args, 1);

    GetDeviceDescriptionBaton* baton = new GetDeviceDescriptionBaton();
    baton->Request.data = baton;
    baton->DeviceIndex = deviceIndex;
    baton->Callback = Persistent<Function>::New(callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetDeviceDescriptionAsync, GetDeviceDescriptionAsyncAfter);

    return scope.Close(Undefined());
}



void GetNumLightsAsync(uv_work_t* request)
{
    GetNumLightsBaton* baton = static_cast<GetNumLightsBaton*>(request->data);

    LFX_RESULT result = ALIENFX_API.GetNumLights(baton->DeviceIndex, &baton->NumberOfLights);

    baton->Result = result;
}

void GetNumLightsAsyncAfter(uv_work_t* request, int status)
{
    GetNumLightsBaton* baton = static_cast<GetNumLightsBaton*>(request->data);

    Handle<Value> error = Null();
    Handle<Object> data = Object::New();
    data->Set(String::NewSymbol("result"), Number::New(baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        data->Set(String::NewSymbol("numberOfLights"), Number::New(baton->NumberOfLights));
    }


    Handle<Value> argv[2] { error, data };
    baton->Callback->Call(Context::GetCurrent()->Global(), 2, argv);
    baton->Callback.Dispose();

    delete baton;
}

Handle<Value> GetNumLights(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 0);
    OPTIONAL_FUNCTION(scope, args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    Handle<Function> callback = GetCallback(args, 1);

    GetNumLightsBaton* baton = new GetNumLightsBaton();
    baton->Request.data = baton;
    baton->DeviceIndex = deviceIndex;
    baton->Callback = Persistent<Function>::New(callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetNumLightsAsync, GetNumLightsAsyncAfter);

    return scope.Close(Undefined());
}



void GetLightDescriptionAsync(uv_work_t* request)
{
    GetLightDescriptionBaton* baton = static_cast<GetLightDescriptionBaton*>(request->data);


    string lightDescription(LFX_DEF_STRING_SIZE, 0);

    LFX_RESULT result = ALIENFX_API.GetLightDescription(
        baton->DeviceIndex,
        baton->LightIndex,
        (char *)lightDescription.c_str(),
        lightDescription.size());

    baton->Result = result;
    baton->LightDescription = lightDescription;
}

void GetLightDescriptionAsyncAfter(uv_work_t* request, int status)
{
    GetLightDescriptionBaton* baton = static_cast<GetLightDescriptionBaton*>(request->data);

    Handle<Value> error = Null();
    Handle<Object> data = Object::New();
    data->Set(String::NewSymbol("result"), Number::New(baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        data->Set(String::NewSymbol("lightDescription"), String::New(baton->LightDescription.c_str()));
    }


    Handle<Value> argv[2] { error, data };
    baton->Callback->Call(Context::GetCurrent()->Global(), 2, argv);
    baton->Callback.Dispose();

    delete baton;
}

Handle<Value> GetLightDescription(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    OPTIONAL_FUNCTION(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    Handle<Function> callback = GetCallback(args, 2);

    GetLightDescriptionBaton* baton = new GetLightDescriptionBaton();
    baton->Request.data = baton;
    baton->DeviceIndex = deviceIndex;
    baton->LightIndex = lightIndex;
    baton->Callback = Persistent<Function>::New(callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetLightDescriptionAsync, GetLightDescriptionAsyncAfter);

    return scope.Close(Undefined());
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
    GetLightLocationBaton* baton = static_cast<GetLightLocationBaton*>(request->data);

    Handle<Value> error = Null();
    Handle<Object> data = Object::New();
    data->Set(String::NewSymbol("result"), Number::New(baton->Result));

    if (baton->Result == LFX_SUCCESS)
    {
        Handle<Object> location = Object::New();
        location->Set(String::NewSymbol("x"), Number::New(baton->LightLocation.x));
        location->Set(String::NewSymbol("y"), Number::New(baton->LightLocation.y));
        location->Set(String::NewSymbol("z"), Number::New(baton->LightLocation.z));

        data->Set(String::NewSymbol("lightLocation"), location);
    }


    Handle<Value> argv[2] { error, data };
    baton->Callback->Call(Context::GetCurrent()->Global(), 2, argv);
    baton->Callback.Dispose();

    delete baton;
}

Handle<Value> GetLightLocation(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    OPTIONAL_FUNCTION(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    Handle<Function> callback = GetCallback(args, 2);

    GetLightDescriptionBaton* baton = new GetLightDescriptionBaton();
    baton->Request.data = baton;
    baton->DeviceIndex = deviceIndex;
    baton->LightIndex = lightIndex;
    baton->Callback = Persistent<Function>::New(callback);

    uv_queue_work(uv_default_loop(), &baton->Request, GetLightDescriptionAsync, GetLightDescriptionAsyncAfter);

    return scope.Close(Undefined());
}


void InitAsyncBindings(const v8::Handle<v8::Object>& target)
{
    NODE_SET_METHOD(target, "initialize", Initialize);
    NODE_SET_METHOD(target, "release", Release);
    NODE_SET_METHOD(target, "getNumDevices", GetNumDevices);
    NODE_SET_METHOD(target, "getDeviceDescription", GetDeviceDescription);
    NODE_SET_METHOD(target, "getNumLights", GetNumLights);
    NODE_SET_METHOD(target, "getLightDescription", GetLightDescription);
    NODE_SET_METHOD(target, "getLightLocation", GetLightLocation);
}
