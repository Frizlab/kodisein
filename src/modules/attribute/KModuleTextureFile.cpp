/*
 *  KModuleTextureFile.cpp
 *  kodisein
 */

#include "KModuleTextureFile.h"
#include "KFileNameValueObject.h"
#include "KFileNameField.h"
#include "KConsole.h"
#include "KFileTools.h"

KDL_CLASS_INTROSPECTION_1	(KModuleTextureFile, KTextureModule)
KDS_MODULE_VALUES   		(KModuleTextureFile, "FileTexture", 1.0, 1.0, 1.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleTextureFile::KModuleTextureFile () : KTextureModule ()
{
    tmp_texture = NULL;
    createFileConnectors();
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
KModuleTextureFile::~KModuleTextureFile ()
{
    deleteTmpTexture();
}

// --------------------------------------------------------------------------------------------------------
void KModuleTextureFile::deleteTmpTexture ()
{
    if (tmp_texture) 
    {
        delete tmp_texture;
        tmp_texture = NULL;
    }
}

// --------------------------------------------------------------------------------------------------------
GLuint KModuleTextureFile::getTextureId ()
{
    KTexture * t = getTexture();
    if (t) return t->getTextureId();
    return 0;
}

// --------------------------------------------------------------------------------------------------------
KTexture * KModuleTextureFile::getTexture ()
{
    if (tmp_texture) 
    {
        return tmp_texture;
    }
    return &texture;
}

// --------------------------------------------------------------------------------------------------------
void KModuleTextureFile::setPicked ( bool p )
{
    KModule::setPicked(p);
    if (picked == false) 
    {
        deleteTmpTexture();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleTextureFile::setTmpFileName ( const string & f )
{
    deleteTmpTexture();
    string tmpTextureFileName = kFileAbsPathName(f);
    
    if (kFileIsImageFile(tmpTextureFileName))
    {
        tmp_texture = new KTexture(tmpTextureFileName);
        if (tmp_texture->getTextureId() == 0)
        {
            deleteTmpTexture ();
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleTextureFile::setFileName ( const string & fn )
{
    deleteTmpTexture();
    texture.setFileName(fn); 
}

// --------------------------------------------------------------------------------------------------------
void KModuleTextureFile::createFileConnectors ()
{
    KFileNameValueObject * value;

    value = new KFileNameValueObject( "file", true );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KModuleTextureFile::setFileName);
    values.back()->setProviderCallback(&texture, (KGetStringPtr)&KTexture::getFileName);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KModuleTextureFile::setTmpFileName,
                                                        KDL_NOTIFICATION_TYPE_SELECTED_FILE_CHANGED);
}


