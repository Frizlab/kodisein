/*
 *  KKeyValueObject.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KKeyValueObject.h"
#include "KLabel.h"
#include "KKeySequenceField.h"
#include "KWidgetArray.h"
#include "KModuleInspector.h"

KDL_CLASS_INTROSPECTION_1 (KKeyValueObject, KStringValueObject)

// --------------------------------------------------------------------------------------------------------
KKeyValueObject::KKeyValueObject (const string & n, int maxLength ) : KStringValueObject (n) 
{
    max_sequence = maxLength;
}
 
// --------------------------------------------------------------------------------------------------------
void KKeyValueObject::addToWidget ( KWidgetArray * widgetArray )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    valueWidget->addChild (new KLabel(value_name));
    string sequence = getProviderValue();
    KKeySequenceField * sequenceField = new KKeySequenceField (sequence, max_sequence);
    valueWidget->addChild (sequenceField);
    widgetArray->getWindow()->addPickable (sequenceField);
    sequenceField->addReceiverCallback(this, (KSetStringPtr)&KKeyValueObject::setReceiverValue);
    widgetArray->addChild (valueWidget);
}

