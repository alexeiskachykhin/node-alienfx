#include <windows.h>
#include "../lightfx.h";


HMODULE hLibrary = LoadLibrary(LFX_DLL_NAME);


_LIGHTFX_API LIGHTFX_API = {
    (LFX2INITIALIZE)GetProcAddress(hLibrary, LFX_DLL_INITIALIZE),
    (LFX2RELEASE)GetProcAddress(hLibrary, LFX_DLL_RELEASE),
    (LFX2RESET)GetProcAddress(hLibrary, LFX_DLL_RESET),
    (LFX2UPDATE)GetProcAddress(hLibrary, LFX_DLL_UPDATE),
    (LFX2LIGHT)GetProcAddress(hLibrary, LFX_DLL_LIGHT)
};
