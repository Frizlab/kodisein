/*
 *  KModuleObjectFace.cpp
 *  kodisein
 */

#include "KModuleObjectFace.h"
#include "KFace.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleObjectFace, KObjectModule)
KDS_MODULE_VALUES		(KModuleObjectFace, "Face", 0.0, 0.6, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
KModuleObjectFace::KModuleObjectFace () : KObjectModule ()
{
    matrix_object = new KFace (this);
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectFace::setXMLValues ( string & values )
{
    KMatrixModule::setXMLValues(values);
    ((KFace*)matrix_object)->setXMLValues(values);
}

// --------------------------------------------------------------------------------------------------------
string KModuleObjectFace::getXMLValues ( int depth ) const
{
    string xml;
    xml += KMatrixModule::getXMLValues(depth);
    xml += ((KFace*)matrix_object)->getXMLValues(depth);
    return xml;
}

