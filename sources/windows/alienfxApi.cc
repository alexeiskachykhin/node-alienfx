#include <windows.h>
#include "../alienfxApi.h"


_ALIENFX_API DiscoverAlienFxAPI()
{
    HMODULE hLibrary = LoadLibrary(LFX_DLL_NAME);

    _ALIENFX_API api = { 0 };

    if (hLibrary)
    {
        api.IsAvailable = true;
        api.GetVersion = (LFX2GETVERSION)GetProcAddress(hLibrary, LFX_DLL_GETVERSION);
        api.Initialize = (LFX2INITIALIZE)GetProcAddress(hLibrary, LFX_DLL_INITIALIZE);
        api.Release = (LFX2RELEASE)GetProcAddress(hLibrary, LFX_DLL_RELEASE);
        api.Reset = (LFX2RESET)GetProcAddress(hLibrary, LFX_DLL_RESET);
        api.Update = (LFX2UPDATE)GetProcAddress(hLibrary, LFX_DLL_UPDATE);
        api.UpdateDefault = (LFX2UPDATEDEFAULT)GetProcAddress(hLibrary, LFX_DLL_UPDATEDEFAULT);
        api.Light = (LFX2LIGHT)GetProcAddress(hLibrary, LFX_DLL_LIGHT);
        api.ActionColor = (LFX2ACTIONCOLOR)GetProcAddress(hLibrary, LFX_DLL_ACTIONCOLOR);
        api.ActionColorEx = (LFX2ACTIONCOLOREX)GetProcAddress(hLibrary, LFX_DLL_ACTIONCOLOREX);
        api.GetNumDevices = (LFX2GETNUMDEVICES)GetProcAddress(hLibrary, LFX_DLL_GETNUMDEVICES);
        api.GetDeviceDescription = (LFX2GETDEVDESC)GetProcAddress(hLibrary, LFX_DLL_GETDEVDESC);
        api.GetNumLights = (LFX2GETNUMLIGHTS)GetProcAddress(hLibrary, LFX_DLL_GETNUMLIGHTS);
        api.GetLightDescription = (LFX2GETLIGHTDESC)GetProcAddress(hLibrary, LFX_DLL_GETLIGHTDESC);
        api.GetLightLocation = (LFX2GETLIGHTLOC)GetProcAddress(hLibrary, LFX_DLL_GETLIGHTLOC);
        api.GetLightColor = (LFX2GETLIGHTCOL)GetProcAddress(hLibrary, LFX_DLL_GETLIGHTCOL);
        api.SetLightColor = (LFX2SETLIGHTCOL)GetProcAddress(hLibrary, LFX_DLL_SETLIGHTCOL);
        api.SetLightActionColor = (LFX2SETLIGHTACTIONCOLOR)GetProcAddress(hLibrary, LFX_DLL_SETLIGHTACTIONCOLOR);
    }

    return api;
}


_ALIENFX_API ALIENFX_API = DiscoverAlienFxAPI();



