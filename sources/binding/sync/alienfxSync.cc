#include <node.h>
#include <string>

#include "../contracts.h"
#include "../objects/alienfxObjects.h"
#include "../../api/alienfxApi.h"

using namespace v8;
using namespace std;


void GetVersionSync(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    REQUIRE_NUMBER_OF_ARGUMENTS(args, 1);
    REQUIRE_OBJECT(args, 0);


    string version(LFX_DEF_STRING_SIZE, 0);


    LFX_RESULT result = ALIENFX_API.GetVersion(
        const_cast<char*>(version.c_str()),
        version.size());

    if (result == LFX_SUCCESS) {
        Local<Object> out = Local<Object>::Cast(args[0]);
        out->Set(String::NewFromUtf8(isolate, "result"), String::NewFromUtf8(isolate, version.c_str()));
    }

    args.GetReturnValue().Set(Number::New(isolate, result));
}

void InitializeSync(const FunctionCallbackInfo<Value>& args)
{
    LFX_RESULT result = ALIENFX_API.Initialize();

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void ReleaseSync(const FunctionCallbackInfo<Value>& args)
{
    LFX_RESULT result = ALIENFX_API.Release();

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void Reset(const FunctionCallbackInfo<Value>& args)
{
    LFX_RESULT result = ALIENFX_API.Reset();

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void Update(const FunctionCallbackInfo<Value>& args)
{
    LFX_RESULT result = ALIENFX_API.Update();

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void UpdateDefault(const FunctionCallbackInfo<Value>& args)
{
    LFX_RESULT result = ALIENFX_API.UpdateDefault();

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void Light(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 2);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int colorValue = args[1]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.Light(locationMask, colorValue);

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void ActionColor(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 3);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    REQUIRE_NUMBER(args, 2);


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int action = args[1]->Uint32Value();
    unsigned int colorValue = args[2]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.ActionColor(locationMask, action, colorValue);

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void ActionColorEx(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 4);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    REQUIRE_NUMBER(args, 2);
    REQUIRE_NUMBER(args, 3);


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int action = args[1]->Uint32Value();
    unsigned int primaryColorValue = args[2]->Uint32Value();
    unsigned int secondaryColorValue = args[3]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.ActionColorEx(locationMask, action, primaryColorValue, secondaryColorValue);

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void GetNumDevicesSync(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    REQUIRE_NUMBER_OF_ARGUMENTS(args, 1);
    REQUIRE_OBJECT(args, 0);


    unsigned int numberOfDevices = 0;


    LFX_RESULT result = ALIENFX_API.GetNumDevices(&numberOfDevices);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[0]);
        out->Set(String::NewFromUtf8(isolate, "numberOfDevices"), Number::New(isolate, numberOfDevices));
    }

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void GetDeviceDescriptionSync(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    REQUIRE_NUMBER_OF_ARGUMENTS(args, 2);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_OBJECT(args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned char deviceType = 0;
    string deviceDescription(LFX_DEF_STRING_SIZE, 0);


    LFX_RESULT result = ALIENFX_API.GetDeviceDescription(
        deviceIndex,
        const_cast<char*>(deviceDescription.c_str()),
        deviceDescription.size(),
        &deviceType);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[1]);
        out->Set(String::NewFromUtf8(isolate, "model"), String::NewFromUtf8(isolate, deviceDescription.c_str()));
        out->Set(String::NewFromUtf8(isolate, "type"), Number::New(isolate, deviceType));
    }

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void GetNumLightsSync(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    REQUIRE_NUMBER_OF_ARGUMENTS(args, 2);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_OBJECT(args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int numberOfLights = 0;


    LFX_RESULT result = ALIENFX_API.GetNumLights(deviceIndex, &numberOfLights);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[1]);
        out->Set(String::NewFromUtf8(isolate, "numberOfLights"), Number::New(isolate, numberOfLights));
    }

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void GetLightDescriptionSync(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    REQUIRE_NUMBER_OF_ARGUMENTS(args, 3);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    REQUIRE_OBJECT(args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    string lightDescription(LFX_DEF_STRING_SIZE, 0);


    LFX_RESULT result = ALIENFX_API.GetLightDescription(
        deviceIndex,
        lightIndex,
        const_cast<char*>(lightDescription.c_str()),
        lightDescription.size());

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewFromUtf8(isolate, "lightDescription"), String::NewFromUtf8(isolate, lightDescription.c_str()));
    }

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void GetLightLocationSync(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    REQUIRE_NUMBER_OF_ARGUMENTS(args, 3);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    REQUIRE_OBJECT(args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    LFX_POSITION lightLocation{ 0 };


    LFX_RESULT result = ALIENFX_API.GetLightLocation(deviceIndex, lightIndex, &lightLocation);

    if (result == LFX_SUCCESS)
    {
        Local<Object> location = Object::New(isolate);
        PositionToObject(lightLocation, location);

        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewFromUtf8(isolate, "lightLocation"), location);
    }

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void GetLightColorSync(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    REQUIRE_NUMBER_OF_ARGUMENTS(args, 3);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    REQUIRE_OBJECT(args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    LFX_COLOR lightColor{ 0 };


    LFX_RESULT result = ALIENFX_API.GetLightColor(deviceIndex, lightIndex, &lightColor);

    if (result == LFX_SUCCESS)
    {
        Local<Object> color = Object::New(isolate);
        ColorToObject(lightColor, color);

        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewFromUtf8(isolate, "lightColor"), color);
    }

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void SetLightColor(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 3);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    REQUIRE_OBJECT(args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    Local<Object> color = Local<Object>::Cast(args[2]);

    LFX_COLOR lightColor{ 0 };
    ObjectToColor(color, lightColor);


    LFX_RESULT result = ALIENFX_API.SetLightColor(deviceIndex, lightIndex, &lightColor);

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void SetLightActionColor(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 4);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    REQUIRE_NUMBER(args, 2);
    REQUIRE_OBJECT(args, 3);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    unsigned int action = args[2]->Uint32Value();
    Local<Object> color = Local<Object>::Cast(args[3]);

    LFX_COLOR lightColor{ 0 };
    ObjectToColor(color, lightColor);

    LFX_RESULT result = ALIENFX_API.SetLightActionColor(deviceIndex, lightIndex, action, &lightColor);

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void SetLightActionColorEx(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 5);
    REQUIRE_NUMBER(args, 0);
    REQUIRE_NUMBER(args, 1);
    REQUIRE_NUMBER(args, 2);
    REQUIRE_OBJECT(args, 3);
    REQUIRE_OBJECT(args, 4);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    unsigned int action = args[2]->Uint32Value();
    Local<Object> primaryColor = Local<Object>::Cast(args[3]);
    Local<Object> secondaryColor = Local<Object>::Cast(args[4]);

    LFX_COLOR primaryLightColor{ 0 };
    ObjectToColor(primaryColor, primaryLightColor);

    LFX_COLOR secondaryLightColor{ 0 };
    ObjectToColor(secondaryColor, secondaryLightColor);


    LFX_RESULT result = ALIENFX_API.SetLightActionColorEx(deviceIndex, lightIndex, action, &primaryLightColor, &secondaryLightColor);

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}

void SetTiming(const FunctionCallbackInfo<Value>& args)
{
    REQUIRE_NUMBER_OF_ARGUMENTS(args, 1);
    REQUIRE_NUMBER(args, 0);


    int timing = args[0]->Int32Value();

    LFX_RESULT result = ALIENFX_API.SetTiming(timing);

    args.GetReturnValue().Set(Number::New(args.GetIsolate(), result));
}



void InitSyncBindings(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = exports->GetIsolate();

    NODE_SET_METHOD(exports, "getVersionSync", GetVersionSync);
    NODE_SET_METHOD(exports, "initializeSync", InitializeSync);
    NODE_SET_METHOD(exports, "releaseSync", ReleaseSync);
    NODE_SET_METHOD(exports, "reset", Reset);
    NODE_SET_METHOD(exports, "update", Update);
    NODE_SET_METHOD(exports, "updateDefault", UpdateDefault);
    NODE_SET_METHOD(exports, "light", Light);
    NODE_SET_METHOD(exports, "actionColor", ActionColor);
    NODE_SET_METHOD(exports, "actionColorEx", ActionColorEx);
    NODE_SET_METHOD(exports, "getNumDevicesSync", GetNumDevicesSync);
    NODE_SET_METHOD(exports, "getDeviceDescriptionSync", GetDeviceDescriptionSync);
    NODE_SET_METHOD(exports, "getNumLightsSync", GetNumLightsSync);
    NODE_SET_METHOD(exports, "getLightDescriptionSync", GetLightDescriptionSync);
    NODE_SET_METHOD(exports, "getLightLocationSync", GetLightLocationSync);
    NODE_SET_METHOD(exports, "getLightColorSync", GetLightColorSync);
    NODE_SET_METHOD(exports, "setLightColor", SetLightColor);
    NODE_SET_METHOD(exports, "setLightActionColor", SetLightActionColor);
    NODE_SET_METHOD(exports, "setLightActionColorEx", SetLightActionColorEx);
    NODE_SET_METHOD(exports, "setTiming", SetTiming);


    exports->Set(String::NewFromUtf8(isolate, "isAvailable"), Boolean::New(isolate, ALIENFX_API.IsAvailable));
}
