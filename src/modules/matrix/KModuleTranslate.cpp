/*
 *  KModuleTranslate.cpp
 *  kodisein
 */

#include "KModuleTranslate.h"
#include "KMatrixHandleTranslate.h"
#include "KConnectorValueInOut.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleTranslate, KModuleMatrix)
KDS_MODULE_VALUES		(KModuleTranslate, "Translate", 1.0, 1.0, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleTranslate::KModuleTranslate () : KModuleMatrix (false)
{
    matrix_object = new KMatrixHandleTranslate(this);
    
    createValueConnectors();
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleTranslate::createValueConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR("pos x", 1, 0, 1, 3, (KObject*)matrix_object, KSeparatedMatrix, setTX, getTX)
    NEW_IO_CONNECTOR("pos y", 1, 0, 2, 3, (KObject*)matrix_object, KSeparatedMatrix, setTY, getTY)
    NEW_IO_CONNECTOR("pos z", 1, 0, 3, 3, (KObject*)matrix_object, KSeparatedMatrix, setTZ, getTZ)
}