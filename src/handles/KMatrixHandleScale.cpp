/*
 *  KMatrixHandleScale.cpp
 *  kodisein
 */

#include "KMatrixHandleScale.h"
#include "KController.h"
#include "KModules.h"
#include "KObjects.h"

KDL_CLASS_INTROSPECTION_1 (KMatrixHandleScale, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KMatrixHandleScale::KMatrixHandleScale ( KMatrixModule * m ) : KMatrixHandle ()
{
    module = m;
    Controller.modules->objects->addPickable(this);
    initScaleHandles ();
}

