/*
 *  KTextureFile.cpp
 *  kodisein
 */

#include "KTextureFile.h"
#include "KTexture.h"
#include "KTextureBatch.h"
#include "KTextureSet.h"
#include "KConnectorTextureVersionIn.h"
#include "KConnectorTextureVersionOut.h"
#include "KConnectorTextureFileIn.h"
#include "KConnectorTextureFileOut.h"
#include "KFileNameValueObject.h"
#include "KFilenameField.h"
#include "KLabel.h"
#include "KConsole.h"
#include "KController.h"
#include "KFileTools.h"

KDL_CLASS_INTROSPECTION_1	(KTextureFile, KModule)
KDS_MODULE_VALUES       	(KTextureFile, "TextureFile", 0.5, 0.5, 0.5, 0.6f)

#define PREV_VERSION	"previous version"
#define NEXT_VERSION	"next version"
#define PREV_TEXTURE	"previous texture"
#define NEXT_TEXTURE	"next texture"

// --------------------------------------------------------------------------------------------------------
KTextureFile::KTextureFile () : KModule ()
{
    filename    = "";
    texture     = NULL;
    tmp_texture = NULL;
    
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
KTextureFile::~KTextureFile ()
{
    deleteTextures();
}

// --------------------------------------------------------------------------------------------------------
void KTextureFile::deleteTextures ()
{
    if (texture)
    {
        delete texture;
        texture = NULL;
    }
    if (tmp_texture)
    {
        delete tmp_texture;
        tmp_texture = NULL;
    }
}

// --------------------------------------------------------------------------------------------------------
bool KTextureFile::isTextureVersion () const
{
    return (getConnectorWithName(PREV_VERSION)->isConnected());
}

// --------------------------------------------------------------------------------------------------------
void KTextureFile::setPicked ( bool p )
{
    KModule::setPicked(p);
    if (picked == false && tmp_texture) 
    {
        delete tmp_texture;
        tmp_texture = NULL;
    }
}

// --------------------------------------------------------------------------------------------------------
void KTextureFile::setTmpFileName ( const string & f )
{
    if (tmp_texture) 
    {
        delete tmp_texture;
        tmp_texture = NULL;
    }
    
    string tmpTextureFileName;
    
    if (kFileIsAbsPath(f) == false)
    {
        tmpTextureFileName = getTextureSetDir() + f;
    }
    else
    {
        tmpTextureFileName = f;
    }
    
    if (kFileIsImageFile(tmpTextureFileName))
    {
        tmp_texture = new KTexture(tmpTextureFileName);
        if (tmp_texture->getTextureId() == 0)
        {
            delete tmp_texture;
            tmp_texture = NULL;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KTextureFile::setFileName ( const string & fn )
{
    if (filename != fn)
    {
	deleteTextures();
        filename = fn; 
    }
}

// --------------------------------------------------------------------------------------------------------
string KTextureFile::getTextureSetDir () const
{
    KModule * rootModule = getRootModule();
    if (rootModule->getClassId() >= KTextureSet::classId())
    {
        return kFileDirName(((KTextureSet*)rootModule)->getFileName());
    }
    return "./";
}

// --------------------------------------------------------------------------------------------------------
string  KTextureFile::getAbsFileName () const
{
    if (kFileIsAbsPath(filename) || filename == "") 
    {
        return filename;
    }
    return getTextureSetDir() + filename;
}

// --------------------------------------------------------------------------------------------------------
void KTextureFile::filenameFieldActivated ( void * sender )
{
    KFileNameField * fnfield = (KFileNameField *)sender;
    fnfield->setCurrentDirPath(getTextureSetDir());
    fnfield->setText(filename);
}
 
// --------------------------------------------------------------------------------------------------------
void KTextureFile::createConnectors ()
{
    KFileNameValueObject * value;

    value = new KFileNameValueObject( "file", true );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KTextureFile::setFileName);
    values.back()->setProviderCallback(this, (KGetStringPtr)&KTextureFile::getFileName);
    values.back()->addReceiverCallback(this, (KSetDataPtr)&KTextureFile::filenameFieldActivated,
                                                        KDL_NOTIFICATION_TYPE_FILENAMEFIELD_ACTIVATED);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KTextureFile::setTmpFileName,
                                                        KDL_NOTIFICATION_TYPE_SELECTED_FILE_CHANGED);

    KConnector * connector;

    connector = new KConnectorTextureFileIn( this, PREV_TEXTURE );
    connector->translate (-1.0, 0.0, 0.0); // left
    connector->rotate (-90.0, 0.0, 90.0);
    addConnector(connector);

    connector = new KConnectorTextureFileOut( this, NEXT_TEXTURE );
    connector->translate (1.25, 0.0, 0.0); // right
    connector->rotate (90.0, 0.0, -90.0);
    addConnector(connector);

    connector = new KConnectorTextureVersionIn( this, PREV_VERSION );
    connector->translate (0.0, 0.0, -1.0); // back
    connector->rotate (-90.0, 0.0, 0.0);
    addConnector(connector);
    
    connector = new KConnectorTextureVersionOut( this, NEXT_VERSION );
    connector->translate (0.0, 0.0, 1.25); // front
    connector->rotate (90.0, 0.0, 0.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KTextureFile::displayConnectors (int mode)
{	
    KModule::displayConnectors(mode);
    loadId();

    glPushAttrib  (GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_TEXTURE_BIT);
    
    GLuint textureId = getTextureId();
    if (textureId)
    {
        glBindTexture (GL_TEXTURE_2D, textureId);
        glEnable      (GL_TEXTURE_2D);
        glTexEnvi     (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }
    
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, 0.25, -1.0); // top
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 0.25,  1.0); 
    glTexCoord2f(0.0, 1.0); glVertex3f( 1.0, 0.25,  1.0); 
    glTexCoord2f(1.0, 1.0); glVertex3f( 1.0, 0.25, -1.0);
    
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -0.25, -1.0); // bottom
    glTexCoord2f(1.0, 1.0); glVertex3f( 1.0, -0.25, -1.0);      
    glTexCoord2f(0.0, 1.0); glVertex3f( 1.0, -0.25,  1.0); 
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -0.25,  1.0);
    glEnd();
    
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
GLuint KTextureFile::getTextureId () const
{
    KTexture * t = getTexture();
    if (t) return t->getTextureId();
    return 0;
}

// --------------------------------------------------------------------------------------------------------
KTexture * KTextureFile::getTexture () const
{
    if (tmp_texture) 
    {
        return tmp_texture;
    }
    if (texture == NULL && !filename.empty())
    {
        ((KTextureFile*)this)->texture = new KTexture(getAbsFileName());
    }
    return texture;
}

// --------------------------------------------------------------------------------------------------------
int KTextureFile::getNumberOfChildVersions () const
{
    KModule * childModule = getConnectorWithName(NEXT_VERSION)->getConnectedModule();
    if (childModule)
    {
        return ((KTextureFile*)childModule)->getNumberOfChildVersions()+1;
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
KTextureFile * KTextureFile::getNthChildVersion ( int n ) const
{
    if (n == 0) return (KTextureFile*)this;
    KModule * childModule = getConnectorWithName(NEXT_VERSION)->getConnectedModule();
    if (childModule)
    {
        return ((KTextureFile*)childModule)->getNthChildVersion(n-1);
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
int KTextureFile::getVersionIndex () const
{
    KModule * parentModule = getConnectorWithName(PREV_VERSION)->getConnectedModule();
    if (parentModule)
    {
        return ((KTextureFile*)parentModule)->getVersionIndex() + 1;
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
KConnector * KTextureFile::getParentConnector () const
{
    if (getConnectorWithName(PREV_VERSION)->isConnected()) return getConnectorWithName(PREV_VERSION);
    return getConnectorWithName(PREV_TEXTURE);
}

// --------------------------------------------------------------------------------------------------------
KTexture * KTextureFile::getIndexedTexture ( int versionIndex ) const
{
    if (versionIndex == 0) return getTexture();
    int versions = 1;
    KTextureFile * firstVersion = 
                        (KTextureFile*)getConnectorWithName(NEXT_VERSION)->getConnectedModule();
    if (firstVersion)
    {
        versions += firstVersion->getNumberOfChildVersions() + 1;
    }
    else return getTexture();

    int index = versionIndex % versions;
    if (index == 0) return getTexture();
    return firstVersion->getNthChildVersion(index-1)->getTexture();
}

// --------------------------------------------------------------------------------------------------------
int KTextureFile::getBatchIndex () const
{
    if (getConnectorWithName(PREV_VERSION)->isConnected())
    {
        return ((KTextureFile*)getConnectorWithName(PREV_VERSION)->getConnectedModule())->getBatchIndex();
    }

    KModule * parentModule = getConnectorWithName(PREV_TEXTURE)->getConnectedModule();
    if (parentModule && parentModule->getClassId() >= KTextureFile::classId())
    {
        return ((KTextureFile*)parentModule)->getBatchIndex();
    }
    if (parentModule && parentModule->getClassId() >= KTextureBatch::classId())
    {
        return ((KTextureBatch*)parentModule)->getIndex();
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
int KTextureFile::getIndex () const
{
    if (getConnectorWithName(PREV_VERSION)->isConnected())
    {
        return ((KTextureFile*)getConnectorWithName(PREV_VERSION)->getConnectedModule())->getIndex();
    }

    KModule * parentModule = getConnectorWithName(PREV_TEXTURE)->getConnectedModule();
    if (parentModule && parentModule->getClassId() >= KTextureFile::classId())
    {
        return ((KTextureFile*)parentModule)->getIndex() + 1;
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
void KTextureFile::reload ()
{
    KTextureFile * nextTexture = (KTextureFile*)getConnectorWithName(NEXT_TEXTURE)->getConnectedModule();
    if (nextTexture) nextTexture->reload();
    nextTexture = (KTextureFile*)getConnectorWithName(NEXT_VERSION)->getConnectedModule();
    if (nextTexture) nextTexture->reload();

    if (texture) 
    {
        delete texture; 
        texture = NULL;
    }
    if (tmp_texture)
    {
        delete tmp_texture;
        tmp_texture = NULL;
    }
}

// --------------------------------------------------------------------------------------------------------
KTextureFile * KTextureFile::getNthChildFile ( int n ) const
{
    if (n == 0) return (KTextureFile*)this;
    KModule * childModule = getConnectorWithName(NEXT_TEXTURE)->getConnectedModule();
    if (childModule)
    {
        return ((KTextureFile*)childModule)->getNthChildFile(n-1);
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
int KTextureFile::getNumberOfChildFiles () const
{
    KModule * childModule = getConnectorWithName(NEXT_TEXTURE)->getConnectedModule();
    if (childModule)
    {
        return ((KTextureFile*)childModule)->getNumberOfChildFiles()+1;
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
string KTextureFile::getDisplayName () const
{ 
    return kStringPrintf("[%s %d %d %d]", 
                                    getName().c_str(), getBatchIndex(), getIndex(), getVersionIndex()); 
}

// --------------------------------------------------------------------------------------------------------
void KTextureFile::initInspector ( KModuleInspector * inspector )
{
    KModule::initInspector(inspector);
    
    KTexture * texture = getTexture();
    if (texture)
    {
        KWidgetArray * valueWidget = new KWidgetArray ();
        valueWidget->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
        KLabel * label;
        label = new KLabel (kStringPrintf("size  %d x %d", texture->width, texture->height));
        valueWidget->addChild(label);
        inspector->addValueWidget(valueWidget);
    }
}

