/*
 *  KModuleObjectSphere.cpp
 *  kodisein
 */

#include "KModuleObjectSphere.h"
#include "KConnectorIntValueInOut.h"
#include "KSphere.h"
#include "KXMLTools.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 	(KModuleObjectSphere, KObjectModule)
KDS_MODULE_VALUES		(KModuleObjectSphere, "Sphere", 0.0, 0.0, 1.0f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleObjectSphere::KModuleObjectSphere () : KObjectModule ()
{
    matrix_object = new KSphere (this);
    
    createConnectors ();
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectSphere::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR_Y("slices", -1.0f,0.333f,0,1,2, (KObject*)matrix_object,KSphere,setSlices,getSlices)
    NEW_IO_CONNECTOR_Y("stacks", -1.0f,0.333f,0,2,2, (KObject*)matrix_object,KSphere,setStacks,getStacks)

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
    ioConnector->translate (-1.2f, -0.333f, -0.333f);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetIntPtr)&KSphere::setNormals);
    values.back()->setProviderCallback(matrix_object, (KGetIntPtr)&KSphere::getNormals);  

    names.clear();
    names.push_back("outside");
    names.push_back("inside");
    enums.clear();
    enums.push_back(GLU_OUTSIDE);
    enums.push_back(GLU_INSIDE);
    ioConnector = new KConnectorIntValueInOut (this, names, enums, "orientation");
    ioConnector->translate (-1.2f, -0.333f, 0.333f);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetIntPtr)&KSphere::setOrientation);
    values.back()->setProviderCallback(matrix_object, (KGetIntPtr)&KSphere::getOrientation);  
}
