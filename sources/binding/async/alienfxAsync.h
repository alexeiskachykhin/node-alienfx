#pragma once

#include <node.h>
#include <uv.h>
#include <string>

#include "../../api/alienfxApi.h"


struct BaseBaton {
    uv_work_t Request;
    v8::Persistent<v8::Function> Callback;
    LFX_RESULT Result;
};


struct GetVersionBaton : BaseBaton {
    std::string Version;
};

struct InitializeBaton : BaseBaton {};

struct ReleaseBaton : BaseBaton {};

struct GetNumDevicesBaton : BaseBaton {
    unsigned int NumberOfDevices;
};

struct GetDeviceDescriptionBaton : BaseBaton {
    unsigned int DeviceIndex;
    std::string DeviceModel;
    unsigned char DeviceType;
};

struct GetNumLightsBaton : BaseBaton {
    unsigned int DeviceIndex;
    unsigned int NumberOfLights;
};

struct GetLightDescriptionBaton : BaseBaton {
    unsigned int DeviceIndex;
    unsigned int LightIndex;
    std::string LightDescription;
};

struct GetLightLocationBaton : BaseBaton {
    unsigned int DeviceIndex;
    unsigned int LightIndex;
    LFX_POSITION LightLocation;
};

struct GetLightColorBaton : BaseBaton {
    unsigned int DeviceIndex;
    unsigned int LightIndex;
    LFX_COLOR LightColor;
};



void InitAsyncBindings(v8::Local<v8::Object> exports, v8::Local<v8::Object> module);