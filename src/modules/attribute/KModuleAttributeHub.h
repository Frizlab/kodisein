/*
 *  KModuleAttributeHub.h
 *  kodisein
 */

#ifndef __KModuleAttributeHub
#define __KModuleAttributeHub

#include "KHubModule.h"

class KModuleAttributeHub : public KHubModule
{
    KDS_MODULE_HEADER

    protected:
    
    void			createConnectors	();

    public:
    
                                KModuleAttributeHub	();
    
    virtual void		postDisplay		( int mode );
};

#endif