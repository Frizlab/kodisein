/*
 *  KModuleObjectPoint.cpp
 *  kodisein
 */

#include "KModuleObjectPoint.h"
#include "KVertex.h"
#include "KController.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleObjectPoint, KObjectModule)
KDS_MODULE_VALUES		(KModuleObjectPoint, "Point", 0.0, 0.3, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
KModuleObjectPoint::KModuleObjectPoint () : KObjectModule ()
{
    matrix_object = new KVertex (this);
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectPoint::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        preDisplay(mode);
        glBegin(GL_POINTS);
        matrix_object->display(mode);
        glEnd();
        postDisplay(mode);
    }
    else
    {
        KObjectModule::display(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectPoint::setXMLValues ( string & values )
{
    KModule::setXMLValues(values);
    ((KVertex*)matrix_object)->setXMLValues(values);
}

// --------------------------------------------------------------------------------------------------------
string KModuleObjectPoint::getXMLValues ( int depth ) const
{
    string xml;
    xml += KModule::getXMLValues(depth);
    xml += ((KVertex*)matrix_object)->getXMLValues(depth);
    return xml;
}

