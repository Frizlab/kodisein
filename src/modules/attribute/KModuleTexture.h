/*
 *  KModuleTexture.h
 *  kodisein
 */

#ifndef __KModuleTexture
#define __KModuleTexture

#include "KTextureModule.h"
#include "KTexture.h"

class KModuleTexture : public KTextureModule
{
    KDS_MODULE_HEADER
    
    protected:
  
    float			batch_index, texture_index, version_index;
    void			createIndexConnectors	();
    
    public:
    
                                KModuleTexture		();

    virtual GLuint		getTextureId		();
    virtual void		setBatchIndex		( float i ) { batch_index = i; }
    virtual float		getBatchIndex		() const { return batch_index; }
    virtual void		setTextureIndex		( float i ) { texture_index = i; }
    virtual float		getTextureIndex		() const { return texture_index; }
    virtual void		setVersionIndex		( float i ) { version_index = i; }
    virtual float		getVersionIndex		() const { return version_index; }
};

#endif