/*
 *  KFileTreeDirCurrent.cpp
 *  kodisein
 */

#include "KFileTreeDirCurrent.h"
#include "KFileTools.h"

// --------------------------------------------------------------------------------------------------------
KFileTreeDirCurrent::KFileTreeDirCurrent ( const string & dirName ) : KFileTreeDir (".")
{
    current_dir_path = kFileAbsPathName(dirName);
}
