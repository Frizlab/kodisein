/*
 *  KModuleVariable.cpp
 *  kodisein
 */

#include "KModuleVariable.h"
#include "KModulator.h"
#include "KNumberField.h"
#include "KFloatValueObject.h"
#include "KConnectorValueIn.h"
#include "KConnectorValueOut.h"
#include "KConsole.h"


KDL_CLASS_INTROSPECTION_1 	(KModuleVariable,  KValueModule)
KDS_MODULE_VALUES		(KModuleVariable, "Variable", 0.0, 0.0, 1.0f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleVariable::KModuleVariable ( const GLfloat v ) : KValueModule ()
{	
    value = v;
        
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleVariable::setValue ( float v )
{ 
    if (v == value) return;

    value = v;

    KConnector * connectedInConnector = getConnectorWithName("variable")->getConnectedConnector();
    
    if (connectedInConnector)
    {
        ((KConnectorValueIn*)connectedInConnector)->setValue(value);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleVariable::createConnectors ()
{
    KValueConnector * connector;
    
    connector = new KConnectorValueOut( this, "variable" );
    connector->translate(0.0, 0.8f, 0.0);
    connector->makeParentConnector(true);
    addConnector(connector);

    KFloatValueObject * value;

    value = new KFloatValueObject("variable");
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetFloatPtr)&KModuleVariable::setValue);
    values.back()->setProviderCallback(this, (KGetFloatPtr)&KModuleVariable::getValue);    
}

// --------------------------------------------------------------------------------------------------------
string KModuleVariable::getDisplayName () const
{ 
    return kStringPrintf("%s %g", KModule::getDisplayName().c_str(), value); 
}

// --------------------------------------------------------------------------------------------------------
void KModuleVariable::initInspector ( KModuleInspector * inspector )
{
    // override value modules initInspector
    inspector->setTitle(getDisplayName());
    
    // variables value
    values[0]->addToWidget(inspector->getValuesWidget());
    inspector->layout();
}

// --------------------------------------------------------------------------------------------------------
void KModuleVariable::addToWidget ( KWidgetArray * valueWidget, int depth )
{
    if (depth >= VALUE_MAX_DEPTH) valueWidget->addChild(new KLabel(VALUE_UNKNOWN_STRING));
    else
    {    
        KNumberField * valueField = new KNumberField (value);
        valueField->setTextCols(5);
        valueField->addReceiverCallback(this, (KSetFloatPtr)&KModuleVariable::setValue);
        valueWidget->getWindow()->addPickable(valueField);
        valueWidget->addChild(valueField);
    }
}
