/*
 *  KPartcile.cpp
 *  kodisein
 */

#include "KParticle.h"

#include <SDL.h>

KDL_CLASS_INTROSPECTION_1 (KParticle, KMatrix)

// --------------------------------------------------------------------------------------------------------
KParticle::KParticle () : KMatrix ()
{
    birth_time = SDL_GetTicks();
}
