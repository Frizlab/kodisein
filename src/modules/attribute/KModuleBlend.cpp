/*
 *  KModuleBlend.cpp
 *  kodisein
 */

#include "KModuleBlend.h"
#include "KConnectorIntValueInOut.h"
#include "KConnectorAttributeOut.h"
#include "KConnectorAttributeIn.h"
#include "KConsole.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1	(KModuleBlend, KAttributeModule)
KDS_MODULE_VALUES       	(KModuleBlend, "Blend", 0.5f, 0.0f, 0.5f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleBlend::KModuleBlend () : KAttributeModule ()
{
    source_func = GL_SRC_ALPHA;
    dest_func 	= GL_ONE_MINUS_SRC_ALPHA;
    blend 	= true;
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleBlend::apply ()
{
    glPushAttrib(GL_COLOR_BUFFER_BIT);
    glBlendFunc(source_func, dest_func);
    if (blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
    KAttributeModule::apply();
}

// --------------------------------------------------------------------------------------------------------
void KModuleBlend::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    vector<string> names;
    names.push_back("yes");
    names.push_back("no");
    vector<int> bools;
    bools.push_back(true);
    bools.push_back(false);
    ioConnector = new KConnectorIntValueInOut( this, names, bools, "blend active" );
    ioConnector->translate (1.0f + KDS_VALUECONNECTOR_RADIUS, 0.0f, 0.0f); 
    ioConnector->rotate(0.0, 0.0, -90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KModuleBlend::setBlend);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KModuleBlend::getBlend);
    names.clear();
    names.push_back("0");
    names.push_back("1");
    names.push_back("dc");
    names.push_back("1-dc");
    names.push_back("sa");
    names.push_back("1-sa");
    names.push_back("da");
    names.push_back("1-da");
    names.push_back("sa saturate");
    
    vector<int> enums;
    enums.push_back(GL_ZERO);
    enums.push_back(GL_ONE);
    enums.push_back(GL_DST_COLOR);
    enums.push_back(GL_ONE_MINUS_DST_COLOR);
    enums.push_back(GL_SRC_ALPHA);
    enums.push_back(GL_ONE_MINUS_SRC_ALPHA);
    enums.push_back(GL_DST_ALPHA);
    enums.push_back(GL_ONE_MINUS_DST_ALPHA);
    enums.push_back(GL_SRC_ALPHA_SATURATE);

    ioConnector = new KConnectorIntValueInOut( this, names, enums, "source factor" );
    ioConnector->translate (1.0f + KDS_VALUECONNECTOR_RADIUS, 0.0f, 0.5f); 
    ioConnector->rotate(0.0, 0.0, -90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KModuleBlend::setSourceFunc);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KModuleBlend::getSourceFunc);  

    names.clear();
    names.push_back("0");
    names.push_back("1");
    names.push_back("sc");
    names.push_back("1-sc");
    names.push_back("sa");
    names.push_back("1-sa");
    names.push_back("da");
    names.push_back("1-da");
 
    enums.clear();
    enums.push_back(GL_ZERO);
    enums.push_back(GL_ONE);
    enums.push_back(GL_SRC_COLOR);
    enums.push_back(GL_ONE_MINUS_SRC_COLOR);
    enums.push_back(GL_SRC_ALPHA);
    enums.push_back(GL_ONE_MINUS_SRC_ALPHA);
    enums.push_back(GL_DST_ALPHA);
    enums.push_back(GL_ONE_MINUS_DST_ALPHA);

    ioConnector = new KConnectorIntValueInOut( this, names, enums, "dest factor" );
    ioConnector->translate (1.0f + KDS_VALUECONNECTOR_RADIUS, 0.0f, -0.5f); 
    ioConnector->rotate(0.0, 0.0, -90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KModuleBlend::setDestFunc);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KModuleBlend::getDestFunc); 

    KConnector * connector;
        
    connector = new KConnectorAttributeOut( this, "blend out" ); 
    connector->translate (0.0, -0.2f, 0.0);
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);

    KAttributeModule::createConnectors();

    connector = new KConnectorAttributeIn( this );
    connector->translate (0.0, KDS_VALUECONNECTOR_RADIUS + KDS_CONNECTOR_MIN_DISTANCE, 0.0);
    addConnector(connector);
}


