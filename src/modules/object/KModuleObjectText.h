/*
 *  KModuleObjectText.h
 *  kodisein
 */

#ifndef __KModuleObjectText
#define __KModuleObjectText

#include "KObjectModule.h"

class KModuleObjectText : public KObjectModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    void		createConnectors	();

    public:
    
                        KModuleObjectText	();
};

#endif