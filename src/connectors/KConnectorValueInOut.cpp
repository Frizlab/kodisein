/*
 *  KConnectorValueInOut.cpp
 *  kodisein
 */

#include "KConnectorValueInOut.h"
#include "KConnectorValueOut.h"
#include "KOperationModule.h"
#include "KModulator.h"
#include "KNumberField.h"
#include "KController.h"
#include "KModules.h"
#include "KConsole.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_2 (KConnectorValueInOut, KConnectorValueIn, KFloatValueObject)

// --------------------------------------------------------------------------------------------------------
void KConnectorValueInOut::connectWithConnector ( KConnector * c )
{
    KConnectorValueIn::connectWithConnector(c);

    if (c->getModule()->getClassId() >= KOperationModule::classId() && 
        ((KOperationModule*)c->getModule())->getSex() == VALUEMODULE_SEX_MALE)
    {
        ((KOperationModule*)c->getModule())->connectInOutConnector(this);
    }
}

// --------------------------------------------------------------------------------------------------------
void KConnectorValueInOut::providerSet ()
{
    receiveValue(&value);
}

// --------------------------------------------------------------------------------------------------------
void KConnectorValueInOut::setValue ( float v )
{
    KFloatValueObject::setReceiverValue(v); // notify receivers without changing internal value
}

// --------------------------------------------------------------------------------------------------------
void KConnectorValueInOut::setReceiverValue ( float v )
{
    value = v;
    KFloatValueObject::setReceiverValue(v);
    
    if (connected_connectors.size() > 1)
    {
        ((KConnectorValueIn*)connected_connectors[1])->setValue(value);
    }
}

// --------------------------------------------------------------------------------------------------------
void KConnectorValueInOut::textFieldPicked ( bool b )
{
    setSelected(!selected);
}

// --------------------------------------------------------------------------------------------------------
void KConnectorValueInOut::addToWidget ( KWidgetArray * widgetArray )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    widgetArray->addChild(valueWidget);

    KLabel * label = new KLabel(getName());
    valueWidget->addChild(label);
        
    KNumberField * valueField = new KNumberField (value);
    valueField->addReceiverCallback((KConnectorValueIn*)this, 
                (KSetFloatPtr)(void (KConnectorValueIn::*)(float))&KConnectorValueInOut::setReceiverValue);
    valueField->addReceiverCallback((KFloatValueObject*)this, 
                (KSetBoolPtr)(void (KFloatValueObject::*)(bool))&KConnectorValueInOut::textFieldPicked,
                KDL_NOTIFICATION_TYPE_TEXTFIELD_PICKED);
    widgetArray->getWindow()->addPickable(valueField);
    valueWidget->addChild(valueField);
    
    if (isConnected())
    {
        ((KValueModule*)getConnectedModule())->addToWidget(valueWidget);
    }

    if (isSelected() || isPicked())
    {
        label->setFGColor(KColor(0.5, 0.5, 1.0, 1.0));
        valueField->setBGColor(KColor(0.0, 0.0, 1.0, 0.25));
    }
}
