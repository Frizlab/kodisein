/*
 *  KAttributeModule.h
 *  kodisein
 */

#ifndef __KAttributeModule
#define __KAttributeModule

#include "KModule.h"

class KAttributeModule : public KModule
{
    INTROSPECTION
    
    protected:
    
    void			createConnectors	();
   
    public:
    
                                KAttributeModule	();
                                    
    virtual void		apply			();
    virtual void		postApply		();
};

#endif