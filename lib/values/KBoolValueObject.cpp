/*
 *  KBoolValueObject.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KBoolValueObject.h"
#include "KNumberField.h"
#include "KWidgetArray.h"
#include "KToggleButton.h"
#include "KModuleInspector.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 (KBoolValueObject, KValueObject)

// --------------------------------------------------------------------------------------------------------
void KBoolValueObject::setReceiverValue ( bool v )
{
    notifyReceivers(v);
}

// --------------------------------------------------------------------------------------------------------
bool KBoolValueObject::getProviderValue () const
{
    bool v;
    receiveValue(&v);
    return v;
}

// --------------------------------------------------------------------------------------------------------
void KBoolValueObject::setXMLValues ( string & xml )
{
    bool value;
    if (kXMLParseValue(xml, value_name, KDL_XML_VALUE_BOOL, &value))
    {
        setReceiverValue(value);
    }
}

// --------------------------------------------------------------------------------------------------------
string KBoolValueObject::getXMLValues ( int depth ) const
{        
    bool value = getProviderValue();
    return kXMLValue(value_name, KDL_XML_VALUE_BOOL, &value, depth);
}

// --------------------------------------------------------------------------------------------------------
void KBoolValueObject::addToWidget ( KWidgetArray * widgetArray )
{
    KButton * button;
    KWidgetArray * valueWidget = new KWidgetArray ();
    valueWidget->addChild (new KLabel(value_name));
    valueWidget->addChild (button = new KToggleButton());
    if (getProviderValue()) button->activate();
    button->addReceiverCallback(this, (KSetBoolPtr)&KBoolValueObject::setReceiverValue);
    widgetArray->getWindow()->addPickable (button);
    widgetArray->addChild (valueWidget);
}

