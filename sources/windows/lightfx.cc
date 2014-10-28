#include <windows.h>
#include "../lightfx.h";


_LIGHTFX_API DiscoverLightFxAPI()
{
    HMODULE hLibrary = LoadLibrary(LFX_DLL_NAME);

    _LIGHTFX_API LIGHTFX_API = {0};

    if (hLibrary)
    {
        LIGHTFX_API.IsAvailable = true;
        LIGHTFX_API.Initialize = (LFX2INITIALIZE)GetProcAddress(hLibrary, LFX_DLL_INITIALIZE);
        LIGHTFX_API.Release = (LFX2RELEASE)GetProcAddress(hLibrary, LFX_DLL_RELEASE);
        LIGHTFX_API.Reset = (LFX2RESET)GetProcAddress(hLibrary, LFX_DLL_RESET);
        LIGHTFX_API.Update = (LFX2UPDATE)GetProcAddress(hLibrary, LFX_DLL_UPDATE);
        LIGHTFX_API.Light = (LFX2LIGHT)GetProcAddress(hLibrary, LFX_DLL_LIGHT);
    }

    return LIGHTFX_API;
}


_LIGHTFX_API LIGHTFX_API = DiscoverLightFxAPI();



