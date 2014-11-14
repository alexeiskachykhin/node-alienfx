#include <node.h>
#include <string>

#include "../contracts.h"
#include "../objects/alienfxObjects.h"
#include "../../api/alienfxApi.h"

using namespace v8;
using namespace std;


Handle<Value> GetVersionSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 0);


    string version(LFX_DEF_STRING_SIZE, 0);


    LFX_RESULT result = ALIENFX_API.GetVersion(
        (char *)version.c_str(),
        version.size());

    if (result == LFX_SUCCESS) {
        Local<Object> out = Local<Object>::Cast(args[0]);
        out->Set(String::NewSymbol("result"), String::New(version.c_str()));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> InitializeSync(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Initialize();

    return scope.Close(Number::New(result));
}

Handle<Value> ReleaseSync(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Release();

    return scope.Close(Number::New(result));
}

Handle<Value> Reset(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Reset();

    return scope.Close(Number::New(result));
}

Handle<Value> Update(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Update();

    return scope.Close(Number::New(result));
}

Handle<Value> UpdateDefault(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.UpdateDefault();

    return scope.Close(Number::New(result));
}

Handle<Value> Light(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int colorValue = args[1]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.Light(locationMask, colorValue);

    return scope.Close(Number::New(result));
}

Handle<Value> ActionColor(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 2);


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int action = args[1]->Uint32Value();
    unsigned int colorValue = args[2]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.ActionColor(locationMask, action, colorValue);

    return scope.Close(Number::New(result));
}

Handle<Value> ActionColorEx(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 4);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 3);


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int action = args[1]->Uint32Value();
    unsigned int primaryColorValue = args[2]->Uint32Value();
    unsigned int secondaryColorValue = args[3]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.ActionColorEx(locationMask, action, primaryColorValue, secondaryColorValue);

    return scope.Close(Number::New(result));
}

Handle<Value> GetNumDevicesSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 0);


    unsigned int numberOfDevices = 0;


    LFX_RESULT result = ALIENFX_API.GetNumDevices(&numberOfDevices);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[0]);
        out->Set(String::NewSymbol("numberOfDevices"), Number::New(numberOfDevices));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetDeviceDescriptionSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_OBJECT(scope, args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned char deviceType = 0;
    string deviceDescription(LFX_DEF_STRING_SIZE, 0);


    LFX_RESULT result = ALIENFX_API.GetDeviceDescription(
        deviceIndex,
        (char *)deviceDescription.c_str(),
        deviceDescription.size(),
        &deviceType);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[1]);
        out->Set(String::NewSymbol("model"), String::New(deviceDescription.c_str()));
        out->Set(String::NewSymbol("type"), Number::New(deviceType));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetNumLightsSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_OBJECT(scope, args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int numberOfLights = 0;


    LFX_RESULT result = ALIENFX_API.GetNumLights(deviceIndex, &numberOfLights);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[1]);
        out->Set(String::NewSymbol("numberOfLights"), Number::New(numberOfLights));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetLightDescriptionSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    string lightDescription(LFX_DEF_STRING_SIZE, 0);


    LFX_RESULT result = ALIENFX_API.GetLightDescription(
        deviceIndex,
        lightIndex,
        (char *)lightDescription.c_str(),
        lightDescription.size());

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewSymbol("lightDescription"), String::New(lightDescription.c_str()));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetLightLocationSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    LFX_POSITION lightLocation{ 0 };


    LFX_RESULT result = ALIENFX_API.GetLightLocation(deviceIndex, lightIndex, &lightLocation);

    if (result == LFX_SUCCESS)
    {
        Handle<Object> location = Object::New();
        PositionToObject(lightLocation, location);

        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewSymbol("lightLocation"), location);
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetLightColorSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    LFX_COLOR lightColor{ 0 };


    LFX_RESULT result = ALIENFX_API.GetLightColor(deviceIndex, lightIndex, &lightColor);

    if (result == LFX_SUCCESS)
    {
        Handle<Object> color = Object::New();
        ColorToObject(lightColor, color);

        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewSymbol("lightColor"), color);
    }

    return scope.Close(Number::New(result));
}

Handle<Value> SetLightColor(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    Local<Object> color = Local<Object>::Cast(args[2]);

    LFX_COLOR lightColor{ 0 };
    ObjectToColor(color, lightColor);


    LFX_RESULT result = ALIENFX_API.SetLightColor(deviceIndex, lightIndex, &lightColor);

    return scope.Close(Number::New(result));
}

Handle<Value> SetLightActionColor(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 4);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 2);
    REQUIRE_OBJECT(scope, args, 3);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    unsigned int action = args[2]->Uint32Value();
    Local<Object> color = Local<Object>::Cast(args[3]);

    LFX_COLOR lightColor{ 0 };
    ObjectToColor(color, lightColor);

    LFX_RESULT result = ALIENFX_API.SetLightActionColor(deviceIndex, lightIndex, action, &lightColor);

    return scope.Close(Number::New(result));
}

Handle<Value> SetLightActionColorEx(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 5);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 2);
    REQUIRE_OBJECT(scope, args, 3);
    REQUIRE_OBJECT(scope, args, 4);


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

    return scope.Close(Number::New(result));
}

Handle<Value> SetTiming(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 0);


    int timing = args[0]->Int32Value();

    LFX_RESULT result = ALIENFX_API.SetTiming(timing);

    return scope.Close(Number::New(result));
}



void InitSyncBindings(const v8::Handle<v8::Object>& target)
{
    NODE_SET_METHOD(target, "getVersionSync", GetVersionSync);
    NODE_SET_METHOD(target, "initializeSync", InitializeSync);
    NODE_SET_METHOD(target, "releaseSync", ReleaseSync);
    NODE_SET_METHOD(target, "reset", Reset);
    NODE_SET_METHOD(target, "update", Update);
    NODE_SET_METHOD(target, "updateDefault", UpdateDefault);
    NODE_SET_METHOD(target, "light", Light);
    NODE_SET_METHOD(target, "actionColor", ActionColor);
    NODE_SET_METHOD(target, "actionColorEx", ActionColorEx);
    NODE_SET_METHOD(target, "getNumDevicesSync", GetNumDevicesSync);
    NODE_SET_METHOD(target, "getDeviceDescriptionSync", GetDeviceDescriptionSync);
    NODE_SET_METHOD(target, "getNumLightsSync", GetNumLightsSync);
    NODE_SET_METHOD(target, "getLightDescriptionSync", GetLightDescriptionSync);
    NODE_SET_METHOD(target, "getLightLocationSync", GetLightLocationSync);
    NODE_SET_METHOD(target, "getLightColorSync", GetLightColorSync);
    NODE_SET_METHOD(target, "setLightColor", SetLightColor);
    NODE_SET_METHOD(target, "setLightActionColor", SetLightActionColor);
    NODE_SET_METHOD(target, "setLightActionColorEx", SetLightActionColorEx);
    NODE_SET_METHOD(target, "setTiming", SetTiming);


    target->Set(String::NewSymbol("isAvailable"), Boolean::New(ALIENFX_API.IsAvailable));
}
