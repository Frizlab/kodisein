/*
 *  KVertex.cpp
 *  kodisein
 */

#include "KVertex.h"
#include "KRotationHandle.h"
#include "KTwoDirectionHandle.h"
#include "KController.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 (KVertex, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KVertex::KVertex ( KMatrixModule * m ) : KMatrixHandle ()
{
    module = m;
    initTranslateHandles();
}

// --------------------------------------------------------------------------------------------------------
void KVertex::initInspector ( KModuleInspector * inspector ) 
{
    initInspectorPosition(inspector);
}

// --------------------------------------------------------------------------------------------------------
void KVertex::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        getPosition().glVertex();
    }
    else if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        KMatrixHandle::display(mode);
    }
}    

// --------------------------------------------------------------------------------------------------------
void KVertex::setXMLValues ( string & values )
{
    KVector pos;
    if (kXMLParseValue(values, "vertex", KDL_XML_VALUE_VERTEX, &pos)) setPosition(pos);
}

// --------------------------------------------------------------------------------------------------------
string KVertex::getXMLValues ( int depth ) const
{
    KVector pos = getPosition();
    return kXMLValue("vertex", KDL_XML_VALUE_VERTEX, &pos, depth);
}

