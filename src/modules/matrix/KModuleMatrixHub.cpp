/*
 *  KModuleMatrixHub.cpp
 *  kodisein
 */

#include "KModuleMatrixHub.h"
#include "KConnectorMatrixOut.h"
#include "KConnectorMatrixIn.h"
#include "KHandlesObject.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleMatrixHub, KHubModule)
KDS_MODULE_VALUES		(KModuleMatrixHub, "MatrixHub", 0.2, 0.2, 0.2, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleMatrixHub::KModuleMatrixHub () : KHubModule ()
{
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleMatrixHub::createConnectors ()
{
    KConnector * connector;

    connector = new KConnectorMatrixOut( this, "matrix out 1" ); 
    connector->translate (0.0, 1.5, 0.0); // top
    addConnector(connector);
    
    connector = new KConnectorMatrixOut( this, "matrix out 2" ); 
    connector->translate (1.5, 0.0, 0.0); // right
    connector->rotate (0.0, 0.0, -90.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 3" ); 
    connector->translate (0.0, 0.0, 1.5); // front
    connector->rotate (90.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 4" ); 
    connector->translate (0.0, 0.0, -1.5); // back
    connector->rotate (-90.0, 0.0, 0.0);
    addConnector(connector);
    
    connector = new KConnectorMatrixOut( this, "matrix out 5" ); 
    connector->translate (-1.5, 0.0, 0.0); // left
    connector->rotate (0.0, 0.0, 90.0);
    addConnector(connector);

    connector = new KConnectorMatrixIn( this ); 
    connector->translate (0.0, -1.0, 0.0); // bottom
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
}


