/*
 *  KFileHandler.h
 *  kodisein
 */
 
#ifndef __KFileHandler
#define __KFileHandler

#include <string>
#include <vector>

using namespace std;

class KFileHandler
{
    protected:
    
    static vector<string> current_dir_stack;

    public:

    static void		init			();
    static bool		changeCurrentDir	( const string & ); // directory handling (OpenGL style:-)
    static bool		pushCurrentDir		( const string & );  
    static void		popCurrentDir		();
    static string	getCurrentDir		();
};

#endif