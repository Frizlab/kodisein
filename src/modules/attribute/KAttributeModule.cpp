/*
 *  KAttributeModule.cpp
 *  kodisein
 */

#include "KAttributeModule.h"
#include "KConnector.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 (KAttributeModule, KModule)

// --------------------------------------------------------------------------------------------------------
KAttributeModule::KAttributeModule () : KModule ()
{
}

// --------------------------------------------------------------------------------------------------------
void KAttributeModule::apply ()
{
    if (hasConnectorOfType(KDS_CONNECTOR_ATTRIBUTE_IN, KDS_USED_CONNECTOR))
    {
        ((KAttributeModule*)getConnectorOfType 
                        (KDS_CONNECTOR_ATTRIBUTE_IN, KDS_USED_CONNECTOR)->getConnectedModule())->apply();
    }
}

// --------------------------------------------------------------------------------------------------------
void KAttributeModule::postApply ()
{
    if (hasConnectorOfType(KDS_CONNECTOR_ATTRIBUTE_IN, KDS_USED_CONNECTOR))
    {
        ((KAttributeModule*)getConnectorOfType
                 (KDS_CONNECTOR_ATTRIBUTE_IN, KDS_USED_CONNECTOR)->getConnectedModule())->postApply();
    }
    glPopAttrib();
    glShadeModel (GL_SMOOTH); // why?
}

// --------------------------------------------------------------------------------------------------------
void KAttributeModule::createConnectors ()
{
    KConnector * connector;
    
    connector = new KConnector( this );
    connector->translate (0.0, 0.0, 1.0); // front
    connector->rotate (90.0, 0.0, 0.0);
    connector->scale(1.0, 1.0, 0.20);
    addConnector(connector);

    connector = new KConnector( this ); 
    connector->translate (0.0, 0.0, -1.0); // back
    connector->rotate (-90.0, 0.0, 0.0);
    connector->scale(1.0, 1.0, 0.20);
    addConnector(connector);
    
    connector = new KConnector( this );
    connector->translate (-1.0, 0.0, 0.0); // left
    connector->rotate (0.0, 0.0, 90.0);
    connector->scale(0.20, 1.0, 1.0);
    addConnector(connector);

    connector = new KConnector( this ); 
    connector->translate (1.0, 0.0, 0.0); // right
    connector->rotate (0.0, 0.0, -90.0);
    connector->scale(0.20, 1.0, 1.0);
    addConnector(connector);
}


