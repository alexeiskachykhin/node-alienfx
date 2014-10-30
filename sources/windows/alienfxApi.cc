#include <windows.h>
#include "../alienfxApi.h"


_ALIENFX_API DiscoverAlienFxAPI()
{
    HMODULE hLibrary = LoadLibrary(LFX_DLL_NAME);

    _ALIENFX_API api = { 0 };

    if (hLibrary)
    {
        api.IsAvailable = true;
        api.Initialize = (LFX2INITIALIZE)GetProcAddress(hLibrary, LFX_DLL_INITIALIZE);
        api.Release = (LFX2RELEASE)GetProcAddress(hLibrary, LFX_DLL_RELEASE);
        api.Reset = (LFX2RESET)GetProcAddress(hLibrary, LFX_DLL_RESET);
        api.Update = (LFX2UPDATE)GetProcAddress(hLibrary, LFX_DLL_UPDATE);
        api.UpdateDefault = (LFX2UPDATEDEFAULT)GetProcAddress(hLibrary, LFX_DLL_UPDATEDEFAULT);
        api.Light = (LFX2LIGHT)GetProcAddress(hLibrary, LFX_DLL_LIGHT);
    }

    return api;
}


_ALIENFX_API ALIENFX_API = DiscoverAlienFxAPI();



