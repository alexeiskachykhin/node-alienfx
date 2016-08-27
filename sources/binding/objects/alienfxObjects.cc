#include <node.h>

#include "../../api/alienfxApi.h"

using namespace v8;
using namespace std;



void ObjectToColor(Local<Object> object, LFX_COLOR& color)
{
    Isolate* isolate = object->GetIsolate();

    color.red = object->Get(String::NewFromUtf8(isolate, "red"))->Uint32Value();
    color.green = object->Get(String::NewFromUtf8(isolate, "green"))->Uint32Value();
    color.blue = object->Get(String::NewFromUtf8(isolate, "blue"))->Uint32Value();
    color.brightness = object->Get(String::NewFromUtf8(isolate, "brightness"))->Uint32Value();
}

void ColorToObject(const LFX_COLOR& color, Local<Object> object)
{
    Isolate* isolate = object->GetIsolate();

    object->Set(String::NewFromUtf8(isolate, "red"), Number::New(isolate, color.red));
    object->Set(String::NewFromUtf8(isolate, "green"), Number::New(isolate, color.green));
    object->Set(String::NewFromUtf8(isolate, "blue"), Number::New(isolate, color.blue));
    object->Set(String::NewFromUtf8(isolate, "brightness"), Number::New(isolate, color.brightness));
}

void PositionToObject(const LFX_POSITION& position, Local<Object> object)
{
    Isolate* isolate = object->GetIsolate();

    object->Set(String::NewFromUtf8(isolate, "x"), Number::New(isolate, position.x));
    object->Set(String::NewFromUtf8(isolate, "y"), Number::New(isolate, position.y));
    object->Set(String::NewFromUtf8(isolate, "z"), Number::New(isolate, position.z));
}


Local<Value> CreateColorObject(Isolate* isolate)
{
    Local<Object> color = Object::New(isolate);
    color->Set(String::NewFromUtf8(isolate, "OFF"), Number::New(isolate, LFX_OFF));
    color->Set(String::NewFromUtf8(isolate, "BLACK"), Number::New(isolate, LFX_BLACK));
    color->Set(String::NewFromUtf8(isolate, "RED"), Number::New(isolate, LFX_RED));
    color->Set(String::NewFromUtf8(isolate, "GREEN"), Number::New(isolate, LFX_GREEN));
    color->Set(String::NewFromUtf8(isolate, "BLUE"), Number::New(isolate, LFX_BLUE));
    color->Set(String::NewFromUtf8(isolate, "WHITE"), Number::New(isolate, LFX_WHITE));
    color->Set(String::NewFromUtf8(isolate, "YELLOW"), Number::New(isolate, LFX_YELLOW));
    color->Set(String::NewFromUtf8(isolate, "ORANGE"), Number::New(isolate, LFX_ORANGE));
    color->Set(String::NewFromUtf8(isolate, "PINK"), Number::New(isolate, LFX_PINK));
    color->Set(String::NewFromUtf8(isolate, "CYAN"), Number::New(isolate, LFX_CYAN));

    return color;
}

Local<Value> CreateBrightnessObject(Isolate* isolate)
{
    Local<Object> brightness = Object::New(isolate);
    brightness->Set(String::NewFromUtf8(isolate, "FULL"), Number::New(isolate, LFX_FULL_BRIGHTNESS));
    brightness->Set(String::NewFromUtf8(isolate, "HALF"), Number::New(isolate, LFX_HALF_BRIGHTNESS));
    brightness->Set(String::NewFromUtf8(isolate, "MIN"), Number::New(isolate, LFX_MIN_BRIGHTNESS));

    return brightness;
}

Local<Value> CreateDeviceTypeObject(Isolate* isolate)
{
    Local<Object> deviceType = Object::New(isolate);
    deviceType->Set(String::NewFromUtf8(isolate, "UNKNOWN"), Number::New(isolate, LFX_DEVTYPE_UNKNOWN));
    deviceType->Set(String::NewFromUtf8(isolate, "NOTEBOOK"), Number::New(isolate, LFX_DEVTYPE_NOTEBOOK));
    deviceType->Set(String::NewFromUtf8(isolate, "DESKTOP"), Number::New(isolate, LFX_DEVTYPE_DESKTOP));
    deviceType->Set(String::NewFromUtf8(isolate, "SERVER"), Number::New(isolate, LFX_DEVTYPE_SERVER));
    deviceType->Set(String::NewFromUtf8(isolate, "DISPLAY"), Number::New(isolate, LFX_DEVTYPE_DISPLAY));
    deviceType->Set(String::NewFromUtf8(isolate, "MOUSE"), Number::New(isolate, LFX_DEVTYPE_MOUSE));
    deviceType->Set(String::NewFromUtf8(isolate, "KEYBOARD"), Number::New(isolate, LFX_DEVTYPE_KEYBOARD));
    deviceType->Set(String::NewFromUtf8(isolate, "GAMEPAD"), Number::New(isolate, LFX_DEVTYPE_GAMEPAD));
    deviceType->Set(String::NewFromUtf8(isolate, "SPEAKER"), Number::New(isolate, LFX_DEVTYPE_SPEAKER));
    deviceType->Set(String::NewFromUtf8(isolate, "OTHER"), Number::New(isolate, LFX_DEVTYPE_OTHER));

    return deviceType;
}

Local<Value> CreatePositionObject(Isolate* isolate)
{
    Local<Object> position = Object::New(isolate);

    // Near Z-plane light definitions
    position->Set(String::NewFromUtf8(isolate, "FRONT_LOWER_LEFT"), Number::New(isolate, LFX_FRONT_LOWER_LEFT));
    position->Set(String::NewFromUtf8(isolate, "FRONT_LOWER_CENTER"), Number::New(isolate, LFX_FRONT_LOWER_CENTER));
    position->Set(String::NewFromUtf8(isolate, "FRONT_LOWER_RIGHT"), Number::New(isolate, LFX_FRONT_LOWER_RIGHT));
    position->Set(String::NewFromUtf8(isolate, "FRONT_MIDDLE_LEFT"), Number::New(isolate, LFX_FRONT_MIDDLE_LEFT));
    position->Set(String::NewFromUtf8(isolate, "FRONT_MIDDLE_CENTER"), Number::New(isolate, LFX_FRONT_MIDDLE_CENTER));
    position->Set(String::NewFromUtf8(isolate, "FRONT_MIDDLE_RIGHT"), Number::New(isolate, LFX_FRONT_MIDDLE_RIGHT));
    position->Set(String::NewFromUtf8(isolate, "FRONT_UPPER_LEFT"), Number::New(isolate, LFX_FRONT_UPPER_LEFT));
    position->Set(String::NewFromUtf8(isolate, "FRONT_UPPER_CENTER"), Number::New(isolate, LFX_FRONT_UPPER_CENTER));
    position->Set(String::NewFromUtf8(isolate, "FRONT_UPPER_RIGHT"), Number::New(isolate, LFX_FRONT_UPPER_RIGHT));

    // Mid Z-plane light definitions
    position->Set(String::NewFromUtf8(isolate, "MIDDLE_LOWER_LEFT"), Number::New(isolate, LFX_MIDDLE_LOWER_LEFT));
    position->Set(String::NewFromUtf8(isolate, "MIDDLE_LOWER_CENTER"), Number::New(isolate, LFX_MIDDLE_LOWER_CENTER));
    position->Set(String::NewFromUtf8(isolate, "MIDDLE_LOWER_RIGHT"), Number::New(isolate, LFX_MIDDLE_LOWER_RIGHT));
    position->Set(String::NewFromUtf8(isolate, "MIDDLE_MIDDLE_LEFT"), Number::New(isolate, LFX_MIDDLE_MIDDLE_LEFT));
    position->Set(String::NewFromUtf8(isolate, "MIDDLE_MIDDLE_CENTER"), Number::New(isolate, LFX_MIDDLE_MIDDLE_CENTER));
    position->Set(String::NewFromUtf8(isolate, "MIDDLE_MIDDLE_RIGHT"), Number::New(isolate, LFX_MIDDLE_MIDDLE_RIGHT));
    position->Set(String::NewFromUtf8(isolate, "MIDDLE_UPPER_LEFT"), Number::New(isolate, LFX_MIDDLE_UPPER_LEFT));
    position->Set(String::NewFromUtf8(isolate, "MIDDLE_UPPER_CENTER"), Number::New(isolate, LFX_MIDDLE_UPPER_CENTER));
    position->Set(String::NewFromUtf8(isolate, "MIDDLE_UPPER_RIGHT"), Number::New(isolate, LFX_MIDDLE_UPPER_RIGHT));

    // Far Z-plane light definitions
    position->Set(String::NewFromUtf8(isolate, "REAR_LOWER_LEFT"), Number::New(isolate, LFX_REAR_LOWER_LEFT));
    position->Set(String::NewFromUtf8(isolate, "REAR_LOWER_CENTER"), Number::New(isolate, LFX_REAR_LOWER_CENTER));
    position->Set(String::NewFromUtf8(isolate, "REAR_LOWER_RIGHT"), Number::New(isolate, LFX_REAR_LOWER_RIGHT));
    position->Set(String::NewFromUtf8(isolate, "REAR_MIDDLE_LEFT"), Number::New(isolate, LFX_REAR_MIDDLE_LEFT));
    position->Set(String::NewFromUtf8(isolate, "REAR_MIDDLE_CENTER"), Number::New(isolate, LFX_REAR_MIDDLE_CENTER));
    position->Set(String::NewFromUtf8(isolate, "REAR_MIDDLE_RIGHT"), Number::New(isolate, LFX_REAR_MIDDLE_RIGHT));
    position->Set(String::NewFromUtf8(isolate, "REAR_UPPER_LEFT"), Number::New(isolate, LFX_REAR_UPPER_LEFT));
    position->Set(String::NewFromUtf8(isolate, "REAR_UPPER_CENTER"), Number::New(isolate, LFX_REAR_UPPER_CENTER));
    position->Set(String::NewFromUtf8(isolate, "REAR_UPPER_RIGHT"), Number::New(isolate, LFX_REAR_UPPER_RIGHT));

    // Combination bit masks
    position->Set(String::NewFromUtf8(isolate, "ALL"), Number::New(isolate, LFX_ALL));
    position->Set(String::NewFromUtf8(isolate, "ALL_RIGHT"), Number::New(isolate, LFX_ALL_RIGHT));
    position->Set(String::NewFromUtf8(isolate, "ALL_LEFT"), Number::New(isolate, LFX_ALL_LEFT));
    position->Set(String::NewFromUtf8(isolate, "ALL_UPPER"), Number::New(isolate, LFX_ALL_UPPER));
    position->Set(String::NewFromUtf8(isolate, "ALL_LOWER"), Number::New(isolate, LFX_ALL_LOWER));
    position->Set(String::NewFromUtf8(isolate, "ALL_FRONT"), Number::New(isolate, LFX_ALL_FRONT));
    position->Set(String::NewFromUtf8(isolate, "ALL_REAR"), Number::New(isolate, LFX_ALL_REAR));

    return position;
}

Local<Value> CreateResutObject(Isolate* isolate)
{
    Local<Object> result = Object::New(isolate);
    result->Set(String::NewFromUtf8(isolate, "SUCCESS"), Number::New(isolate, LFX_SUCCESS));
    result->Set(String::NewFromUtf8(isolate, "FAILURE"), Number::New(isolate, LFX_FAILURE));
    result->Set(String::NewFromUtf8(isolate, "NOINIT"), Number::New(isolate, LFX_ERROR_NOINIT));
    result->Set(String::NewFromUtf8(isolate, "NODEVS"), Number::New(isolate, LFX_ERROR_NODEVS));
    result->Set(String::NewFromUtf8(isolate, "NOLIGHTS"), Number::New(isolate, LFX_ERROR_NOLIGHTS));
    result->Set(String::NewFromUtf8(isolate, "BUFFSIZE"), Number::New(isolate, LFX_ERROR_BUFFSIZE));

    return result;
}

Local<Value> CreateActionObject(Isolate* isolate)
{
    Local<Object> action = Object::New(isolate);
    action->Set(String::NewFromUtf8(isolate, "MORPH"), Number::New(isolate, LFX_ACTION_MORPH));
    action->Set(String::NewFromUtf8(isolate, "PULSE"), Number::New(isolate, LFX_ACTION_PULSE));
    action->Set(String::NewFromUtf8(isolate, "COLOR"), Number::New(isolate, LFX_ACTION_COLOR));

    return action;
}



void InitObjectBindings(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = exports->GetIsolate();

    Local<Value> color = CreateColorObject(isolate);
    exports->Set(String::NewFromUtf8(isolate, "Color"), color);

    Local<Value> brightness = CreateBrightnessObject(isolate);
    exports->Set(String::NewFromUtf8(isolate, "Brightness"), brightness);

    Local<Value> deviceType = CreateDeviceTypeObject(isolate);
    exports->Set(String::NewFromUtf8(isolate, "DeviceType"), deviceType);

    Local<Value> position = CreatePositionObject(isolate);
    exports->Set(String::NewFromUtf8(isolate, "Position"), position);

    Local<Value> result = CreateResutObject(isolate);
    exports->Set(String::NewFromUtf8(isolate, "Result"), result);

    Local<Value> action = CreateActionObject(isolate);
    exports->Set(String::NewFromUtf8(isolate, "Action"), action);
}
