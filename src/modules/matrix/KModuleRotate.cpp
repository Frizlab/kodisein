/*
 *  KModuleRotate.cpp
 *  kodisein
 */

#include "KModuleRotate.h"
#include "KMatrixHandleRotate.h"
#include "KConnectorValueInOut.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleRotate, KModuleMatrix)
KDS_MODULE_VALUES		(KModuleRotate, "Rotate", 0.0, 1.0, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleRotate::KModuleRotate () : KModuleMatrix (false)
{
    matrix_object = new KMatrixHandleRotate(this);

    createValueConnectors();
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleRotate::createValueConnectors ()
{
    KConnectorValueInOut * ioConnector;
    
    NEW_IO_CONNECTOR("rot x", 1,  0, 1, 3, (KObject*)matrix_object, KSeparatedMatrix, setRX, getRX)
    NEW_IO_CONNECTOR("rot y", 1,  0, 2, 3, (KObject*)matrix_object, KSeparatedMatrix, setRY, getRY)
    NEW_IO_CONNECTOR("rot z", 1,  0, 3, 3, (KObject*)matrix_object, KSeparatedMatrix, setRZ, getRZ)
}

