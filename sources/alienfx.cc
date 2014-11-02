#include <node.h>
#include <v8.h>
#include <string>

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

Handle<Value> UpdateDefault(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.UpdateDefault();

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

Handle<Value> GetNumDevices(const Arguments& args)
{
    HandleScope scope;


    if (args.Length() < 1)
    {
        Local<Value> exception = Exception::TypeError(String::New("Function expects 1 parameter."));
        ThrowException(exception);
    }

    if (!args[0]->IsObject())
    {
        Local<Value> exception = Exception::TypeError(String::New("First argument must be an object."));
        ThrowException(exception);
    }


    unsigned int numberOfDevices = 0;


    LFX_RESULT result = ALIENFX_API.GetNumDevices(&numberOfDevices);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[0]);
        out->Set(String::NewSymbol("result"), Number::New(numberOfDevices));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetDeviceDescription(const Arguments& args)
{
    HandleScope scope;


    if (args.Length() < 2)
    {
        Local<Value> exception = Exception::Error(String::New("Function expects 2 parameters."));
        ThrowException(exception);
    }

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("First argument must be a number."));
        ThrowException(exception);
    }

    if (!args[1]->IsObject())
    {
        Local<Value> exception = Exception::Error(String::New("Second argument must be an object."));
        ThrowException(exception);
    }


    unsigned int deviceIndex = args[0]->Uint32Value();

    unsigned char deviceType = 0;
    std::string deviceDescription(256, 0);


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

Handle<Value> GetNumLights(const Arguments& args)
{
    HandleScope scope;


    if (args.Length() < 2)
    {
        Local<Value> exception = Exception::Error(String::New("Function expects 2 parameters."));
        ThrowException(exception);
    }

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("First argument must be a number."));
        ThrowException(exception);
    }

    if (!args[1]->IsObject())
    {
        Local<Value> exception = Exception::Error(String::New("Second argument must be an object."));
        ThrowException(exception);
    }


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int numberOfLights = 0;


    LFX_RESULT result = ALIENFX_API.GetNumLights(deviceIndex, &numberOfLights);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[1]);
        out->Set(String::NewSymbol("result"), Number::New(numberOfLights));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetLightDescription(const Arguments& args)
{
    HandleScope scope;


    if (args.Length() < 3)
    {
        Local<Value> exception = Exception::Error(String::New("Function expects 3 parameters."));
        ThrowException(exception);
    }

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("First argument must be a number."));
        ThrowException(exception);
    }

    if (!args[1]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("Second argument must be a number."));
        ThrowException(exception);
    }

    if (!args[2]->IsObject())
    {
        Local<Value> exception = Exception::Error(String::New("Third argument must be an object."));
        ThrowException(exception);
    }


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    std::string lightDescription(256, 0);


    LFX_RESULT result = ALIENFX_API.GetLightDescription(
        deviceIndex,
        lightIndex,
        (char *)lightDescription.c_str(),
        lightDescription.size());

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewSymbol("result"), String::New(lightDescription.c_str()));
    }

    return scope.Close(Number::New(result));
}

Handle<Value> GetLightLocation(const Arguments& args)
{
    HandleScope scope;


    if (args.Length() < 3)
    {
        Local<Value> exception = Exception::Error(String::New("Function expects 3 parameters."));
        ThrowException(exception);
    }

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("First argument must be a number."));
        ThrowException(exception);
    }

    if (!args[1]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("Second argument must be a number."));
        ThrowException(exception);
    }

    if (!args[2]->IsObject())
    {
        Local<Value> exception = Exception::Error(String::New("Third argument must be an object."));
        ThrowException(exception);
    }


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    LFX_POSITION lightLocation = {0};


    LFX_RESULT result = ALIENFX_API.GetLightLocation(deviceIndex, lightIndex, &lightLocation);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewSymbol("result"), Number::New(sizeof LFX_POSITION));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetLightColor(const Arguments& args)
{
    HandleScope scope;


    if (args.Length() < 3)
    {
        Local<Value> exception = Exception::Error(String::New("Function expects 3 parameters."));
        ThrowException(exception);
    }

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("First argument must be a number."));
        ThrowException(exception);
    }

    if (!args[1]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("Second argument must be a number."));
        ThrowException(exception);
    }

    if (!args[2]->IsObject())
    {
        Local<Value> exception = Exception::Error(String::New("Third argument must be an object."));
        ThrowException(exception);
    }


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    LFX_COLOR lightColor = { 0 };


    LFX_RESULT result = ALIENFX_API.GetLightColor(deviceIndex, lightIndex, &lightColor);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewSymbol("red"), Number::New(lightColor.red));
        out->Set(String::NewSymbol("green"), Number::New(lightColor.green));
        out->Set(String::NewSymbol("blue"), Number::New(lightColor.blue));
        out->Set(String::NewSymbol("brightness"), Number::New(lightColor.brightness));
    }


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

Handle<Value> CreateDeviceTypeObject()
{
    HandleScope scope;

    Local<Object> deviceType = Object::New();
    deviceType->Set(String::NewSymbol("UNKNOWN"), Number::New(LFX_DEVTYPE_UNKNOWN));
    deviceType->Set(String::NewSymbol("NOTEBOOK"), Number::New(LFX_DEVTYPE_NOTEBOOK));
    deviceType->Set(String::NewSymbol("DESKTOP"), Number::New(LFX_DEVTYPE_DESKTOP));
    deviceType->Set(String::NewSymbol("SERVER"), Number::New(LFX_DEVTYPE_SERVER));
    deviceType->Set(String::NewSymbol("DISPLAY"), Number::New(LFX_DEVTYPE_DISPLAY));
    deviceType->Set(String::NewSymbol("MOUSE"), Number::New(LFX_DEVTYPE_MOUSE));
    deviceType->Set(String::NewSymbol("KEYBOARD"), Number::New(LFX_DEVTYPE_KEYBOARD));
    deviceType->Set(String::NewSymbol("GAMEPAD"), Number::New(LFX_DEVTYPE_GAMEPAD));
    deviceType->Set(String::NewSymbol("SPEAKER"), Number::New(LFX_DEVTYPE_SPEAKER));
    deviceType->Set(String::NewSymbol("OTHER"), Number::New(LFX_DEVTYPE_OTHER));

    return scope.Close(deviceType);
}

Handle<Value> CreatePositionObject()
{
    HandleScope scope;

    Local<Object> position = Object::New();

    // Near Z-plane light definitions
    position->Set(String::NewSymbol("FRONT_LOWER_LEFT"), Number::New(LFX_FRONT_LOWER_LEFT));
    position->Set(String::NewSymbol("FRONT_LOWER_CENTER"), Number::New(LFX_FRONT_LOWER_CENTER));
    position->Set(String::NewSymbol("FRONT_LOWER_RIGHT"), Number::New(LFX_FRONT_LOWER_RIGHT));
    position->Set(String::NewSymbol("FRONT_MIDDLE_LEFT"), Number::New(LFX_FRONT_MIDDLE_LEFT));
    position->Set(String::NewSymbol("FRONT_MIDDLE_CENTER"), Number::New(LFX_FRONT_MIDDLE_CENTER));
    position->Set(String::NewSymbol("FRONT_MIDDLE_RIGHT"), Number::New(LFX_FRONT_MIDDLE_RIGHT));
    position->Set(String::NewSymbol("FRONT_UPPER_LEFT"), Number::New(LFX_FRONT_UPPER_LEFT));
    position->Set(String::NewSymbol("FRONT_UPPER_CENTER"), Number::New(LFX_FRONT_UPPER_CENTER));
    position->Set(String::NewSymbol("FRONT_UPPER_RIGHT"), Number::New(LFX_FRONT_UPPER_RIGHT));

    // Mid Z-plane light definitions
    position->Set(String::NewSymbol("MIDDLE_LOWER_LEFT"), Number::New(LFX_MIDDLE_LOWER_LEFT));
    position->Set(String::NewSymbol("MIDDLE_LOWER_CENTER"), Number::New(LFX_MIDDLE_LOWER_CENTER));
    position->Set(String::NewSymbol("MIDDLE_LOWER_RIGHT"), Number::New(LFX_MIDDLE_LOWER_RIGHT));
    position->Set(String::NewSymbol("MIDDLE_MIDDLE_LEFT"), Number::New(LFX_MIDDLE_MIDDLE_LEFT));
    position->Set(String::NewSymbol("MIDDLE_MIDDLE_CENTER"), Number::New(LFX_MIDDLE_MIDDLE_CENTER));
    position->Set(String::NewSymbol("MIDDLE_MIDDLE_RIGHT"), Number::New(LFX_MIDDLE_MIDDLE_RIGHT));
    position->Set(String::NewSymbol("MIDDLE_UPPER_LEFT"), Number::New(LFX_MIDDLE_UPPER_LEFT));
    position->Set(String::NewSymbol("MIDDLE_UPPER_CENTER"), Number::New(LFX_MIDDLE_UPPER_CENTER));
    position->Set(String::NewSymbol("MIDDLE_UPPER_RIGHT"), Number::New(LFX_MIDDLE_UPPER_RIGHT));

    // Far Z-plane light definitions
    position->Set(String::NewSymbol("REAR_LOWER_LEFT"), Number::New(LFX_REAR_LOWER_LEFT));
    position->Set(String::NewSymbol("REAR_LOWER_CENTER"), Number::New(LFX_REAR_LOWER_CENTER));
    position->Set(String::NewSymbol("REAR_LOWER_RIGHT"), Number::New(LFX_REAR_LOWER_RIGHT));
    position->Set(String::NewSymbol("REAR_MIDDLE_LEFT"), Number::New(LFX_REAR_MIDDLE_LEFT));
    position->Set(String::NewSymbol("REAR_MIDDLE_CENTER"), Number::New(LFX_REAR_MIDDLE_CENTER));
    position->Set(String::NewSymbol("REAR_MIDDLE_RIGHT"), Number::New(LFX_REAR_MIDDLE_RIGHT));
    position->Set(String::NewSymbol("REAR_UPPER_LEFT"), Number::New(LFX_REAR_UPPER_LEFT));
    position->Set(String::NewSymbol("REAR_UPPER_CENTER"), Number::New(LFX_REAR_UPPER_CENTER));
    position->Set(String::NewSymbol("REAR_UPPER_RIGHT"), Number::New(LFX_REAR_UPPER_RIGHT));

    // Combination bit masks
    position->Set(String::NewSymbol("ALL"), Number::New(LFX_ALL));
    position->Set(String::NewSymbol("ALL_RIGHT"), Number::New(LFX_ALL_RIGHT));
    position->Set(String::NewSymbol("ALL_LEFT"), Number::New(LFX_ALL_LEFT));
    position->Set(String::NewSymbol("ALL_UPPER"), Number::New(LFX_ALL_UPPER));
    position->Set(String::NewSymbol("ALL_LOWER"), Number::New(LFX_ALL_LOWER));
    position->Set(String::NewSymbol("ALL_FRONT"), Number::New(LFX_ALL_FRONT));
    position->Set(String::NewSymbol("ALL_REAR"), Number::New(LFX_ALL_REAR));

    return scope.Close(position);
}


void Init(Handle<Object> target) {
    NODE_SET_METHOD(target, "initialize", Initialize);
    NODE_SET_METHOD(target, "release", Release);
    NODE_SET_METHOD(target, "reset", Reset);
    NODE_SET_METHOD(target, "update", Update);
    NODE_SET_METHOD(target, "updateDefault", UpdateDefault);
    NODE_SET_METHOD(target, "light", Light);
    NODE_SET_METHOD(target, "getNumDevices", GetNumDevices);
    NODE_SET_METHOD(target, "getDeviceDescription", GetDeviceDescription);
    NODE_SET_METHOD(target, "getNumLights", GetNumLights);
    NODE_SET_METHOD(target, "getLightDescription", GetLightDescription);
    NODE_SET_METHOD(target, "getLightLocation", GetLightLocation);
    NODE_SET_METHOD(target, "getLightColor", GetLightColor);


    Handle<Value> color = CreateColorObject();
    target->Set(String::NewSymbol("Color"), color);

    Handle<Value> brightness = CreateBrightnessObject();
    target->Set(String::NewSymbol("Brightness"), brightness);

    Handle<Value> deviceType = CreateDeviceTypeObject();
    target->Set(String::NewSymbol("DeviceType"), deviceType);

    Handle<Value> position = CreatePositionObject();
    target->Set(String::NewSymbol("Position"), position);
}

NODE_MODULE(alienfx, Init)
