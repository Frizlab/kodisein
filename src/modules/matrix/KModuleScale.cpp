/*
 *  KModuleScale.cpp
 *  kodisein
 */

#include "KModuleScale.h"
#include "KMatrixHandleScale.h"
#include "KConnectorValueInOut.h"
#include "KModules.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleScale, KModuleMatrix)
KDS_MODULE_VALUES		(KModuleScale, "Scale", 1.0, 0.0, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleScale::KModuleScale () : KModuleMatrix (false)
{
    matrix_object = new KMatrixHandleScale(this);

    createValueConnectors();
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleScale::createValueConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR("size x", 1, 0, 1, 3, (KObject*)matrix_object, KSeparatedMatrix, setSX, getSX)
    NEW_IO_CONNECTOR("size y", 1, 0, 2, 3, (KObject*)matrix_object, KSeparatedMatrix, setSY, getSY)
    NEW_IO_CONNECTOR("size z", 1, 0, 3, 3, (KObject*)matrix_object, KSeparatedMatrix, setSZ, getSZ)
}
