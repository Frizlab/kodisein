/*
 *  KModuleFog.cpp
 *  kodisein
 */

#include "KModuleFog.h"
#include "KConnectorIntValueInOut.h"
#include "KConnectorAttributeIn.h"
#include "KConnectorAttributeOut.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1	(KModuleFog, KAttributeModule)
KDS_MODULE_VALUES   	(KModuleFog, "Fog", 1.0f, 1.0f, 1.0f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleFog::KModuleFog () : KAttributeModule ()
{
    fog_color	= KColor(1.0, 1.0, 1.0, 1.0);
    fog_mode	= GL_LINEAR;
    fog_start	= 0.0;
    fog_end	= 1.0;
    fog_density	= 1.0;
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleFog::apply ()
{
    glPushAttrib (GL_FOG_BIT);

    glEnable (GL_FOG);
    glFogf   (GL_FOG_MODE, 	fog_mode);
    glFogf   (GL_FOG_DENSITY,	fog_density);
    glFogf   (GL_FOG_START,	fog_start);
    glFogf   (GL_FOG_END, 	fog_end);
    glFogfv  (GL_FOG_COLOR,	fog_color.getValues());
    
    KAttributeModule::apply();
}

// --------------------------------------------------------------------------------------------------------
void KModuleFog::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    vector<string> names;
    names.push_back("linear");
    names.push_back("exp");
    names.push_back("exp2");
    vector<int> enums;
    enums.push_back(GL_LINEAR);
    enums.push_back(GL_EXP);
    enums.push_back(GL_EXP2);
        
    ioConnector = new KConnectorIntValueInOut( this, names, enums, "fog mode" );
    ioConnector->translate (1.2f, 0.0, 0.0); 
    ioConnector->rotate(0.0, 0.0, -90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KModuleFog::setFogMode);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KModuleFog::getFogMode);  
    
    NEW_IO_CONNECTOR("start",   -1,  0, 1, 3, (KObject*)this, KModuleFog, setFogStart, 	 getFogStart)
    NEW_IO_CONNECTOR("density", -1,  0, 2, 3, (KObject*)this, KModuleFog, setFogDensity, getFogDensity)
    NEW_IO_CONNECTOR("end",     -1,  0, 3, 3, (KObject*)this, KModuleFog, setFogEnd,	 getFogEnd)

    NEW_IO_CONNECTOR("red",   0,  1, 1, 3, (KObject*)&fog_color, KColor, setRed, 	getRed)
    NEW_IO_CONNECTOR("green", 0,  1, 2, 3, (KObject*)&fog_color, KColor, setGreen,	getGreen)
    NEW_IO_CONNECTOR("blue",  0,  1, 3, 3, (KObject*)&fog_color, KColor, setBlue, 	getBlue)

    KConnector * connector;

    connector = new KConnectorAttributeOut( this, "fog out" );
    connector->translate (0.0, -0.20f, 0.0); 
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
    
    KAttributeModule::createConnectors();

    connector = new KConnectorAttributeIn( this ); 
    connector->translate (0.0, KDS_VALUECONNECTOR_RADIUS + KDS_CONNECTOR_MIN_DISTANCE, 0.0);
    addConnector(connector);
}

