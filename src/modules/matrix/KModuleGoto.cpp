/*
 *  KModuleGoto.cpp
 *  kodisein
 */

#include "KModuleGoto.h"
#include "KModuleLabel.h"
#include "KController.h"
#include "KConnectorMatrixIn.h"
#include "KHandlesObject.h"
#include "KStringValueObject.h"
#include "KConnectorIntValueInOut.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleGoto, KHubModule)
KDS_MODULE_VALUES		(KModuleGoto, "Goto", 0.1f, 0.1f, 0.1f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleGoto::KModuleGoto () : KHubModule ()
{
    label_name	= "";
    active	= 1;
    label	= NULL;
    
    matrix_object = new KHandlesObject(this);
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
KModuleGoto::~KModuleGoto ()
{
    if (label)
    {
        label->removeGoto(this);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleGoto::setActive ( int a )
{
    active = a;
}

// --------------------------------------------------------------------------------------------------------
void KModuleGoto::setLabelName ( const string & labelName )
{
    if (labelName != label_name || label == NULL)
    {
        label_name = labelName;
        KModuleLabel * newLabel = KModuleLabel::getLabelWithName(label_name);
        if (label == newLabel) return;
        if (label) label->removeGoto(this);
        label = newLabel;
        if (label) label->addGoto(this);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleGoto::displayChildModules ( int mode )
{
    if (active && label && mode != KDS_APPLICATION_MODE_EDIT_MODULES) 
    {
        label->displayChildModules(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
string KModuleGoto::getDisplayName () const
{ 
    return kStringPrintf("[%s '%s' %s]", 	
                                    getName().c_str(), label_name.c_str(), active ? "active" : "inactive"); 
}

// --------------------------------------------------------------------------------------------------------
void KModuleGoto::createConnectors ()
{
    KValueObject * value;

    value = new KStringValueObject( "label name" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KModuleGoto::setLabelName);
    values.back()->setProviderCallback(this, (KGetStringPtr)&KModuleGoto::getLabelName);

    KConnectorIntValueInOut * ioConnector;

    vector<string> names;
    names.push_back("yes");
    names.push_back("no");
    vector<int> bools;
    bools.push_back(1);
    bools.push_back(0);
    ioConnector = new KConnectorIntValueInOut( this, names, bools, "active" );
    ioConnector->translate (1.0f + KDS_VALUECONNECTOR_RADIUS, 0.0, 0.0); 
    ioConnector->rotate(0.0, 0.0, -90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KModuleGoto::setActive);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KModuleGoto::getActive);      
    
    KConnector * connector;
    
    connector = new KConnector( this ); 
    connector->translate (0.0, 0.25, 0.0); // top
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


