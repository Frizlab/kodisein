/*
 *  KModuleScale.h
 *  kodisein
 */

#ifndef __KModuleScale
#define __KModuleScale

#include "KModuleMatrix.h"

// --------------------------------------------------------------------------------------------------------

class KModuleScale : public KModuleMatrix
{
    KDS_MODULE_HEADER

    protected:
    
    void			createValueConnectors	();
    
    public:
    
                                KModuleScale		();
};

#endif
