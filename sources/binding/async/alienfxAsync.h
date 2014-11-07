#pragma once

#include <node.h>
#include "../../api/alienfxApi.h"


struct InitializeBaton {
    uv_work_t Request;
    v8::Persistent<v8::Function> Callback;
    LFX_RESULT Result;
};



void InitAsyncBindings(const v8::Handle<v8::Object>& target);