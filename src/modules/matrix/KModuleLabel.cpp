/*
 *  KModuleLabel.cpp
 *  kodisein
 */

#include "KModuleLabel.h"
#include "KModuleGoto.h"
#include "KController.h"
#include "KModules.h"
#include "KConnectorMatrixOut.h"
#include "KConnectorMatrixIn.h"
#include "KHandlesObject.h"
#include "KStringValueObject.h"
#include "KConnectorIntValueInOut.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleLabel, KHubModule)
KDS_MODULE_VALUES		(KModuleLabel, "Label", 0.1f, 0.1f, 0.1f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleLabel::KModuleLabel () : KHubModule ()
{
    label_name	= "label";
    active	= 1;
    
    matrix_object = new KHandlesObject(this);
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
KModuleLabel::~KModuleLabel ()
{
    disconnect (); // to make sure that the virtual disconnectConnector will be called
    while (gotos.empty() == false)
    {
        gotos.back()->setLabelName("");
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleLabel::addGoto ( KModuleGoto * gotoModule )
{ 
    vector<KModuleGoto*>::iterator result = find (gotos.begin(), gotos.end(), gotoModule);
    if (result == gotos.end())
    {
        gotos.push_back(gotoModule);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleLabel::removeGoto ( KModuleGoto * gotoModule )
{ 
    vector<KModuleGoto*>::iterator result = find (gotos.begin(), gotos.end(), gotoModule);
    if (result != gotos.end())
    {
        gotos.erase(result);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleLabel::setLabelName ( const string & labelName )
{ 
    if (labelName != label_name)
    {
        label_name = labelName;

        vector<KModuleGoto*>::iterator iter = gotos.begin();
        while (iter != gotos.end())
        {
            (*iter)->setLabelName(label_name);
            iter++;
        }
    }
}
 
// --------------------------------------------------------------------------------------------------------
KModuleLabel * KModuleLabel::getLabelWithName ( const string & labelName )
{
    if (labelName == "") return NULL;
    vector<KModule*> labels; 
    Controller.modules->getModulesOfType ( labels, false, KModuleLabel::classId() );
    vector<KModule*>::iterator iter = labels.begin();
    while (iter != labels.end())
    {	
        if (((KModuleLabel*)*iter)->getLabelName() == labelName) return (KModuleLabel*)*iter;
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KModuleLabel::disconnectConnector ( KConnector * connector )
{
    if (connector == getConnectorWithName("matrix out") && 
        Controller.modules->getShowInactiveModules() == false)
    {
        Controller.modules->toggleModuleHierarchy (true, getConnectorWithName("matrix out")->getConnectedModule());
    }
    KHubModule::disconnectConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
bool 
KModuleLabel::connectModule ( KModule * otherModule, KConnector * ownConnector, KConnector * otherConnector )
{
    if (ownConnector == NULL || otherConnector == NULL)
    {
        return KModule::connectModule(otherModule, ownConnector, otherConnector);
    }
    if (ownConnector->getName() == "matrix out" && active == 0 &&
        Controller.modules->getShowInactiveModules() == false)
    {
        KModule::connectModule(otherModule, ownConnector, otherConnector);
        Controller.modules->toggleModuleHierarchy (false, getConnectorWithName("matrix out")->getConnectedModule());
        return true;
    }
    return KModule::connectModule(otherModule, ownConnector, otherConnector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleLabel::setActive( int a )
{ 
    if (active != a)
    {
        active = a;
        if (Controller.modules->getShowInactiveModules() == false)
        {
            Controller.modules->toggleModuleHierarchy 
                                    (active != 0, getConnectorWithName("matrix out")->getConnectedModule());
        }
    }
}
 
// --------------------------------------------------------------------------------------------------------
string KModuleLabel::getDisplayName () const
{ 
    return kStringPrintf("[%s '%s' %s]", 	
                                    getName().c_str(), label_name.c_str(), active ? "active" : "inactive"); 
}

// --------------------------------------------------------------------------------------------------------
void KModuleLabel::displayChildModules ( int mode )
{
    if (active) 
    {
        KModule::displayChildModules(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleLabel::createConnectors ()
{
    KValueObject * value;

    value = new KStringValueObject( "name" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KModuleLabel::setLabelName);
    values.back()->setProviderCallback(this, (KGetStringPtr)&KModuleLabel::getLabelName);

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
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KModuleLabel::setActive);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KModuleLabel::getActive);      
    
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


