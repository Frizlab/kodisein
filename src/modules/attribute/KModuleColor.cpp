/*
 *  KModuleColor.cpp
 *  kodisein
 */

#include "KModuleColor.h"
#include "KColor.h"
#include "KConnectorValueInOut.h"
#include "KConnectorAttributeOut.h"
#include "KConnectorAttributeIn.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1	(KModuleColor, KAttributeModule)
KDS_MODULE_VALUES       	(KModuleColor, "Color", 0.0, 0.0, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleColor::KModuleColor () : KAttributeModule ()
{
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleColor::apply ()
{
    glPushAttrib(GL_CURRENT_BIT);
    color.glColor();
    KAttributeModule::apply();
}

// --------------------------------------------------------------------------------------------------------
void KModuleColor::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR("red",   1,0, 1,4, (KObject*)&color, KColor, setRed, 	getRed)
    NEW_IO_CONNECTOR("green", 1,0, 2,4, (KObject*)&color, KColor, setGreen, 	getGreen)
    NEW_IO_CONNECTOR("blue",  1,0, 3,4, (KObject*)&color, KColor, setBlue, 	getBlue)
    NEW_IO_CONNECTOR("alpha", 1,0, 4,4, (KObject*)&color, KColor, setAlpha, 	getAlpha)

    KConnector * connector;
        
    connector = new KConnectorAttributeOut( this, "color out" ); 
    connector->translate (0.0, -0.20f, 0.0); 
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
    
    KAttributeModule::createConnectors();

    connector = new KConnectorAttributeIn( this ); 
    connector->translate (0.0, KDS_VALUECONNECTOR_RADIUS + KDS_CONNECTOR_MIN_DISTANCE, 0.0); 
    addConnector(connector);
}


