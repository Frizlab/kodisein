/*
 *  KModuleTextureFile.h
 *  kodisein
 */

#ifndef __KModuleTextureFile
#define __KModuleTextureFile

#include "KTextureModule.h"
#include "KTexture.h"

class KModuleTextureFile : public KTextureModule
{
    KDS_MODULE_HEADER
    
    protected:

    KTexture	texture;
    KTexture *	tmp_texture;

    void	createFileConnectors	();
    void	deleteTmpTexture	();
    
    public:
    
                KModuleTextureFile	();
                ~KModuleTextureFile	();
    
    void	setPicked		( bool );
    void	setTmpFileName		( const string & );
    void	setFileName 		( const string & );

    GLuint	getTextureId		();
    KTexture *	getTexture		();
};

#endif