/*
 *  KModuleTranslate.h
 *  kodisein
 */

#ifndef __KModuleTranslate
#define __KModuleTranslate

#include "KModuleMatrix.h"

class KMatrixHandleTranslate;

class KModuleTranslate : public KModuleMatrix
{
    KDS_MODULE_HEADER

    protected:
    
    void			createValueConnectors	();
    
    public:
    
                                KModuleTranslate	();
};

#endif
