#include <node.h>

#include "../../api/alienfxApi.h"

using namespace v8;
using namespace std;



void ObjectToColor(const Handle<Object> object, LFX_COLOR& color)
{
    color.red = object->Get(String::NewSymbol("red"))->Uint32Value();
    color.green = object->Get(String::NewSymbol("green"))->Uint32Value();
    color.blue = object->Get(String::NewSymbol("blue"))->Uint32Value();
    color.brightness = object->Get(String::NewSymbol("brightness"))->Uint32Value();
}

void ColorToObject(const LFX_COLOR& color, Handle<Object> object)
{
    object->Set(String::NewSymbol("red"), Number::New(color.red));
    object->Set(String::NewSymbol("green"), Number::New(color.green));
    object->Set(String::NewSymbol("blue"), Number::New(color.blue));
    object->Set(String::NewSymbol("brightness"), Number::New(color.brightness));
}

void PositionToObject(const LFX_POSITION& position, Handle<Object> object)
{
    object->Set(String::NewSymbol("x"), Number::New(position.x));
    object->Set(String::NewSymbol("y"), Number::New(position.y));
    object->Set(String::NewSymbol("z"), Number::New(position.z));
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

Handle<Value> CreateResutObject()
{
    HandleScope scope;

    Local<Object> result = Object::New();
    result->Set(String::NewSymbol("SUCCESS"), Number::New(LFX_SUCCESS));
    result->Set(String::NewSymbol("FAILURE"), Number::New(LFX_FAILURE));
    result->Set(String::NewSymbol("NOINIT"), Number::New(LFX_ERROR_NOINIT));
    result->Set(String::NewSymbol("NODEVS"), Number::New(LFX_ERROR_NODEVS));
    result->Set(String::NewSymbol("NOLIGHTS"), Number::New(LFX_ERROR_NOLIGHTS));
    result->Set(String::NewSymbol("BUFFSIZE"), Number::New(LFX_ERROR_BUFFSIZE));

    return scope.Close(result);
}

Handle<Value> CreateActionObject()
{
    HandleScope scope;

    Local<Object> action = Object::New();
    action->Set(String::NewSymbol("MORPH"), Number::New(LFX_ACTION_MORPH));
    action->Set(String::NewSymbol("PULSE"), Number::New(LFX_ACTION_PULSE));
    action->Set(String::NewSymbol("COLOR"), Number::New(LFX_ACTION_COLOR));

    return scope.Close(action);
}



void InitObjectBindings(const v8::Handle<v8::Object>& target)
{
    HandleScope scope;

    Handle<Value> color = CreateColorObject();
    target->Set(String::NewSymbol("Color"), color);

    Handle<Value> brightness = CreateBrightnessObject();
    target->Set(String::NewSymbol("Brightness"), brightness);

    Handle<Value> deviceType = CreateDeviceTypeObject();
    target->Set(String::NewSymbol("DeviceType"), deviceType);

    Handle<Value> position = CreatePositionObject();
    target->Set(String::NewSymbol("Position"), position);

    Handle<Value> result = CreateResutObject();
    target->Set(String::NewSymbol("Result"), result);

    Handle<Value> action = CreateActionObject();
    target->Set(String::NewSymbol("Action"), action);
}
