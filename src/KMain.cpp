/*
 *  KMain.cpp
 *  kodisein
 */

#include "KMain.h"
#include "KController.h"
#include "KStringTools.h"
#include "KFileTools.h"

#include <SDL.h>

#ifndef WIN32
#import <sys/param.h> // for MAXPATHLEN 
#else
#define MAXPATHLEN MAX_PATH
#endif

// --------------------------------------------------------------------------------------------------------

#include <hash_map>
#include "KConsole.h"

void test()
{
	typedef hash_map<const char*, const char *> Hash;
	Hash h;
	string c("c");
	string * b = new string("b");
	KConsole::dbg("hash: %p", h);
	h[c.c_str()] = "hallo c";
	h[(new string(*b))->c_str()] = "HALLO B";

	delete b;

	Hash::iterator result;

	result = h.find("a");
	if (result != h.end())
    {
		KConsole::dbg("found value for key %s: %s", "a", (*result).second);
    }

	result = h.find("b");
	if (result != h.end())
    {
		KConsole::dbg("found value for key %s: %s", "b", (*result).second);
    }

	result = h.find("c");
	if (result != h.end())
    {
		KConsole::dbg("found value for key %s: %s", "c", (*result).second);
    }

	result = h.begin();
	while (result != h.end())
	{
		KConsole::dbg("%s: %p", (*result).first, (*result).second);
		result++;
	}
}

KController Controller;

// --------------------------------------------------------------------------------------------------------
int SDL_main (int argc, char* argv[])
{
    for (int index = 1; index < argc; index++)
    { 
        // parse arguments the simple way
        string argString = argv[index];
        if (string(argString.substr(0,4)).compare("-psn") != 0) // if not finder lauch argument -> try to open file
        {	
            char * buffer = (char*)malloc(MAXPATHLEN+1);
            SDL_Event user_event; 
            user_event.type = SDL_USEREVENT;
            user_event.user.code  = KDL_NOTIFICATION_TYPE_APPLICATION_OPEN_FILE;
            user_event.user.data1 = strncpy(buffer, argv[index], MAXPATHLEN);
            SDL_PushEvent(&user_event);
        }
    }
    
#if defined(__APPLE__) && defined(__MACH__)
    // OpenGL attributes
    // OpenGL attributes
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
#endif

    Controller.app_name = argv[0];

    // init controller
    if (Controller.init())
    {
		Controller.mainLoop(); // controller does the rest
    }
    else
    {
        SDL_Quit();
        return -3;
    }
    
    // clean up the SDL library
    SDL_Quit();
    
    return 0;
}

