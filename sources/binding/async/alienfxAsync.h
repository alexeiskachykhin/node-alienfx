#pragma once

#include <node.h>
#include "../../api/alienfxApi.h"


struct BaseBaton {
    uv_work_t Request;
    v8::Persistent<v8::Function> Callback;
    LFX_RESULT Result;
};

struct InitializeBaton: BaseBaton {};

struct ReleaseBaton : BaseBaton {};



void InitAsyncBindings(const v8::Handle<v8::Object>& target);