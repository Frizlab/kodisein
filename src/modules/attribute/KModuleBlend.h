/*
 *  KModuleBlend.h
 *  kodisein
 */

#ifndef __KModuleBlend
#define __KModuleBlend

#include "KAttributeModule.h"

class KModuleBlend : public KAttributeModule
{
    KDS_MODULE_HEADER
    
    protected:
 
    bool			blend;
    int				source_func;
    int				dest_func;
 
    void			createConnectors	();
   
    public:
    
                                KModuleBlend		();
    
    virtual void		apply			();
    
    int				getSourceFunc		() const { return source_func; }
    void			setSourceFunc		( int i ) { source_func = i; }
    int				getDestFunc		() const { return dest_func; }
    void			setDestFunc		( int i ) { dest_func = i; }
    void			setBlend		( bool b ) { blend = b; }
    bool			getBlend		() const { return blend; }
};

#endif