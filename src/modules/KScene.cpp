/*
 *  KScene.cpp
 *  kodisein
 */

#include "KScene.h"
#include "KController.h"
#include "KModules.h"
#include "KConnectorSceneIn.h"
#include "KConnectorSceneOut.h"
#include "KFileNameValueObject.h"
#include "KFileNameField.h"
#include "KLabel.h"
#include "KConsole.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1	(KScene, KModule)
KDS_MODULE_VALUES       	(KScene, "Scene", 1.0, 1.0, 0.0, 0.6f)

#define PREV_SCENE	"previous scene"
#define NEXT_SCENE	"next scene"

// --------------------------------------------------------------------------------------------------------
KScene::KScene () : KModule ()
{
    filename   		 = "";
    texture_id_modules   = 0;
    texture_id_animation = 0;
    
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
KScene::~KScene ()
{
    if (texture_id_modules)
    {
        glDeleteTextures(1, &texture_id_modules);
        glDeleteTextures(1, &texture_id_animation);
    }
}

// --------------------------------------------------------------------------------------------------------
void KScene::setFileName ( const string & fn )
{ 
    if (filename != fn)
    {
        filename = fn;

        if (texture_id_modules)
        {
            glDeleteTextures(1, &texture_id_modules);
            texture_id_modules = 0;
            
            glDeleteTextures(1, &texture_id_animation);
            texture_id_animation = 0;
        }
        
        string xml = Controller.getXMLFromFileWithName(filename);
        if (!xml.empty())
        {
            KModules * saveModules = Controller.modules;
            KModules * modules = new KModules();
            modules->setXML(xml);
            
            glPushAttrib     (GL_ALL_ATTRIB_BITS);
            
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            modules->display(KDS_APPLICATION_MODE_EDIT_MODULES);

            glGenTextures    (1, &texture_id_modules);
            glBindTexture    (GL_TEXTURE_2D, texture_id_modules);
            
            KSize screenSize = KEventHandler::getScreenSize();
            int ns = 256;
            
            GLubyte * imageData    = (GLubyte*)malloc(screenSize.w * screenSize.h * 4);
            GLubyte * newImageData = (GLubyte*)malloc(ns * ns * 3);
            
            if (imageData && newImageData)
            {
                glReadPixels     (0, 0, screenSize.w, screenSize.h, GL_RGB, GL_UNSIGNED_BYTE, imageData);
                
                gluScaleImage    (GL_RGB, screenSize.w, screenSize.h, GL_UNSIGNED_BYTE, imageData,
                                    ns, ns, GL_UNSIGNED_BYTE, newImageData);
                
                glTexImage2D     (GL_TEXTURE_2D, 0, 3, ns, ns, 0, GL_RGB, GL_UNSIGNED_BYTE, newImageData);
            }
            else
            {
                KConsole::printError("unable to create texture data memory");
                glPopAttrib ();
                return;
            }
            
            glPopAttrib      ();

            modules->display (KDS_APPLICATION_MODE_ANIMATION);
            
            glGenTextures    (1, &texture_id_animation);
            glBindTexture    (GL_TEXTURE_2D, texture_id_animation);

            glReadPixels     (0, 0, screenSize.w, screenSize.h, GL_RGB, GL_UNSIGNED_BYTE, imageData);
            
            gluScaleImage    (GL_RGB, screenSize.w, screenSize.h, GL_UNSIGNED_BYTE, imageData,
                                  ns, ns, GL_UNSIGNED_BYTE, newImageData);

            glTexImage2D     (GL_TEXTURE_2D, 0, 3, ns, ns, 0, GL_RGB, GL_UNSIGNED_BYTE, newImageData);

            free             (imageData);
            free             (newImageData);

            glPopAttrib      ();
            
            delete modules;
                                                
            Controller.modules = saveModules;
        }
    }
}
 
// --------------------------------------------------------------------------------------------------------
void KScene::createConnectors ()
{
    KFileNameValueObject * value;

    value = new KFileNameValueObject( "file", true );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KScene::setFileName);
    values.back()->setProviderCallback(this, (KGetStringPtr)&KScene::getFileName);      

    KConnector * connector;

    connector = new KConnectorSceneOut( this, NEXT_SCENE );
    connector->translate (0.0, 1.0, 0.0); // top
    addConnector(connector);

    connector = new KConnectorSceneIn( this, PREV_SCENE );
    connector->translate (0.0, -1.25, 0.0); // bottom
    connector->rotate (0.0, 0.0, 180.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KScene::displayConnectors (int mode)
{
    KModule::displayConnectors(mode);
    loadId();

    if (texture_id_modules)
    {
        glPushAttrib  (GL_TEXTURE_BIT);
        glEnable      (GL_TEXTURE_2D);
        glBindTexture (GL_TEXTURE_2D, texture_id_modules);
    
        glBegin(GL_QUADS);
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0,  1.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, -1.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f(1.0,  1.0, -1.0); 
        glTexCoord2f(0.0, 1.0); glVertex3f(1.0,  1.0,  1.0);      
        glEnd();
    
        glBegin(GL_QUADS);
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(-1.0,  1.0,  1.0); 
        glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  1.0, -1.0); 
        glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0,  1.0);      
        glEnd();

        glBindTexture (GL_TEXTURE_2D, texture_id_animation);

        glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  1.0, 1.0); 
        glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f( 1.0, -1.0, 1.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f( 1.0,  1.0, 1.0);      
        glEnd();

        glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(0.0, 1.0); glVertex3f( 1.0,  1.0, -1.0); 
        glTexCoord2f(0.0, 0.0); glVertex3f( 1.0, -1.0, -1.0); 
        glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, -1.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f(-1.0,  1.0, -1.0);      
        glEnd();
    }
    else
    {
        glPushAttrib  (GL_TEXTURE_BIT);
    }
    
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
int KScene::getNumberOfChildScenes () const
{
    return 0;
}

// --------------------------------------------------------------------------------------------------------
KScene * KScene::getNthChildScene ( int n ) const
{
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KConnector * KScene::getParentConnector () const
{
    if (getConnectorWithName(PREV_SCENE)->isConnected()) 
    {
        return getConnectorWithName(PREV_SCENE);
    }
    return getConnectorWithName(PREV_SCENE);
}

// --------------------------------------------------------------------------------------------------------
int KScene::getIndex () const
{
    KModule * parentModule = getConnectorWithName(PREV_SCENE)->getConnectedModule();
    if (parentModule && parentModule->getClassId() >= KScene::classId())
    {
        return ((KScene*)parentModule)->getIndex() + 1;
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
string KScene::getDisplayName () const
{ 
    return kStringPrintf("[%s %d %s ]", getName().c_str(),  getIndex(), getFileName().c_str()); 
}

