/*
 *  KModuleSwitch.h
 *  kodisein
 */

#ifndef __KModuleSwitch
#define __KModuleSwitch

#include "KOperationModule.h"

class KModuleSwitch : public KOperationModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    float		old_value;
    bool		switched;
    
    public:    
                        KModuleSwitch 		();

    virtual void	displayConnectors 	( int );
    virtual float	getValue		() const;
};

#endif
