/*
 *  KModuleObjectBox.h
 *  kodisein
 */

#ifndef __KModuleObjectBox
#define __KModuleObjectBox

#include "KObjectModule.h"

class KModuleObjectBox : public KObjectModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    void 			createConnectors	();
    
    public:
                                KModuleObjectBox 	();
                                    
    virtual void		expand			();
};

#endif

