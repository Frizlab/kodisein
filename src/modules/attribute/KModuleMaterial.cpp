/*
 *  KModuleMaterial.cpp
 *  kodisein
 */

#include "KModuleMaterial.h"
#include "KConnectorIntValueInOut.h"
#include "KConnectorAttributeOut.h"
#include "KConnectorAttributeIn.h"
#include "KToggleButton.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1	(KModuleMaterial, KAttributeModule)
KDS_MODULE_VALUES   	(KModuleMaterial, "Material", 0.5f, 0.5f, 0.5f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleMaterial::KModuleMaterial () : KAttributeModule ()
{
    cull_face		= true;
    polygon_mode	= GL_FILL;
    shading_mode	= GL_SMOOTH;
    face_mode		= GL_FRONT;
    parameter		= GL_SPECULAR;
    shininess		= 128;
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleMaterial::apply ()
{
    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_LIGHTING_BIT);

    cull_face ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    glShadeModel (shading_mode);
    glPolygonMode(face_mode, polygon_mode);
    glMaterialfv (face_mode, parameter, color.getValues());
    glMaterialf  (face_mode, GL_SHININESS, shininess);
    
    KAttributeModule::apply();
}

// --------------------------------------------------------------------------------------------------------
void KModuleMaterial::setShininess ( float s )
{
    shininess = kMax (0, kMin (128, s));
}

// --------------------------------------------------------------------------------------------------------
void KModuleMaterial::createConnectors ()
{
    KConnectorIntValueInOut * dioConnector;
    
    vector<string> names;
    names.push_back("front");
    names.push_back("back");
    names.push_back("front & back");
    vector<int> enums;
    enums.push_back(GL_FRONT);
    enums.push_back(GL_BACK);
    enums.push_back(GL_FRONT_AND_BACK);
    
    dioConnector = new KConnectorIntValueInOut( this, names, enums, "face mode" );
    dioConnector->translate (0.33f, 0.0, -(1.0f + KDS_VALUECONNECTOR_RADIUS)); 
    dioConnector->rotate(-90.0f, 0.0, 0.0);
    addConnector(dioConnector);
    values.push_back(dioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KModuleMaterial::setFaceMode);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KModuleMaterial::getFaceMode);  

    names.clear();
    names.push_back("ambient");
    names.push_back("diffuse");
    names.push_back("specular");
    names.push_back("emission");
    enums.clear();
    enums.push_back(GL_AMBIENT);
    enums.push_back(GL_DIFFUSE);
    enums.push_back(GL_SPECULAR);
    enums.push_back(GL_EMISSION);
    dioConnector = new KConnectorIntValueInOut( this, names, enums, "parameter" );
    dioConnector->translate (-0.33f, 0.0f, -(1.0f + KDS_VALUECONNECTOR_RADIUS)); 
    dioConnector->rotate(-90.0f, 0.0, 0.0);
    addConnector(dioConnector);
    values.push_back(dioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KModuleMaterial::setParameter);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KModuleMaterial::getParameter);  

    KConnectorValueInOut * ioConnector;
    NEW_IO_CONNECTOR("red",   1,  0, 1, 4, (KObject*)&color, KColor, setRed, 	getRed)
    NEW_IO_CONNECTOR("green", 1,  0, 2, 4, (KObject*)&color, KColor, setGreen, 	getGreen)
    NEW_IO_CONNECTOR("blue",  1,  0, 3, 4, (KObject*)&color, KColor, setBlue, 	getBlue)
    NEW_IO_CONNECTOR("alpha", 1,  0, 4, 4, (KObject*)&color, KColor, setAlpha, 	getAlpha)
    NEW_IO_CONNECTOR("shininess", 0, 1, 1, 1, (KObject*)this, KModuleMaterial, setShininess, getShininess)
    
    names.clear();
    names.push_back("point");
    names.push_back("line");
    names.push_back("fill");
    enums.clear();
    enums.push_back(GL_POINT);
    enums.push_back(GL_LINE);
    enums.push_back(GL_FILL);
    dioConnector = new KConnectorIntValueInOut( this, names, enums, "polygon mode" );
    dioConnector->translate (-(1.0f + KDS_VALUECONNECTOR_RADIUS), 0.0, 0.5f); 
    dioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(dioConnector);
    values.push_back(dioConnector);
    dioConnector->addReceiverCallback(this, (KSetIntPtr)&KModuleMaterial::setPolygonMode);
    dioConnector->setProviderCallback(this, (KGetIntPtr)&KModuleMaterial::getPolygonMode);  

    names.clear();
    names.push_back("flat");
    names.push_back("smooth");
    enums.clear();
    enums.push_back(GL_FLAT);
    enums.push_back(GL_SMOOTH);
    dioConnector = new KConnectorIntValueInOut( this, names, enums, "shading mode" );
    dioConnector->translate (-(1.0f + KDS_VALUECONNECTOR_RADIUS), 0.0, 0.0); 
    dioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(dioConnector);
    values.push_back(dioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KModuleMaterial::setShadingMode);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KModuleMaterial::getShadingMode);  

    names.clear();
    names.push_back("yes");
    names.push_back("no");
    vector<int> bools;
    bools.push_back(true);
    bools.push_back(false);
    dioConnector = new KConnectorIntValueInOut( this, names, bools, "cull face" );
    dioConnector->translate (-(1.0f + KDS_VALUECONNECTOR_RADIUS), 0.0, -0.5f); 
    dioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(dioConnector);
    values.push_back(dioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)(void (KWidget::*)(int))&KModuleMaterial::setCullFace);
    values.back()->setProviderCallback(this, (KGetIntPtr)(int (KWidget::*)() const)&KModuleMaterial::getCullFace);  

    KConnector * connector;

    connector = new KConnectorAttributeOut( this, "material out" ); 
    connector->translate (0.0, -0.20f, 0.0); 
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
    
    KAttributeModule::createConnectors();

    connector = new KConnectorAttributeIn( this ); 
    connector->translate (0.0, KDS_VALUECONNECTOR_RADIUS + KDS_CONNECTOR_MIN_DISTANCE, 0.0);
    addConnector(connector);
}

