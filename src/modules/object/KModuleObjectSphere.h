/*
 *  KModuleObjectSphere.h
 *  kodisein
 */

#ifndef __KModuleObjectSphere
#define __KModuleObjectSphere

#include "KObjectModule.h"

class KModuleObjectSphere : public KObjectModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    void 			createConnectors	();
    
    public:
                                KModuleObjectSphere	();
};

#endif

