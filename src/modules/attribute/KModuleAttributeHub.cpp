/*
 *  KModuleAttributeHub.cpp
 *  kodisein
 */

#include "KModuleAttributeHub.h"
#include "KController.h"
#include "KConnectorAttributeIn.h"
#include "KConnectorMatrixIn.h"
#include "KConnectorMatrixOut.h"
#include "KHandlesObject.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleAttributeHub, KHubModule)
KDS_MODULE_VALUES		(KModuleAttributeHub, "AttributeHub", 0.6f, 0.6f, 0.6f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleAttributeHub::KModuleAttributeHub () : KHubModule ()
{
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleAttributeHub::postDisplay ( int mode )
{
    displayChildModules(mode);
    popAttributes(mode);
    glPopMatrix();
}

// --------------------------------------------------------------------------------------------------------
void KModuleAttributeHub::createConnectors ()
{
    KConnector * connector;
  
    connector = new KConnectorMatrixOut( this, "matrix out" ); 
    connector->translate (0.0, 1.5, 0.0); // top
    addConnector(connector);
  
    connector = new KConnectorAttributeIn( this, "attribute in 1" );
    connector->translate (1.1f, 0.0f, 0.0f); // right
    connector->rotate (0.0, 0.0, -90.0f);
    addConnector(connector);

    connector = new KConnectorAttributeIn( this, "attribute in 2" ); 
    connector->translate (0.0, 0.0, 1.1f); // front
    connector->rotate (90.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorAttributeIn( this, "attribute in 3" ); 
    connector->translate (0.0f, 0.0f, -1.1f); // back
    connector->rotate (-90.0f, 0.0, 0.0);
    addConnector(connector);
    
    connector = new KConnectorAttributeIn( this, "attribute in 4" ); 
    connector->translate (-1.1f, 0.0, 0.0); // left
    connector->rotate (0.0, 0.0, 90.0);
    addConnector(connector);

    connector = new KConnectorMatrixIn( this ); 
    connector->translate (0.0, -1.0f, 0.0); // bottom
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
}


