/*
 *  KModuleColor.h
 *  kodisein
 */

#ifndef __KModuleColor
#define __KModuleColor

#include "KAttributeModule.h"

class KColor;

class KModuleColor : public KAttributeModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    KColor 			color;
 
    void			createConnectors	();
   
    public:
    
                                KModuleColor		();
    
    virtual void		apply			();
    
    KColor      		getColor		() { return color; }
};

#endif