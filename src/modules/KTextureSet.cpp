/*
 *  KTextureSet.cpp
 *  kodisein
 */

#include "KTextureSet.h"
#include "KTextureBatch.h"
#include "KConnectorTextureBatchOut.h"
#include "KFileNameField.h"
#include "KController.h"
#include "KModules.h"
#include "KConsole.h"
#include "KFileHandler.h"
#include "KFileTools.h"
#include "KXMLTools.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_1 	(KTextureSet, KModule)
KDS_MODULE_VALUES       	(KTextureSet, "TextureSet", 0.5f, 0.5f, 0.5f, 0.6f)

#define FIRST_BATCH "first batch"

// --------------------------------------------------------------------------------------------------------
KTextureSet * KTextureSet::newTextureSet ()
{
    return new KTextureSet();
}

// --------------------------------------------------------------------------------------------------------
KTextureSet * KTextureSet::newTextureSetFromFile ( const string & textureSetFile )
{
    string xml = Controller.getXMLFromFileWithName(textureSetFile);
    if (!xml.empty()) 
    {
        if (kXMLReadNamedOpenTag(xml, "TextureSet"))
        {
            if (KFileHandler::pushCurrentDir(kFileDirName(textureSetFile)))
            {
                KTextureSet * newTextureSet = new KTextureSet();
                newTextureSet->filename = textureSetFile;
                newTextureSet->setXML(xml);
                KFileHandler::popCurrentDir();
                Controller.modules->addModule(newTextureSet);
                return newTextureSet;
            }
        }
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KTextureSet::createConnectors ()
{
    KConnector * connector;

    connector = new KConnectorTextureBatchOut( this, FIRST_BATCH );
    connector->translate (0.0, 0.5, 0.0); // top
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KTextureSet::displayConnectors (int mode)
{	
    KModule::displayConnectors(mode);
    loadId();

    float g = 0.25, c = 1.0-g;
    
    glBegin(GL_QUADS);
    RECTANGLE_XZ(-1.0,  -g, -1.0,  -g, -c); // bottom
    RECTANGLE_XZ(   g, 1.0, -1.0,  -g, -c);
    RECTANGLE_XZ(   g, 1.0,    g, 1.0, -c);
    RECTANGLE_XZ(-1.0,  -g,    g, 1.0, -c);

    RECTANGLE_XY(-1.0,  -g, -c,  0.0, 1.0); // front
    RECTANGLE_XY(   g, 1.0, -c,  0.0, 1.0);
    RECTANGLE_XY(-1.0,  -g, -c,  0.0, -g); 
    RECTANGLE_XY(   g, 1.0, -c,  0.0, -g);
    
    RECTANGLE_YX(-1.0,  -g, -c,  0.0, -1.0); // back
    RECTANGLE_YX(   g, 1.0, -c,  0.0, -1.0);
    RECTANGLE_YX(-1.0,  -g, -c,  0.0, g);
    RECTANGLE_YX(   g, 1.0, -c,  0.0, g);
    
    RECTANGLE_ZY(-c,  0.0, -1.0,  -g, -1.0); // left
    RECTANGLE_ZY(-c,  0.0,    g, 1.0, -1.0);
    RECTANGLE_ZY(-c,  0.0, -1.0,  -g, g);
    RECTANGLE_ZY(-c,  0.0,    g, 1.0, g);
    
    RECTANGLE_YZ(-c,  0.0, -1.0,  -g, 1.0); // right
    RECTANGLE_YZ(-c,  0.0,    g, 1.0, 1.0);
    RECTANGLE_YZ(-c,  0.0, -1.0,  -g, -g);
    RECTANGLE_YZ(-c,  0.0,    g, 1.0, -g);
    glEnd();
}
 
// --------------------------------------------------------------------------------------------------------
string KTextureSet::getDisplayName () const
{ 
    return kStringPrintf("[%s %s]", getName().c_str(), getFileName().c_str()); 
}

// --------------------------------------------------------------------------------------------------------
void KTextureSet::initInspector ( KModuleInspector * inspector )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    
    valueWidget->addChild (new KLabel("file"));

    KFileNameField * filenameField = new KFileNameField();
    filenameField->setTextCols(50);
    filenameField->KWidget::flags[KDL_WIDGET_FLAG_FILL_X] = true;
    filenameField->setText(filename);
    filenameField->addReceiverCallback(this, (KSetStringPtr)&KTextureSet::setFileName);
    filenameField->setProviderCallback(this, (KGetStringPtr)&KTextureSet::getFileName);      

    valueWidget->addChild  (filenameField);
    inspector->addPickable (filenameField);

    inspector->addValueWidget(valueWidget);

    KModule::initInspector(inspector);
}
 
// --------------------------------------------------------------------------------------------------------
KTexture * KTextureSet::getIndexedTexture ( int batchIndex, int textureIndex, int versionIndex ) const
{
    int batches = 0;
    KTextureBatch * batchModule = (KTextureBatch*)getConnectorWithName(FIRST_BATCH)->getConnectedModule();
    if (batchModule)
    {
        batches = batchModule->getNumberOfChildBatches() + 1;
    }
    else return NULL;

    return batchModule->getNthChildBatch(batchIndex % batches)->getIndexedTexture(textureIndex, versionIndex);
}

// --------------------------------------------------------------------------------------------------------
void KTextureSet::reload ()
{
    KTextureBatch * batchModule = (KTextureBatch*)getConnectorWithName(FIRST_BATCH)->getConnectedModule();
    if (batchModule)
    {
        batchModule->reload();
    }
}

// --------------------------------------------------------------------------------------------------------
bool KTextureSet::save () const
{
    return Controller.saveXMLInFileWithName(getXML(), filename);
}

