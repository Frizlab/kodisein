/*
 *  KModuleIdentity.h
 *  kodisein
 */

#ifndef __KModuleIdentity
#define __KModuleIdentity

#include "KModuleMatrix.h"

class KModuleIdentity : public KModuleMatrix
{
    KDS_MODULE_HEADER
    
    protected:
    
    void			createConnectors	();

    public:
    
                                KModuleIdentity		();
                        
    virtual KMatrix		getWorldMatrix		() const { return *(KMatrix*)matrix_object; }
    
    virtual void		display			( int mode );
};

#endif