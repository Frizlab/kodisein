/*
 *  KObjectModule.cpp
 *  kodisein
 */

#include "KObjectModule.h"
#include "KHandlesObject.h"
#include "KConnectorAttributeIn.h"
#include "KConnectorMatrixIn.h"
#include "KConnectorMatrixOut.h"
#include "KController.h"

KDL_CLASS_INTROSPECTION_1 (KObjectModule, KMatrixModule)

// --------------------------------------------------------------------------------------------------------
KObjectModule::KObjectModule () : KMatrixModule ()
{
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KObjectModule::createConnectors ()
{
    KConnector * connector;
    
    connector = new KConnectorMatrixOut( this, "matrix out 1" ); 
    connector->translate (0.0, 1.5, 0.0); // top
    addConnector(connector);
    
    connector = new KConnectorMatrixOut( this, "matrix out 2"); 
    connector->translate (0.0, 0.0, 1.5); // front
    connector->rotate (90.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 3" ); 
    connector->translate (0.0, 0.0, -1.5); // back
    connector->rotate (-90.0, 0.0, 0.0);
    addConnector(connector);
    
    connector = new KConnector( this ); 
    connector->translate (-1.0, 0.0, 0.0); // left
    connector->rotate (0.0, 0.0, 90.0);
    addConnector(connector);

    connector = new KConnectorAttributeIn( this ); 
    connector->translate (1.1, 0.0, 0.0); // right
    connector->rotate (0.0, 0.0, -90.0);
    addConnector(connector);

    connector = new KConnectorMatrixIn( this );
    connector->translate (0.0, -1.0, 0.0); // bottom
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KObjectModule::display ( int mode )
{
    if ((mode == KDS_APPLICATION_MODE_ANIMATION) || (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS))
    {
        preDisplay(mode);
        matrix_object->display(mode);
        postDisplay(mode);
    }
    else
    {
        KMatrixModule::display(mode);
    }
}

