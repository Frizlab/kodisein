/*
 *  KMatrixModule.cpp
 *  kodisein
 */

#include "KMatrixModule.h"
#include "KController.h"
#include "KHandlesObject.h"
#include "KConnectorMatrixOut.h"
#include "KConnectorMatrixIn.h"
#include "KObjects.h"
#include "KModules.h"
#include "KConsole.h"
#include "KXMLTools.h"

#include <algorithm>

KDL_CLASS_INTROSPECTION_1 (KMatrixModule, KModule)

// --------------------------------------------------------------------------------------------------------
KMatrixModule::KMatrixModule () : KModule ()
{
    description   = "";
    matrix_object = NULL; // must be created by subclasses!
}

// --------------------------------------------------------------------------------------------------------
KMatrixModule::KMatrixModule ( const KMatrixModule & m ) : KModule (m)
{
    description   = ""; 
    matrix_object = NULL; // must be created by subclasses!
}

// --------------------------------------------------------------------------------------------------------
KMatrixModule::~KMatrixModule ()
{
    delete matrix_object;
}

// --------------------------------------------------------------------------------------------------------
KMatrix KMatrixModule::getWorldMatrix () const
{
    KMatrixModule * parent = (KMatrixModule*)getParentModule();
    if (parent) 
    {
        return parent->getWorldMatrix() * (*matrix_object);
    }
    return (*matrix_object);
}

// --------------------------------------------------------------------------------------------------------
KMatrixModule * KMatrixModule::getFirstChild () const
{
    KConnector * outConnector = getConnectorOfType(KDS_CONNECTOR_MATRIX_OUT, KDS_USED_CONNECTOR);
    if (outConnector == NULL) return NULL;
    return (KMatrixModule*)outConnector->getConnectedModule();
}

// --------------------------------------------------------------------------------------------------------
KMatrixModule * KMatrixModule::getNextSibling () const
{
    KModule * parentModule = getParentModule();
    vector<KModule*> siblings;
    if (parentModule)	siblings = parentModule->getChildModules();
    else 		siblings = Controller.modules->getRootModules();
    
    vector<KModule*>::iterator result = find(siblings.begin(), siblings.end(), (KModule*)this);
    do
    {
        result++; 
        if (result >= siblings.end()) result = siblings.begin();
    }
    while ((*result) != (KModule*)this && (*result)->getClassId() >= KMatrixModule::classId() == false);
    return (KMatrixModule*)*result;
}

// --------------------------------------------------------------------------------------------------------
KMatrixModule * KMatrixModule::getPrevSibling () const
{
    KModule * parentModule = getParentModule();
    vector<KModule*> siblings;
    if (parentModule)	siblings = parentModule->getChildModules();
    else 		siblings = Controller.modules->getRootModules();

    vector<KModule*>::iterator result = find(siblings.begin(), siblings.end(), (KModule*)this);    
    do
    {
        result--; 
        if (result < siblings.begin()) result = siblings.end()-1;
    }
    while ((*result) != (KModule*)this && (*result)->getClassId() >= KMatrixModule::classId() == false);
    return (KMatrixModule*)*result;
}

// --------------------------------------------------------------------------------------------------------
void KMatrixModule::setPicked ( bool p )
{
    if (picked != p)
    {
        if (p) Controller.modules->objects->pickHandle(matrix_object);
        else   Controller.modules->objects->pickHandle(NULL);
        KModule::setPicked(p);
    }
}

// --------------------------------------------------------------------------------------------------------
void KMatrixModule::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        preDisplay(mode);
        matrix_object->glMultMatrix();
        postDisplay(mode);
    }
    else if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        preDisplay(mode);
        matrix_object->display(mode);
        postDisplay(mode);
    }
    else
    {
        KModule::display(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
void KMatrixModule::apply ( KMatrix m ) const
{
    PickableVector::const_iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        if (((KConnector*)*iter)->getType() == KDS_CONNECTOR_MATRIX_OUT && 
            ((KConnector*)*iter)->getConnectedModule())
        {
            ((KMatrixModule*)((KConnector*)*iter)->getConnectedModule())->apply(m * (*matrix_object));
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KMatrixModule::initInspector ( KModuleInspector * inspector )
{
    KModule::initInspector(inspector);
    ((KHandle*)matrix_object)->initInspector(inspector);
}

// --------------------------------------------------------------------------------------------------------
void KMatrixModule::setXMLValues ( string & values )
{
    kXMLParseValue(values, "matrix", KDL_XML_VALUE_SEPARATED_MATRIX, matrix_object);
    KModule::setXMLValues(values);
}

// --------------------------------------------------------------------------------------------------------
string KMatrixModule::getXMLValues ( int depth ) const
{
    string xml;
    if (matrix_object) 
    {
        xml += kXMLValue("matrix", KDL_XML_VALUE_SEPARATED_MATRIX, matrix_object, depth);
    }
    xml += KModule::getXMLValues(depth);
    return xml;
}
