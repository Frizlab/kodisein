/*
 *  KMatrixHandleRotate.cpp
 *  kodisein
 */

#include "KMatrixHandleRotate.h"
#include "KController.h"
#include "KModules.h"
#include "KObjects.h"

KDL_CLASS_INTROSPECTION_1 (KMatrixHandleRotate, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KMatrixHandleRotate::KMatrixHandleRotate ( KMatrixModule * m ) : KMatrixHandle ()
{
    module = m;
    Controller.modules->objects->addPickable(this);
    initRotateHandles ();
}

