/*
 *  KFloatValueObject.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KFloatValueObject.h"
#include "KNumberField.h"
#include "KWidgetArray.h"
#include "KModuleInspector.h"
#include "KConsole.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 (KFloatValueObject, KValueObject)

// --------------------------------------------------------------------------------------------------------
KFloatValueObject::KFloatValueObject ( const string & n ) : KValueObject (n) 
{
}

// --------------------------------------------------------------------------------------------------------
void KFloatValueObject::setReceiverValue ( float v )
{
    notifyReceivers(v);
}

// --------------------------------------------------------------------------------------------------------
void KFloatValueObject::setValue ( float v )
{
    notifyReceivers(v);
}

// --------------------------------------------------------------------------------------------------------
float KFloatValueObject::getValue () const
{
    return getProviderValue();
}

// --------------------------------------------------------------------------------------------------------
float KFloatValueObject::getProviderValue () const
{
    float v;
    receiveValue(&v);
    return v;
}

// --------------------------------------------------------------------------------------------------------
void KFloatValueObject::setXMLValues ( string & xml )
{
    GLfloat value;
    if (kXMLParseValue(xml, value_name, KDL_XML_VALUE_FLOAT, &value))
    {
        setReceiverValue(value);
    }
}

// --------------------------------------------------------------------------------------------------------
string KFloatValueObject::getXMLValues ( int depth ) const
{        
    GLfloat value = getValue();
    return kXMLValue(value_name, KDL_XML_VALUE_FLOAT, &value, depth);
}

// --------------------------------------------------------------------------------------------------------
void KFloatValueObject::addToWidget ( KWidgetArray * widgetArray )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    KLabel * label = new KLabel(value_name);
    valueWidget->addChild(label);
        
    KNumberField * valueField = new KNumberField (getValue());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KFloatValueObject::setValue);
    widgetArray->getWindow()->addPickable(valueField);
    valueWidget->addChild(valueField);
    widgetArray->addChild(valueWidget);
}

