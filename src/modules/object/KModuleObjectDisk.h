/*
 *  KModuleObjectDisk.h
 *  kodisein
 */

#ifndef __KModuleObjectDisk
#define __KModuleObjectDisk

#include "KObjectModule.h"

class KModuleObjectDisk : public KObjectModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    void 			createConnectors	();
    
    public:
                                KModuleObjectDisk	();
};

#endif

