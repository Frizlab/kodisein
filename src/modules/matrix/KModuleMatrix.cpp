/*
 *  KModuleMatrix.cpp
 *  kodisein
 */

#include "KModuleMatrix.h"
#include "KConnectorMatrixOut.h"
#include "KConnectorMatrixIn.h"
#include "KConnectorValueInOut.h"
#include "KMatrixHandle.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleMatrix, KMatrixModule)
KDS_MODULE_VALUES       	(KModuleMatrix, "Transform", 0.5, 0.5, 0.5, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleMatrix::KModuleMatrix ( bool fullCreation ) : KMatrixModule ()
{
    if (fullCreation == true)
    {
        matrix_object = new KMatrixHandle(this);
        createValueConnectors();
        createConnectors();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleMatrix::createValueConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR("pos x", 0, -1, 1, 3, (KObject*)matrix_object, KSeparatedMatrix, setTX, getTX)
    NEW_IO_CONNECTOR("pos y", 0, -1, 2, 3, (KObject*)matrix_object, KSeparatedMatrix, setTY, getTY)
    NEW_IO_CONNECTOR("pos z", 0, -1, 3, 3, (KObject*)matrix_object, KSeparatedMatrix, setTZ, getTZ)

    NEW_IO_CONNECTOR("size x", 0,  1, 1, 3, (KObject*)matrix_object, KSeparatedMatrix, setSX, getSX)
    NEW_IO_CONNECTOR("size y", 0,  1, 2, 3, (KObject*)matrix_object, KSeparatedMatrix, setSY, getSY)
    NEW_IO_CONNECTOR("size z", 0,  1, 3, 3, (KObject*)matrix_object, KSeparatedMatrix, setSZ, getSZ)

    NEW_IO_CONNECTOR("rot x", 1,  0, 1, 3, (KObject*)matrix_object, KSeparatedMatrix, setRX, getRX)
    NEW_IO_CONNECTOR("rot y", 1,  0, 2, 3, (KObject*)matrix_object, KSeparatedMatrix, setRY, getRY)
    NEW_IO_CONNECTOR("rot z", 1,  0, 3, 3, (KObject*)matrix_object, KSeparatedMatrix, setRZ, getRZ)
}

// --------------------------------------------------------------------------------------------------------
void KModuleMatrix::createConnectors ()
{
    KConnector * connector;

    connector = new KConnectorMatrixOut( this );
    connector->translate (0.0, 0.75, 0.0); // top
    addConnector(connector);
    
    connector = new KConnector( this );
    connector->translate (0.0, 0.0, 1.0); // front
    connector->rotate (90.0, 0.0, 0.0);
    connector->scale(1.0, 1.0, 0.25);
    addConnector(connector);

    connector = new KConnector( this ); 
    connector->translate (0.0, 0.0, -1.0); // back
    connector->rotate (-90.0, 0.0, 0.0);
    connector->scale(1.0, 1.0, 0.25);
    addConnector(connector);
    
    connector = new KConnector( this );
    connector->translate (-1.0, 0.0, 0.0); // left
    connector->rotate (0.0, 0.0, 90.0);
    connector->scale(0.25, 1.0, 1.0);
    addConnector(connector);

    connector = new KConnector( this ); 
    connector->translate (1.0, 0.0, 0.0); // right
    connector->rotate (0.0, 0.0, -90.0);
    connector->scale(0.25, 1.0, 1.0);
    addConnector(connector);

    connector = new KConnectorMatrixIn( this ); 
    connector->translate (0.0, -0.25, 0.0); // bottom
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
    
    matrix_object->addReceiverCallback(this, (KSetDataPtr)&KModuleMatrix::handleMoved);
}

// --------------------------------------------------------------------------------------------------------
void KModuleMatrix::handleMoved ( void * handleData )
{
    vector<KValueObject*>::const_iterator valueIter = values.begin();
    while(valueIter != values.end())
    {
        if ((*valueIter)->getClassId() >= KConnectorValueInOut::classId())
        {
            ((KConnectorValueInOut*)*valueIter)->setReceiverValue
                                (((KConnectorValueInOut*)*valueIter)->getProviderValue());
        }
        valueIter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleMatrix::initInspector ( KModuleInspector * inspector )
{
    vector<KValueObject*>::const_iterator valueIter = values.begin();
    while(valueIter != values.end())
    {
        if ((*valueIter)->getClassId() >= KConnectorValueInOut::classId())
        {
            ((KConnectorValueInOut*)*valueIter)->setReceiverValue
                                (((KConnectorValueInOut*)*valueIter)->KConnectorValueIn::getValue());
        }
        valueIter++;
    }

    KModule::initInspector(inspector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleMatrix::setXMLValues ( string & values )
{
    KModule::setXMLValues(values);
}

// --------------------------------------------------------------------------------------------------------
string KModuleMatrix::getXMLValues ( int depth ) const
{
    return KModule::getXMLValues(depth);
}

