/*
 *  KHandle.cpp
 *  kodisein
 */

#include "KHandle.h"
#include "KHandlesObject.h"
#include "KController.h"
#include "KModules.h"
#include "KObjects.h"
#include "KProjection.h"
#include "KConsole.h"
#include "KModuleInspector.h"
#include "KNumberField.h"

#include <SDL.h>

KDL_CLASS_INTROSPECTION_3 (KHandle, KSeparatedMatrix, KPickable, KNotificationObject)

// --------------------------------------------------------------------------------------------------------
KHandle::KHandle () : KSeparatedMatrix (), KPickable ()
{
    parent = NULL;
}

// --------------------------------------------------------------------------------------------------------
KHandle::KHandle ( KHandle * p ) : KSeparatedMatrix (), KPickable ()
{
    parent = p;
}

// --------------------------------------------------------------------------------------------------------
void KHandle::setPicked ( bool p )
{
    if (p != picked)
    {
        KPickable::setPicked(p);
        getRootHandle()->setPicked(p);
    }
}

// --------------------------------------------------------------------------------------------------------
void KHandle::preDisplay ( int )
{
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);
    glPushMatrix();
    loadId();
    if (picked) glColor4f(1.0, 1.0, 1.0, 1.0);
}

// --------------------------------------------------------------------------------------------------------
void KHandle::postDisplay ( int mode )
{
    glPopMatrix();    
    glPopAttrib();
}

// -------------------------------------------------------------------------------------------------------- 
KMatrix KHandle::getWorldMatrix () const
{
    if (parent) return (parent->getWorldMatrix() * (*this));
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
KHandlesObject * KHandle::getRootHandle ( ) const
{
    if (parent) return (parent->getRootHandle());
    return (KHandlesObject*)this;
}

// --------------------------------------------------------------------------------------------------------
void KHandle::moved ( const KMouseEvent & mouseEvent )
{
    KVector pos = getWorldMatrix().getPosition();
            
    if (Controller.modules->objects->getProjection()->moveObjectRelativeToWindow (mouseEvent.delta, pos))
    {
        KHandleData handleData = {&pos, &mouseEvent};
        notifyReceivers((void*)&handleData, KDL_NOTIFICATION_TYPE_HANDLE_MOVED);
    }
    else
    {
        KConsole::printError("moving handle failed!", false);
    }
}

// --------------------------------------------------------------------------------------------------------
void KHandle::notify () const
{
    notifyReceivers((void*)matrix);
}

// --------------------------------------------------------------------------------------------------------
void KHandle::initInspector ( KModuleInspector * inspector )
{
    initInspectorPosition(inspector);
    initInspectorSize	 (inspector);
    initInspectorRotation(inspector);
}

// --------------------------------------------------------------------------------------------------------
void KHandle::initInspectorPosition ( KModuleInspector * inspector )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    valueWidget->addChild(new KLabel("position"));
    
    KNumberField * valueField = new KNumberField (getTX());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSeparatedMatrix::setTX );
    inspector->addPickable(valueField);
    valueWidget->addChild(valueField);

    valueField = new KNumberField ( getTY());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSeparatedMatrix::setTY );
    inspector->addPickable(valueField);
    valueWidget->addChild(valueField);

    valueField = new KNumberField (getTZ());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSeparatedMatrix::setTZ );
    inspector->addPickable(valueField);
    valueWidget->addChild(valueField);
        
    inspector->addValueWidget(valueWidget);
}

// --------------------------------------------------------------------------------------------------------
void KHandle::initInspectorSize ( KModuleInspector * inspector )
{    
    KWidgetArray * valueWidget = new KWidgetArray ();
    valueWidget->addChild(new KLabel("size    "));

    KNumberField * valueField = new KNumberField (getSX());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSeparatedMatrix::setSX );
    inspector->addPickable(valueField);
    valueWidget->addChild(valueField);

    valueField = new KNumberField (getSY());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSeparatedMatrix::setSY );
    inspector->addPickable(valueField);
    valueWidget->addChild(valueField);

    valueField = new KNumberField (getSZ());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSeparatedMatrix::setSZ );
    inspector->addPickable(valueField);
    valueWidget->addChild(valueField);
        
    inspector->addValueWidget(valueWidget);
}

// --------------------------------------------------------------------------------------------------------
void KHandle::initInspectorRotation ( KModuleInspector * inspector )
{    
    KWidgetArray * valueWidget = new KWidgetArray ();
    valueWidget->addChild(new KLabel("rotation"));

    KNumberField * valueField = new KNumberField (getRX());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSeparatedMatrix::setRX );
    inspector->addPickable(valueField);
    valueWidget->addChild(valueField);

    valueField = new KNumberField (getRY());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSeparatedMatrix::setRY );
    inspector->addPickable(valueField);
    valueWidget->addChild(valueField);

    valueField = new KNumberField (getRZ());
    valueField->addReceiverCallback(this, (KSetFloatPtr)&KSeparatedMatrix::setRZ );
    inspector->addPickable(valueField);
    valueWidget->addChild(valueField);
        
    inspector->addValueWidget(valueWidget);
}

