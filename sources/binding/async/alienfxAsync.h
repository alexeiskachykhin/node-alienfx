#pragma once

#include <node.h>
#include <string>

#include "../../api/alienfxApi.h"


struct BaseBaton {
    uv_work_t Request;
    v8::Persistent<v8::Function> Callback;
    LFX_RESULT Result;
};

struct InitializeBaton: BaseBaton {};

struct ReleaseBaton : BaseBaton {};

struct GetNumDevicesBaton : BaseBaton {
    unsigned int NumberOfDevices;
};

struct GetDeviceDescriptionBaton : BaseBaton {
    unsigned int DeviceIndex;
    std::string DeviceModel;
    unsigned char DeviceType;
};



void InitAsyncBindings(const v8::Handle<v8::Object>& target);