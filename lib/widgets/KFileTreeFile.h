/*
 *  KFileTreeFile.h
 *  kodisein
 */

#ifndef __KFileTreeFile
#define __KFileTreeFile

#pragma warning(disable:4786)

#include "KFileTreeNode.h"

class KFileTreeDir;

class KFileTreeFile : public KFileTreeNode
{
    INTROSPECTION
    
    public:
    
                        KFileTreeFile 	( const KFileTreeDir *, const string & );
                        
    virtual void	render		();
}; 

#endif
