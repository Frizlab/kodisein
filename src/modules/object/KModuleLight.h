/*
 *  KModuleLight.h
 *  kodisein
 */

#ifndef __KModuleLight
#define __KModuleLight

#include "KMatrixModule.h"
#include "KLight.h"

class KModuleLight : public KMatrixModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    void			createConnectors	();

    public:
    
                                KModuleLight		();
    
    virtual void		initLight		( GLenum );
    virtual void		display			( int );
    virtual void		displayConnectors	( int );
};

#endif