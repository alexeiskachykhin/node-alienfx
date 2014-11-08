#pragma once

#include <node.h>
#include "../../api/alienfxApi.h"


void ObjectToColor(const v8::Handle<v8::Object> object, LFX_COLOR& color);
void ColorToObject(const LFX_COLOR& color, v8::Handle<v8::Object> object);
void PositionToObject(const LFX_POSITION& position, v8::Handle<v8::Object> object);

void InitObjectBindings(const v8::Handle<v8::Object>& target);