/*
 *  KMatrixHandleTranslate.cpp
 *  kodisein
 */

#include "KMatrixHandleTranslate.h"
#include "KController.h"
#include "KModules.h"
#include "KObjects.h"

KDL_CLASS_INTROSPECTION_1 (KMatrixHandleTranslate, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KMatrixHandleTranslate::KMatrixHandleTranslate ( KMatrixModule * m ) : KMatrixHandle ()
{
    module = m;
    Controller.modules->objects->addPickable(this);
    initTranslateHandles ();
}


