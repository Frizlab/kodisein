/*
 *  KObjectModule.h
 *  kodisein
 */

#ifndef __KObjectModule
#define __KObjectModule

#include "KMatrixModule.h"

class KModuleInspector; 

class KObjectModule : public KMatrixModule
{
    INTROSPECTION
    
    protected:
    
    void			createConnectors	();
    
    public:
                                KObjectModule		();
    
    virtual void		display			( int mode );    
    virtual void		expand			() {}
};

#endif

