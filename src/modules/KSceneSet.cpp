/*
 *  KSceneSet.cpp
 *  kodisein
 */

#include "KSceneSet.h"
#include "KScene.h"
#include "KConnectorSceneOut.h"
#include "KFileNameField.h"
#include "KController.h"
#include "KConsole.h"


KDL_CLASS_INTROSPECTION_1 	(KSceneSet, KModule)
KDS_MODULE_VALUES       	(KSceneSet, "KSceneSet", 1.0, 1.0, 0.0, 0.6f)

#define FIRST_SCENE "first scene"

// --------------------------------------------------------------------------------------------------------
KSceneSet::KSceneSet () : KModule ()
{
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KSceneSet::createConnectors ()
{
    KConnector * connector;

    connector = new KConnectorSceneOut( this, FIRST_SCENE );
    connector->translate (0.0, 1.0, 0.0); // top
    addConnector(connector);
    
    connector = new KConnector( this );
    connector->translate (0.0, 0.0, 1.0); // front
    connector->rotate (90.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnector( this );
    connector->translate (0.0, 0.0, -1.0); // back
    connector->rotate (-90.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnector( this );
    connector->translate (-1.0, 0.0, 0.0); // left
    connector->rotate (0.0, 0.0, 90.0);
    addConnector(connector);

    connector = new KConnector( this );
    connector->translate (1.0, 0.0, 0.0); // right
    connector->rotate (0.0, 0.0, -90.0);
    addConnector(connector);

    connector = new KConnector( this );
    connector->translate (0.0, -1.0, 0.0); // bottom
    connector->rotate (0.0, 0.0, 180.0);
    addConnector(connector);

}

// --------------------------------------------------------------------------------------------------------
void KSceneSet::setFileName ( const string & fileName )
{
    filename = fileName; 
}
 
// --------------------------------------------------------------------------------------------------------
string KSceneSet::getDisplayName () const
{ 
    return kStringPrintf("[%s %s]", getName().c_str(), getFileName().c_str()); 
}

// --------------------------------------------------------------------------------------------------------
void KSceneSet::initInspector ( KModuleInspector * inspector )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    
    valueWidget->addChild (new KLabel("file"));

    KFileNameField * filenameField = new KFileNameField(filename);
    filenameField->setTextCols(50);
    filenameField->addReceiverCallback(this, (KSetStringPtr)&KSceneSet::setFileName);
    filenameField->setProviderCallback(this, (KGetStringPtr)&KSceneSet::getFileName);      

    valueWidget->addChild  (filenameField);
    inspector->addPickable (filenameField);

    inspector->addValueWidget(valueWidget);

    KModule::initInspector(inspector);
}
 
// --------------------------------------------------------------------------------------------------------
KScene * KSceneSet::getIndexedScene ( int sceneIndex ) const
{
    int scenes = 0;
    KScene * sceneModule = (KScene*)getConnectorWithName(FIRST_SCENE)->getConnectedModule();
    if (sceneModule)
    {
        scenes = sceneModule->getNumberOfChildScenes() + 1;
    }
    else return NULL;

    return sceneModule->getNthChildScene(sceneIndex % scenes);
}

// --------------------------------------------------------------------------------------------------------
bool KSceneSet::save () const
{
    return Controller.saveXMLInFileWithName(getXML(), filename);
}

