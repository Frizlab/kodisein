/*
 *  KModuleColorMask.cpp
 *  kodisein
 */

#include "KModuleColorMask.h"
#include "KConnectorIntValueInOut.h"
#include "KConnectorAttributeOut.h"
#include "KConnectorAttributeIn.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1	(KModuleColorMask, KAttributeModule)
KDS_MODULE_VALUES       	(KModuleColorMask, "ColorMask", 0.2f, 0.2f, 0.2f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleColorMask::KModuleColorMask () : KAttributeModule ()
{
    color_mask.resize(4);
    color_mask[0] = false;
    color_mask[1] = false;
    color_mask[2] = false;
    color_mask[3] = false;
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleColorMask::apply ()
{
    glPushAttrib(GL_COLOR_BUFFER_BIT);
    glColorMask(!color_mask[0], !color_mask[1], !color_mask[2], !color_mask[3]);
    KAttributeModule::apply();
}

// --------------------------------------------------------------------------------------------------------
void KModuleColorMask::createConnectors ()
{
    KConnectorIntValueInOut * ioConnector;

    vector<string> names;
    names.push_back("no");
    names.push_back("yes");
    vector<int> bools;
    bools.push_back(0);
    bools.push_back(1);
    
    ioConnector = new KConnectorIntValueInOut( this, names, bools, "mask red" );
    ioConnector->translate (1.0f + KDS_VALUECONNECTOR_RADIUS, 0.0f, 0.75f);
    ioConnector->rotate (0.0, 0.0, -90);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KModuleColorMask::setRedMask);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KModuleColorMask::getRedMask);    

    ioConnector = new KConnectorIntValueInOut( this, names, bools, "mask green" );
    ioConnector->translate (1.0f + KDS_VALUECONNECTOR_RADIUS, 0.0f, 0.25f);
    ioConnector->rotate (0.0, 0.0, -90);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KModuleColorMask::setGreenMask);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KModuleColorMask::getGreenMask);    

    ioConnector = new KConnectorIntValueInOut( this, names, bools, "mask blue" );
    ioConnector->translate (1.0f + KDS_VALUECONNECTOR_RADIUS, 0.0, -0.25f);
    ioConnector->rotate (0.0, 0.0, -90);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KModuleColorMask::setBlueMask);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KModuleColorMask::getBlueMask);    

    ioConnector = new KConnectorIntValueInOut( this, names, bools, "mask alpha" );
    ioConnector->translate (1.0f + KDS_VALUECONNECTOR_RADIUS, 0.0, -0.75f);
    ioConnector->rotate (0.0, 0.0, -90);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KModuleColorMask::setAlphaMask);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KModuleColorMask::getAlphaMask);    

    KConnector * connector;
        
    connector = new KConnectorAttributeOut( this, "color mask out" );
    connector->translate (0.0, -0.20f, 0.0); 
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
    
    KAttributeModule::createConnectors();

    connector = new KConnectorAttributeIn( this ); 
    connector->translate (0.0, KDS_VALUECONNECTOR_RADIUS + KDS_CONNECTOR_MIN_DISTANCE, 0.0); 
    addConnector(connector);
}


