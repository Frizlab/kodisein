/*
 *  KStringValueObject.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KStringValueObject.h"
#include "KNumberField.h"
#include "KWidgetArray.h"
#include "KModuleInspector.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 (KStringValueObject, KValueObject)

// --------------------------------------------------------------------------------------------------------
void KStringValueObject::setReceiverValue ( const string & v )
{
    notifyReceivers(v);
}

// --------------------------------------------------------------------------------------------------------
string KStringValueObject::getProviderValue () const
{
    string v;
    receiveValue(&v);
    return v;
}

// --------------------------------------------------------------------------------------------------------
void KStringValueObject::setXMLValues ( string & xml )
{
    string value;
    if (kXMLParseValue(xml, value_name, KDL_XML_VALUE_STRING, &value))
    {
        setReceiverValue(value);
    }
}

// --------------------------------------------------------------------------------------------------------
string KStringValueObject::getXMLValues ( int depth ) const
{        
    string value = getProviderValue();
    return kXMLValue(value_name, KDL_XML_VALUE_STRING, &value, depth);
}

// --------------------------------------------------------------------------------------------------------
void KStringValueObject::addToWidget ( KWidgetArray * widgetArray )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    valueWidget->addChild (new KLabel(value_name));
    KTextField * textField = new KTextField (getProviderValue());
    textField->KWidget::flags[KDL_TEXTFIELD_FLAG_NOTIFY_ON_UNPICK] = true;
    textField->setTextCols(30);
    valueWidget->addChild (textField);
    widgetArray->getWindow()->addPickable (textField);
    textField->addReceiverCallback(this, (KSetStringPtr)&KStringValueObject::setReceiverValue);
    widgetArray->addChild (valueWidget);
}

