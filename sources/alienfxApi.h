#pragma once

#include <LFX2.h>


struct _ALIENFX_API {
    bool IsAvailable;
    LFX2GETVERSION GetVersion;
    LFX2INITIALIZE Initialize;
    LFX2RELEASE Release;
    LFX2RESET Reset;
    LFX2UPDATE Update;
    LFX2UPDATEDEFAULT UpdateDefault;
    LFX2LIGHT Light;
    LFX2ACTIONCOLOR ActionColor;
    LFX2GETNUMDEVICES GetNumDevices;
    LFX2GETDEVDESC GetDeviceDescription;
    LFX2GETNUMLIGHTS GetNumLights;
    LFX2GETLIGHTDESC GetLightDescription;
    LFX2GETLIGHTLOC GetLightLocation;
    LFX2GETLIGHTCOL GetLightColor;
    LFX2SETLIGHTCOL SetLightColor;
};

extern _ALIENFX_API ALIENFX_API;