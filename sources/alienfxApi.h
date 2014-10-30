#pragma once

#include <LFX2.h>


struct _ALIENFX_API {
    bool IsAvailable;
    LFX2INITIALIZE Initialize;
    LFX2RELEASE Release;
    LFX2RESET Reset;
    LFX2UPDATE Update;
    LFX2UPDATEDEFAULT UpdateDefault;
    LFX2LIGHT Light;
};

extern _ALIENFX_API ALIENFX_API;