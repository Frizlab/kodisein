/*
 *  KHubModule.cpp
 *  kodisein
 */

#include "KHubModule.h"
#include "KHandlesObject.h"

KDL_CLASS_INTROSPECTION_1 (KHubModule, KMatrixModule) // KModuleMatrix)

// --------------------------------------------------------------------------------------------------------
KHubModule::KHubModule () : KMatrixModule ()
{
    matrix_object = new KHandlesObject (this);
}

// --------------------------------------------------------------------------------------------------------
const KMatrix & KHubModule::getMatrix () const
{
    KMatrixModule * parent = (KMatrixModule*)getParentModule();
    if (parent) return parent->getMatrix();
    return (*(KMatrix*)matrix_object);
}

// --------------------------------------------------------------------------------------------------------
KMatrix KHubModule::getWorldMatrix () const
{
    KMatrixModule * parent = (KMatrixModule*)getParentModule();
    if (parent) return parent->getWorldMatrix();
    return KMatrix();
}

// --------------------------------------------------------------------------------------------------------
void KHubModule::display ( int mode )
{
    KModule::display(mode);
}

// --------------------------------------------------------------------------------------------------------
void KHubModule::initInspector ( KModuleInspector * inspector )
{
    KModule::initInspector(inspector);
}

// --------------------------------------------------------------------------------------------------------
void KHubModule::setXMLValues ( string & values )
{
    KModule::setXMLValues(values);
}

// --------------------------------------------------------------------------------------------------------
string KHubModule::getXMLValues ( int depth ) const
{
    return KModule::getXMLValues(depth);
}

