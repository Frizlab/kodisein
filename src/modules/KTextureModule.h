/*
 *  KTextureModule.h
 *  kodisein
 */

#ifndef __KTextureModule
#define __KTextureModule

#include "KAttributeModule.h"
#include "KTexture.h"

class KTextureModule : public KAttributeModule
{
    INTROSPECTION
    
    protected:
    
    int				texture_env_mode;
    int				s_generation_mode;
    int				t_generation_mode;
    KColor 			color;

    void			createConnectors	();
    
    public:
    
                                KTextureModule		();

    virtual void		apply			();
    virtual void		postApply		();
    
    virtual GLuint		getTextureId		() { return 0; }

    virtual void		setTextureEnvMode	( int m ) { texture_env_mode = m; }
    virtual int 		getTextureEnvMode	() const  { return texture_env_mode; }
    virtual void		setSGenerationMode	( int m ) { s_generation_mode = m; }
    virtual int 		getSGenerationMode	() const  { return s_generation_mode; }
    virtual void		setTGenerationMode	( int m ) { t_generation_mode = m; }
    virtual int 		getTGenerationMode	() const  { return t_generation_mode; }
};

#endif