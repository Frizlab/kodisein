/*
 *  KModuleObjectLandscape.cpp
 *  kodisein
 */

#include "KModuleObjectLandscape.h"
#include "KConnectorValueInOut.h"
#include "KLandscape.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleObjectLandscape, KObjectModule)
KDS_MODULE_VALUES		(KModuleObjectLandscape, "Landscape", 1.0f, 1.0f, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleObjectLandscape::KModuleObjectLandscape () : KObjectModule ()
{
   matrix_object = new KLandscape (this);
   
   createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectLandscape::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR_Y("v steps", -1,  0.333, 0, 1,2, (KObject*)matrix_object,KLandscape,setVSteps,getVSteps)
    NEW_IO_CONNECTOR_Y("u steps", -1,  0.333, 0, 2,2, (KObject*)matrix_object,KLandscape,setUSteps,getUSteps)

    NEW_IO_CONNECTOR_Y("v order", -1, -0.333, 0, 1,2, (KObject*)matrix_object,KLandscape,setVOrder,getVOrder)
    NEW_IO_CONNECTOR_Y("u order", -1, -0.333, 0, 2,2, (KObject*)matrix_object,KLandscape,setUOrder,getUOrder)
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectLandscape::setXMLValues ( string & values )
{
    KMatrixModule::setXMLValues(values);
    ((KLandscape*)matrix_object)->setXMLValues(values);
}

// --------------------------------------------------------------------------------------------------------
string KModuleObjectLandscape::getXMLValues ( int depth ) const
{
    string xml;
    xml += KMatrixModule::getXMLValues(depth);
    xml += ((KLandscape*)matrix_object)->getXMLValues(depth);
    return xml;
}

