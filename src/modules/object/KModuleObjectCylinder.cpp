/*
 *  KModuleObjectCylinder.cpp
 *  kodisein
 */

#include "KModuleObjectCylinder.h"
#include "KConnectorIntValueInOut.h"
#include "KCylinder.h"
#include "KXMLTools.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 	(KModuleObjectCylinder, KObjectModule)
KDS_MODULE_VALUES		(KModuleObjectCylinder, "Cylinder", 1.0f, 0.0, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleObjectCylinder::KModuleObjectCylinder () : KObjectModule ()
{
    matrix_object = new KCylinder (this);
    
    createConnectors ();
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectCylinder::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR_Y("slices", -1, 0.5,0,1,2, (KObject*)matrix_object,KCylinder,setSlices,getSlices)
    NEW_IO_CONNECTOR_Y("stacks", -1, 0.5,0,2,2, (KObject*)matrix_object,KCylinder,setStacks,getStacks)

    ioConnector = new KConnectorValueInOut (this, "top radius");
    ioConnector->translate (-1.2f, 0.0, 0.0);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetFloatPtr)&KCylinder::setTopRadius);
    values.back()->setProviderCallback(matrix_object, (KGetFloatPtr)&KCylinder::getTopRadius);  

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
    values.back()->addReceiverCallback(matrix_object, (KSetIntPtr)&KCylinder::setNormals);
    values.back()->setProviderCallback(matrix_object, (KGetIntPtr)&KCylinder::getNormals);  

    names.clear();
    names.push_back("outside");
    names.push_back("inside");
    enums.clear();
    enums.push_back(GLU_OUTSIDE);
    enums.push_back(GLU_INSIDE);
    ioConnector = new KConnectorIntValueInOut (this, names, enums, "orientation");
    ioConnector->translate (-1.2f, -0.5f, 0.333f);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetIntPtr)&KCylinder::setOrientation);
    values.back()->setProviderCallback(matrix_object, (KGetIntPtr)&KCylinder::getOrientation);  
}
