/*
 *  KModuleSize.cpp
 *  kodisein
 */

#include "KModuleSize.h"
#include "KConnectorValueInOut.h"
#include "KConnectorAttributeOut.h"
#include "KConnectorAttributeIn.h"
#include "KConsole.h"


KDL_CLASS_INTROSPECTION_1	(KModuleSize, KAttributeModule)
KDS_MODULE_VALUES       	(KModuleSize, "Size", 0.3f, 0.3f, 0.3f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleSize::KModuleSize () : KAttributeModule ()
{
    line_width = 1;
    point_size = 1;
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleSize::apply ()
{
    glPushAttrib(GL_POINT_BIT | GL_LINE_BIT);
    glPointSize(point_size);
    glLineWidth(line_width);
    KAttributeModule::apply();
}

// --------------------------------------------------------------------------------------------------------
void KModuleSize::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR("line width", 1,0, 1,2, (KObject*)this, KModuleSize, setLineWidth, getLineWidth)
    NEW_IO_CONNECTOR("point size", 1,0, 2,2, (KObject*)this, KModuleSize, setPointSize, getPointSize)

    KConnector * connector;
        
    connector = new KConnectorAttributeOut( this, "size out" ); 
    connector->translate (0.0, -0.20f, 0.0); 
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
    
    KAttributeModule::createConnectors();

    connector = new KConnectorAttributeIn( this ); 
    connector->translate (0.0, KDS_VALUECONNECTOR_RADIUS + KDS_CONNECTOR_MIN_DISTANCE, 0.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleSize::setPointSize ( float ps )
{
    point_size = kMax(ps, 1.0);
}

// --------------------------------------------------------------------------------------------------------
void KModuleSize::setLineWidth ( float lw )
{
    line_width = kMax(lw, 1.0);
}
