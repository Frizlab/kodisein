/*
 *  KKey.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KKey.h"
#include "KKeyTools.h"

// --------------------------------------------------------------------------------------------------------
KKey::KKey ( SDL_keysym keysym )
{
    name = kKeyGetNameForKeysym(keysym);
    character = 0;
    if ( (keysym.unicode & 0xFF80) == 0 ) 
    {
        character = keysym.unicode & 0x7F;
    }
    sym = keysym.sym;
    mod = keysym.mod;
}

