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
    LFX2ACTIONCOLOREX ActionColorEx;
    LFX2GETNUMDEVICES GetNumDevices;
    LFX2GETDEVDESC GetDeviceDescription;
    LFX2GETNUMLIGHTS GetNumLights;
    LFX2GETLIGHTDESC GetLightDescription;
    LFX2GETLIGHTLOC GetLightLocation;
    LFX2GETLIGHTCOL GetLightColor;
    LFX2SETLIGHTCOL SetLightColor;
    LFX2SETLIGHTACTIONCOLOR SetLightActionColor;
    LFX2SETLIGHTACTIONCOLOREX SetLightActionColorEx;
    LFX2SETTIMING SetTiming;
};

extern _ALIENFX_API ALIENFX_API;