/*
 *  KModuleObjectDisk.cpp
 *  kodisein
 */

#include "KModuleObjectDisk.h"
#include "KConnectorIntValueInOut.h"
#include "KDisk.h"
#include "KXMLTools.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 	(KModuleObjectDisk, KObjectModule)
KDS_MODULE_VALUES		(KModuleObjectDisk, "Disk", 1.0f, 1.0f, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleObjectDisk::KModuleObjectDisk () : KObjectModule ()
{
    matrix_object = new KDisk (this);
    
    createConnectors ();
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectDisk::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR_Y("slices", -1, 0.5,0,1,2, (KObject*)matrix_object,KDisk,setSlices,getSlices)
    NEW_IO_CONNECTOR_Y("loops",  -1, 0.5,0,2,2, (KObject*)matrix_object,KDisk,setLoops, getLoops)

    vector<int>    enums;
    vector<string> names;
    
    names.clear();
    names.push_back("none");
    names.push_back("flat");
    names.push_back("smooth");
    enums.clear();
    enums.push_back(GLU_NONE);
    enums.push_back(GLU_FLAT);
    enums.push_back(GLU_SMOOTH);
    ioConnector = new KConnectorIntValueInOut (this, names, enums, "normals");
    ioConnector->translate (-1.2f, -0.5f, -0.333f);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetIntPtr)&KDisk::setNormals);
    values.back()->setProviderCallback(matrix_object, (KGetIntPtr)&KDisk::getNormals);  

    names.clear();
    names.push_back("outside");
    names.push_back("inside");
    enums.clear();
    enums.push_back(GLU_OUTSIDE);
    enums.push_back(GLU_INSIDE);
    ioConnector = new KConnectorIntValueInOut (this, names, enums, "orientation");
    ioConnector->translate (-1.2, -0.5, 0.333);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetIntPtr)&KDisk::setOrientation);
    values.back()->setProviderCallback(matrix_object, (KGetIntPtr)&KDisk::getOrientation);  

    ioConnector = new KConnectorValueInOut (this, "inner radius");
    ioConnector->translate (-1.2, 0.0, 0.0);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetFloatPtr)&KDisk::setInnerRadius);
    values.back()->setProviderCallback(matrix_object, (KGetFloatPtr)&KDisk::getInnerRadius);  

    ioConnector = new KConnectorValueInOut (this, "start angle");
    ioConnector->translate (-1.2, 0.0, 0.5);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetFloatPtr)&KDisk::setStartAngle);
    values.back()->setProviderCallback(matrix_object, (KGetFloatPtr)&KDisk::getStartAngle);  

    ioConnector = new KConnectorValueInOut (this, "sweep angle");
    ioConnector->translate (-1.2, 0.0, -0.5);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetFloatPtr)&KDisk::setSweepAngle);
    values.back()->setProviderCallback(matrix_object, (KGetFloatPtr)&KDisk::getSweepAngle);  
}
