/*
 *  KFileHandler.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KFileHandler.h"
#include "KFileTools.h"
#include "KConsole.h"

#ifndef WIN32
#include <unistd.h> 	// chdir & getcwd
#include <sys/param.h>	// MAXPATHLEN
#else
#include <direct.h>
#endif

vector<string> KFileHandler::current_dir_stack;

// --------------------------------------------------------------------------------------------------------
void KFileHandler::init()
{
#ifndef WIN32
    char buffer[MAXPATHLEN+1];
    getwd(buffer);
#else
	char buffer[256];
	getcwd(buffer, 255);
#endif
    
    current_dir_stack.push_back(buffer);
}

// --------------------------------------------------------------------------------------------------------
bool KFileHandler::changeCurrentDir ( const string & newCurrentDir )
{
    current_dir_stack.pop_back();
    return pushCurrentDir(newCurrentDir);
}

// --------------------------------------------------------------------------------------------------------
bool KFileHandler::pushCurrentDir ( const string & newCurrentDir )
{
    string absPathName = kFileAbsPathName(newCurrentDir);
    
    if (chdir(absPathName.c_str()) == 0)
    {
        current_dir_stack.push_back(absPathName);
        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------
void KFileHandler::popCurrentDir ()
{
    current_dir_stack.pop_back();
    chdir (current_dir_stack.back().c_str());
}

// --------------------------------------------------------------------------------------------------------
string KFileHandler::getCurrentDir ()
{
    return current_dir_stack.back();
}
