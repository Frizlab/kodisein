/*
 *  KTextureFile.h
 *  kodisein
 */

#ifndef __KTextureFile
#define __KTextureFile

#include "KModule.h"

class KTexture;
class KTextureBatch;

class KTextureFile : public KModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    KTexture			      * texture;
    KTexture			      * tmp_texture;
    string				filename;
    void				createConnectors	();
    void				deleteTextures		();
        
    public:
    
                                        KTextureFile 		();
                                       ~KTextureFile 		();
                                       
    bool				isTextureVersion	() const;
    void				setPicked		( bool );
    KTexture * 				getTexture		() const;
    GLuint				getTextureId		() const;
    string 				getDisplayName 		() const;
    void				setTmpFileName		( const string & );
    void				setFileName		( const string & );
    string				getFileName		() const { return filename; }
    string				getAbsFileName		() const;
    string				getTextureSetDir	() const;
    void				displayConnectors	( int );
    KTexture * 				getIndexedTexture 	( int ) const;
    int					getNumberOfChildFiles   () const;
    KTextureFile * 			getNthChildFile 	( int ) const;
    KTextureFile *			getNthChildVersion	( int ) const;
    int					getNumberOfChildVersions() const;
    KConnector * 			getParentConnector	() const;
    void				reload			();
    
    void				filenameFieldActivated	( void * );
    
    int					getIndex		() const;
    int					getBatchIndex		() const;
    int					getVersionIndex		() const;
    
    void				initInspector 		( KModuleInspector * );
};

#endif
