/*
 *  KModuleLight.cpp
 *  kodisein
 */

#include "KModuleLight.h"
#include "KModuleColor.h"
#include "KBoolValueObject.h"
#include "KConnectorValueInOut.h"
#include "KConnectorAttributeIn.h"
#include "KConnectorMatrixIn.h"
#include "KConnectorMatrixOut.h"
#include "KController.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleLight, KMatrixModule)
KDS_MODULE_VALUES		(KModuleLight, "Light", 1.0, 1.0, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleLight::KModuleLight () : KMatrixModule ()
{
    matrix_object = new KLight (this);

    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleLight::initLight ( GLenum light )
{
    KColor ambient, diffuse, specular;
    KColor * ambientPtr = NULL, * diffusePtr = NULL, * specularPtr = NULL;
    KModuleColor * colorModule;
    colorModule = (KModuleColor*)getConnectorWithName("diffuse color")->getConnectedModule();
    if (colorModule) 
    {
        diffuse = colorModule->getColor();
        diffusePtr = &diffuse;
    }
    colorModule = (KModuleColor*)getConnectorWithName("ambient color")->getConnectedModule();
    if (colorModule)
    {
        ambient = colorModule->getColor();
        ambientPtr = &ambient;
    }
    colorModule = (KModuleColor*)getConnectorWithName("specular color")->getConnectedModule();
    if (colorModule)
    {
        specular = colorModule->getColor();
        specularPtr = &specular;
    }

    ((KLight*)matrix_object)->initLight (light, getWorldMatrix(), ambientPtr, diffusePtr, specularPtr);
}

// --------------------------------------------------------------------------------------------------------
void KModuleLight::createConnectors ()
{
    KValueObject * value;

    value = new KBoolValueObject("directional");
    values.push_back(value);
    values.back()->addReceiverCallback(matrix_object, (KSetBoolPtr)&KLight::setDirectional);
    values.back()->setProviderCallback(matrix_object, (KGetBoolPtr)&KLight::getDirectional);    
    
    KConnectorValueInOut * ioConnector;
                        
    NEW_IO_CONNECTOR_Y("spot exponent", 1,0.5,0,1,2,
                                        (KObject*)matrix_object,KLight,setSpotExponent,getSpotExponent)
    NEW_IO_CONNECTOR_Y("spot cutoff", 1,0.5,0,2,2, 
                                        (KObject*)matrix_object,KLight,setSpotCutoff,getSpotCutoff)
    NEW_IO_CONNECTOR_Y("constant attenuation", 1,-0.5,0,1,3,
                                        (KObject*)matrix_object,KLight,setCAttenuation,getCAttenuation)
    NEW_IO_CONNECTOR_Y("linear attenuation", 1,-0.5,0,2,3,
                                        (KObject*)matrix_object,KLight,setLAttenuation,getLAttenuation)
    NEW_IO_CONNECTOR_Y("quadratic attenuation", 1,-0.5,0,3,3,
                                        (KObject*)matrix_object,KLight,setQAttenuation,getQAttenuation)
    
    KConnector * connector;
    
    connector = new KConnectorMatrixOut( this, "matrix out" ); 
    connector->translate (0.0, 1.5, 0.0); // top
    addConnector(connector);
    
    connector = new KConnectorAttributeIn( this, "ambient color"); 
    connector->translate (-1.1, 0.0, 0.0); // left
    connector->rotate (0.0, 0.0, 90.0);
    addConnector(connector);

    connector = new KConnectorAttributeIn( this, "specular color" ); 
    connector->translate (0.0, 0.0, -1.1); // back
    connector->rotate (-90.0, 0.0, 0.0);
    addConnector(connector);
    
    connector = new KConnectorAttributeIn( this, "diffuse color" ); 
    connector->translate (0.0, 0.0, 1.1); // front
    connector->rotate (90.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnector( this ); 
    connector->translate (1.0, 0.0, 0.0); // right
    connector->rotate (0.0, 0.0, -90.0);
    addConnector(connector);

    connector = new KConnectorMatrixIn( this ); 
    connector->translate (0.0, -1.0, 0.0); // bottom
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleLight::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        glPushMatrix();
       	matrix_object->glMultMatrix();
        displayChildModules(mode);
        glPopMatrix();
    }
    else
    {
        KMatrixModule::display(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleLight::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);

    loadId();

    GLfloat h = 0.4, bw = 0.4;

    glBegin(GL_QUADS); // inner bottom
    RECTANGLE_ZX(bw-1, 1-bw, bw-1, 1-bw, h-1.0);
    RECTANGLE_XZ(bw-1, 1-bw, bw-1, 1-bw, 1.0-h);
    RECTANGLE_ZY(bw-1, 1-bw, bw-1, 1-bw, 1.0-h);
    glEnd();
}

