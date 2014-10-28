#pragma once

#include <LFX2.h>;


struct _LIGHTFX_API {
    bool IsAvailable;
    LFX2INITIALIZE Initialize;
    LFX2RELEASE Release;
    LFX2RESET Reset;
    LFX2UPDATE Update;
    LFX2LIGHT Light;
};

extern _LIGHTFX_API LIGHTFX_API;