/*
 *  KModuleMatrixHub.h
 *  kodisein
 */

#ifndef __KModuleMatrixHub
#define __KModuleMatrixHub

#include "KHubModule.h"

class KModuleMatrixHub : public KHubModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    void			createConnectors	();

    public:
    
                                KModuleMatrixHub	();
};

#endif