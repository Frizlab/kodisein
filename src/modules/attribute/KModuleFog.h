/*
 *  KModuleFog.h
 *  kodisein
 */

#ifndef __KModuleFog
#define __KModuleFog

#include "KAttributeModule.h"

class KModuleFog : public KAttributeModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    int				fog_mode;
    float			fog_density;
    float			fog_start, fog_end;
    KColor 			fog_color;

    void			createConnectors	();
    
    public:
    
                                KModuleFog		();

    virtual void		apply			();
    
    virtual void		setFogMode		( int m ) { fog_mode = m; }
    virtual int 		getFogMode		() const { return fog_mode; }
    virtual void		setFogDensity	( float f ) { fog_density = f; }
    virtual float 		getFogDensity	() const { return fog_density; }
    virtual void		setFogStart		( float f ) { fog_start = f; }
    virtual float 		getFogStart		() const { return fog_start; }
    virtual void		setFogEnd		( float f ) { fog_end = f; }
    virtual float 		getFogEnd		() const { return fog_end; }
};

#endif