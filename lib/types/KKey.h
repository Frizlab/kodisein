/*
 *  KKey.h
 *  kodisein
 */

#ifndef __KKey
#define __KKey

#pragma warning(disable:4786)

#include <SDL_keyboard.h>
#include <string>

using namespace std;

// --------------------------------------------------------------------------------------------------------
struct KKey 
{
    KKey 	( SDL_keysym );

    string 	name;
    char 	character;
    SDLKey	sym;
    int    	mod;
};

#endif