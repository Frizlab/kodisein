/*
 *  KModuleObjectCylinder.h
 *  kodisein
 */

#ifndef __KModuleObjectCylinder
#define __KModuleObjectCylinder

#include "KObjectModule.h"

class KModuleObjectCylinder : public KObjectModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    void	createConnectors	();
    
    public:
                KModuleObjectCylinder	();
};

#endif

