/*
 *  KModuleRotate.h
 *  kodisein
 */

#ifndef __KModuleRotate
#define __KModuleRotate

#include "KModuleMatrix.h"

class KModuleRotate : public KModuleMatrix
{
    KDS_MODULE_HEADER

    protected:
    
    void	createValueConnectors	();

    public:
    
                KModuleRotate		();
};

#endif
