/*
 *  KSizeValueObject.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KSizeValueObject.h"
#include "KNumberField.h"
#include "KWidgetArray.h"
#include "KModuleInspector.h"
#include "KConsole.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 (KSizeValueObject, KValueObject)

// --------------------------------------------------------------------------------------------------------
KSizeValueObject::KSizeValueObject ( const string & n ) : KValueObject (n) 
{
}

// --------------------------------------------------------------------------------------------------------
void KSizeValueObject::setWidthValue ( float w )
{
    notifyReceivers(KSize((int)w, getProviderValue().h));
}

// --------------------------------------------------------------------------------------------------------
void KSizeValueObject::setHeightValue ( float h )
{
    notifyReceivers(KSize(getProviderValue().w, (int)h));
}

// --------------------------------------------------------------------------------------------------------
KSize KSizeValueObject::getProviderValue () const
{
    KSize size;
    receiveValue(&size);
    return size;
}

// --------------------------------------------------------------------------------------------------------
void KSizeValueObject::setReceiverValue ( const KSize & size ) 
{
    notifyReceivers(size);
}

// --------------------------------------------------------------------------------------------------------
void KSizeValueObject::setXMLValues ( string & xml )
{
    KSize value;
    if (kXMLParseValue(xml, value_name, KDL_XML_VALUE_SIZE, &value))
    {
        setReceiverValue(value);
    }
}

// --------------------------------------------------------------------------------------------------------
string KSizeValueObject::getXMLValues ( int depth ) const
{        
    KSize value = getProviderValue();
    return kXMLValue(value_name, KDL_XML_VALUE_SIZE, &value, depth);
}

// --------------------------------------------------------------------------------------------------------
void KSizeValueObject::addToWidget ( KWidgetArray * widgetArray )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    KLabel * label = new KLabel(value_name);
    valueWidget->addChild(label);
        
    KNumberField * valueField;
    valueField = new KNumberField (getProviderValue().w);
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSizeValueObject::setWidthValue);
    widgetArray->getWindow()->addPickable(valueField);
    valueWidget->addChild(valueField);
    valueField = new KNumberField (getProviderValue().h);
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSizeValueObject::setHeightValue);
    widgetArray->getWindow()->addPickable(valueField);
    valueWidget->addChild(valueField);
    
    widgetArray->addChild(valueWidget);
}

