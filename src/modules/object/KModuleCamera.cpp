/*
 *  KModuleCamera.cpp
 *  kodisein
 */

#include "KModuleCamera.h"
#include "KConnectorIntValueInOut.h"
#include "KConnectorMatrixIn.h"
#include "KConnectorMatrixOut.h"
#include "KController.h"
#include "KModules.h"
#include "KCameraHandler.h"
#include "KProjection.h"
#include "KBoolValueObject.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleCamera, KMatrixModule)
KDS_MODULE_VALUES		(KModuleCamera, "Camera", 1.0f, 0.0, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleCamera::KModuleCamera () : KMatrixModule ()
{
    matrix_object = new KCamera (this);
    manual_mode	= false;
    createConnectors();
}
 
// --------------------------------------------------------------------------------------------------------
void KModuleCamera::createConnectors ()
{
    KValueObject * value;

    value = new KBoolValueObject("manual");
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KModuleCamera::setManualMode);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KModuleCamera::getManualMode);    

    KConnectorValueInOut * ioConnector;

    vector<string> names;
    names.push_back("yes");
    names.push_back("no");
    vector<int> bools;
    bools.push_back(true);
    bools.push_back(false);
    ioConnector = new KConnectorIntValueInOut( this, names, bools, "perspective" );
    ioConnector->translate (1.0f + KDS_VALUECONNECTOR_RADIUS, 0.0, 0.0); 
    ioConnector->rotate(0.0, 0.0, -90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetBoolPtr)&KCamera::setPerspective);
    values.back()->setProviderCallback(matrix_object, (KGetBoolPtr)&KCamera::getPerspective);    
    
    NEW_IO_CONNECTOR_Y("viewport x",      1, 0.5,0,1,2, matrix_object, KCamera,
                                                        setViewportRelativePosX, getViewportRelativePosX)
    NEW_IO_CONNECTOR_Y("viewport y",      1, 0.5,0,2,2, matrix_object, KCamera,
                                                        setViewportRelativePosY, getViewportRelativePosY)
    NEW_IO_CONNECTOR_Y("viewport width",  1,-0.5,0,1,2, matrix_object, KCamera,
                                                        setViewportRelativeWidth, getViewportRelativeWidth)
    NEW_IO_CONNECTOR_Y("viewport height", 1,-0.5,0,2,2, matrix_object, KCamera,
                                                        setViewportRelativeHeight, getViewportRelativeHeight)
    NEW_IO_CONNECTOR_Y("aspect ratio",      1,-0,0,1,3, matrix_object, KCamera,
                                                        setAspectRatio, getAspectRatio)
    NEW_IO_CONNECTOR_Y("field of view y",   1,-0,0,3,3, matrix_object, KCamera,
                                                        setFov, getFov)
    KConnector * connector;

    connector = new KConnectorMatrixOut( this, "matrix out 1" ); 
    connector->translate (0.0, 2.9142f, 0.0); // top
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 2" ); 
    connector->translate (0.0, 1.4142f * 0.75f + 1.0f, 1.4142f * 0.75f + 1.0f); // front top
    connector->rotate (45.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 3" ); 
    connector->translate (0.0, 0.0, 2.9142f); // front 
    connector->rotate (90.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 4" ); 
    connector->translate (0.0, -1.4142f * 0.75f - 1.0f, 1.4142f * 0.75f + 1.0f); // front bottom
    connector->rotate (135.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 5" ); 
    connector->translate (0.0, -1.4142f * 0.75f - 1.0f, -1.4142f * 0.75f - 1.0f); // back bottom
    connector->rotate (225.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 6" ); 
    connector->translate (0.0, 0.0, -2.9142f); // back 
    connector->rotate (270.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 7" ); 
    connector->translate (0.0, 1.4142f * 0.75f + 1.0f, -1.4142f * 0.75f - 1.0f); // back top
    connector->rotate (-45.0, 0.0, 0.0);
    addConnector(connector);
    
    connector = new KConnectorMatrixIn( this ); 
    connector->translate (0.0, -2.4142f, 0.0); // bottom
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleCamera::initProjection ()
{
    KProjection * projection = ((KCamera*)matrix_object)->getProjection();
    *((KMatrix*)projection) = getWorldMatrix(); // get world matrix and apply to projection
    projection->initProjection();
}

// --------------------------------------------------------------------------------------------------------
void KModuleCamera::displayConnectors (int mode)
{
    KModule::displayConnectors(mode);
    loadId();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f,  1.0f, 2.4142f);
    glVertex3f(1.0f, -1.0f, 2.4142f);
    glVertex3f(1.0f, -2.4142f,  1.0f);
    glVertex3f(1.0f, -2.4142f, -1.0f);
    glVertex3f(1.0f, -1.0f, -2.4142f);
    glVertex3f(1.0f,  1.0f, -2.4142f);
    glVertex3f(1.0f,  2.4142f, -1.0f);
    glVertex3f(1.0f,  2.4142f,  1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0, 0.0);
    glVertex3f(-1.0f,  1.0f, 2.4142f);
    glVertex3f(-1.0f,  2.4142f,  1.0f);
    glVertex3f(-1.0f,  2.4142f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -2.4142f);
    glVertex3f(-1.0f, -1.0f, -2.4142f);
    glVertex3f(-1.0f, -2.4142f, -1.0f);
    glVertex3f(-1.0f, -2.4142f,  1.0f);
    glVertex3f(-1.0f, -1.0f, 2.4142f);
    glEnd();
}

