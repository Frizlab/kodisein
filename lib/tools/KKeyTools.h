/*
 *  KKeyTools.h
 *  kodisein
 */

#ifndef __KKeyTools
#define __KKeyTools

#pragma warning(disable:4786)

#include <string>
#include <SDL_keyboard.h>

using namespace std;

extern const char * SDLKeyNames[];
extern const char * SDLModNames[];

class KPosition;

// --------------------------------------------------------------------------------------------------------
SDLKey 		kKeyGetSymForSymName			( const string & symName );
SDLMod 		kKeyGetModForModName			( const string & modName );
SDL_keysym 	kKeyGetKeysymForKeyName       		( const string & keyName );
string		kKeyGetNameForSym			( SDLKey keySym );
string		kKeyGetNameForMod			( int keyMod );
string		kKeyGetNameForKeysym 			( SDL_keysym keySym );

int 		kKeyGetDisplayWidthForKeyName		( const string & keyName );
int		kKeyGetDisplayWidthForKeySequence	( const string & shortcut );
int 		kKeyDisplayKey 				( const string & keyName,  const KPosition & pos );
void 		kKeyDisplayKeySequence 			( const string & sequence, const KPosition & pos );

#endif
