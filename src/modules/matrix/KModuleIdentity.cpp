/*
 *  KModuleIdentity.cpp
 *  kodisein
 */

#include "KModuleIdentity.h"
#include "KConnectorMatrixOut.h"
#include "KConnectorMatrixIn.h"
#include "KHandlesObject.h"
#include "KObjects.h"
#include "KPerspectiveProjection.h"
#include "KController.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleIdentity, KModuleMatrix)
KDS_MODULE_VALUES		(KModuleIdentity, "Identity", 0.1f, 0.1f, 0.1f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleIdentity::KModuleIdentity () : KModuleMatrix (false)
{
    matrix_object = new KHandlesObject(this);
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleIdentity::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        KModuleMatrix::display(mode);
    }
    else // (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS || mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        preDisplay(mode);
        KModule * parentModule = getParentModule();
        if (parentModule)
        {
            ((KMatrixModule*)parentModule)->getWorldMatrix().getInverse().glMultMatrix();
        }
        postDisplay(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleIdentity::createConnectors ()
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
}


