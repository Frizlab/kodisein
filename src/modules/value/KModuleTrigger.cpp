/*
 *  KModuleTrigger.cpp
 *  kodisein
 */

#include "KModuleTrigger.h"
#include "KController.h"
#include "KModules.h"
#include "KKeyHandler.h"
#include "KWidgetArray.h"
#include "KLabel.h"
#include "KModulator.h"
#include "KConnectorValueOut.h"
#include "KConnectorValueIn.h"
#include "KKeyValueObject.h"
#include "KConsole.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 	(KModuleTrigger,  KActivationValueModule)
KDS_MODULE_VALUES		(KModuleTrigger, "Trigger", 0.0, 0.0, 1.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleTrigger::KModuleTrigger () : KActivationValueModule ()
{	
    last_time = 0;
        
    Controller.modules->addValueModule(this);
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
KModuleTrigger::~KModuleTrigger ()
{
    Controller.modules->removeValueModule(this);
}

// --------------------------------------------------------------------------------------------------------
void KModuleTrigger::activate ()
{
    activated = true;
    last_time = SDL_GetTicks();
}

// --------------------------------------------------------------------------------------------------------
float KModuleTrigger::getValue () const
{
    if (activated)
    {
        unsigned int now = SDL_GetTicks();
        KValueConnector * inConnector = (KValueConnector*)getConnectorWithName(VALUE_IN);
    
        if (inConnector->isConnected())
        {
            float inValue = inConnector->getValue();
            float secDiff = (now - last_time) / 1000.0;
            if (secDiff > inValue)
            {
                ((KModuleTrigger*)this)->deactivate();
                return 0.0;
            }
            else
            {
                return secDiff/inValue;
            }
        }
        else
        {
            ((KModuleTrigger*)this)->deactivate();
            return 1.0;
        }
    }
    else
    {
        ((KModuleTrigger*)this)->last_time = 0;
        return 0.0;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleTrigger::createConnectors ()
{
    KValueObject * value;

    value = new KKeyValueObject( "activation key" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KModuleTrigger::setActivationKey);
    values.back()->setProviderCallback(this, (KGetStringPtr)&KModuleTrigger::getActivationKey);

    KValueConnector * connector;
    
    connector = new KConnectorValueOut( this, VALUE_OUT );
    connector->translate(0.0, 0.8, 0.0);
    connector->makeParentConnector(true);
    addConnector(connector);

    connector = new KConnectorValueIn( this, VALUE_IN );
    connector->rotate (0, 0, 180);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleTrigger::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    loadId();
    glPushAttrib(GL_LINE_BIT | GL_LIGHTING_BIT);
    glLineWidth(1);    
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslated(0.0, 2*KDS_VALUECONNECTOR_RADIUS, 0.0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glutSolidTorus(KDS_VALUECONNECTOR_RADIUS, KDS_VALUECONNECTOR_RADIUS, 8, 20);
    glPopMatrix();
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
string KModuleTrigger::getDisplayName () const
{ 
    return kStringPrintf("[%s %s]", getName().c_str(), activation_key.c_str()); 
}

// --------------------------------------------------------------------------------------------------------
void KModuleTrigger::initInspector ( KModuleInspector * inspector )
{
    KModule::initInspector(inspector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleTrigger::addToWidget ( KWidgetArray * valueWidget, int depth )
{
    if (depth > VALUE_MAX_DEPTH) valueWidget->addChild(new KLabel(VALUE_UNKNOWN_STRING));
    else
    {    
        valueWidget->addChild(new KLabel(activation_key));
        KModule * inModule = getConnectorWithName(VALUE_IN)->getConnectedModule();
         if (inModule && inModule->getClassId() >= KValueModule::classId())
         {
            valueWidget->addChild(new KLabel("<"));
            ((KValueModule*)inModule)->addToWidget (valueWidget, depth+1);
            valueWidget->addChild(new KLabel(">"));
         }
    }
}
