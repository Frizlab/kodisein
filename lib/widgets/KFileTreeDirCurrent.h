/*
 *  KFileTreeDirCurrent.h
 *  kodisein
 */

#ifndef __KFileTreeDirCurrent
#define __KFileTreeDirCurrent

#pragma warning(disable:4786)

#include "KFileTreeDir.h"

class KFileTreeDirCurrent : public KFileTreeDir
{
    string	current_dir_path; 	// absolute path of the current ('.') directory
    
    public:
    
                KFileTreeDirCurrent	( const string & );

    string	getAbsPathName		() const { return current_dir_path; }
};

#endif