/*
 *  KModuleVertex.h
 *  kodisein
 */

#ifndef __KModuleVertex
#define __KModuleVertex

#include "KMatrixModule.h"

class KModuleInspector;

class KModuleVertex : public KMatrixModule
{
    KDS_MODULE_HEADER
    
    protected:
 
    float			texture_s, texture_t;
    bool			texture_coords;
    void			createConnectors	();
   
    public:
                                KModuleVertex 		();

    void			apply			( KMatrix ) const;
    void			displayConnectors	( int );
    
    void			setTextureCoords	(  bool b ) { texture_coords = b; }
    bool			getTextureCoords	() const { return texture_coords; }
    void			setTextureS		( float f ) { texture_s = f; }
    float 			getTextureS		() const { return texture_s; }
    void			setTextureT		( float f ) { texture_t = f; }
    float 			getTextureT		() const { return texture_t; }
};

#endif

