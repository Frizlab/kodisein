/*
 *  KTexture.h
 *  kodisein
 */

#ifndef __KTexture
#define __KTexture

#pragma warning(disable:4786)

#include "KNotificationObject.h"

#include <SDL_opengl.h>

class KTexture : public KObject
{
    INTROSPECTION
    
    public:
    
    int 		bpp;
    int 		width;
    int 		height;
    GLuint		texture_id;
    string		filename;
 
                        KTexture 		();
                        KTexture 		( const string & );
    virtual             ~KTexture		();
                       
    bool		loadFile		();
    void		setFileName		( const string & );
    string	 	getFileName		() const { return filename; }
    GLuint		getTextureId		() const { return texture_id; }
};

#endif