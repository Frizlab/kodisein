/*
 *  KModuleAccu.cpp
 *  kodisein
 */

#include "KModuleAccu.h"
#include "KWidgetArray.h"
#include "KLabel.h"
#include "KConnectorValueOut.h"
#include "KConnectorValueIn.h"
#include "KBoolValueObject.h"
#include "KConsole.h"
#include "KController.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 	(KModuleAccu,  KValueModule)
KDS_MODULE_VALUES		(KModuleAccu, "Accu", 1.0, 1.0, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleAccu::KModuleAccu () : KValueModule ()
{
    increment = true;
    reset();
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleAccu::reset ()
{
    accu_value = 0.0;
    old_value  = 0.0;
    old_reset  = 0.0;
    
    propagateValue(0);
}

// --------------------------------------------------------------------------------------------------------
float KModuleAccu::getValue () const
{
    KValueConnector * valueConnector, * resetConnector;
    resetConnector = (KValueConnector*)getConnectorWithName(RESET_IN);
    valueConnector = (KValueConnector*)getConnectorWithName(VALUE_IN);
    
    float newReset = resetConnector->getValue();
            
    if (newReset < old_reset) 
    {
        ((KModuleAccu*)this)->reset();
    }
    ((KModuleAccu*)this)->old_reset = newReset;

    float newValue = valueConnector->getValue();
            
    if (newValue < old_value)
    {
        if (increment)
        {
            ((KModuleAccu*)this)->accu_value += old_value;
        }
        else
        {
            ((KModuleAccu*)this)->accu_value -= old_value;
        }
    }
    
    ((KModuleAccu*)this)->old_value = newValue;
    
    if (increment)
    {
        return accu_value + newValue;
    }
        
    return accu_value - newValue;
}

// --------------------------------------------------------------------------------------------------------
void KModuleAccu::createConnectors ()
{
    KBoolValueObject * value;

    value = new KBoolValueObject ("increment"); 
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KModuleAccu::setIncrement);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KModuleAccu::getIncrement);      

    KValueConnector * connector;
    
    connector = new KConnectorValueOut( this, VALUE_OUT );
    connector->translate(0.0, 0.8, 0.0);
    connector->makeParentConnector(true);
    addConnector(connector);

    connector = new KConnectorValueIn( this, VALUE_IN );
    connector->translate(0.0, -2*KDS_VALUECONNECTOR_RADIUS, 0.0);
    connector->rotate (0, 0, 180);
    addConnector(connector);
    
    connector = new KConnectorValueIn( this, RESET_IN );
    connector->translate (0, KDS_VALUECONNECTOR_RADIUS, KDS_VALUECONNECTOR_RADIUS);
    connector->rotate (90, 0, 0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleAccu::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    loadId();
    glPushAttrib(GL_LINE_BIT | GL_LIGHTING_BIT);
    glLineWidth(1);    
    glEnable(GL_LIGHTING);
    
    glPushMatrix();
    glutSolidCube(KDS_VALUECONNECTOR_RADIUS);
    glTranslated(0.0, 2*KDS_VALUECONNECTOR_RADIUS, 0.0);
    glutSolidCube(KDS_VALUECONNECTOR_RADIUS);
    glTranslated(-KDS_VALUECONNECTOR_RADIUS, -KDS_VALUECONNECTOR_RADIUS, 0.0);
    glutSolidCube(KDS_VALUECONNECTOR_RADIUS);
    glTranslated( 2*KDS_VALUECONNECTOR_RADIUS, 0.0, 0.0);
    glutSolidCube(KDS_VALUECONNECTOR_RADIUS);
    glPopMatrix();
    
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
void KModuleAccu::addToWidget ( KWidgetArray * valueWidget, int depth )
{
    if (depth > VALUE_MAX_DEPTH) valueWidget->addChild(new KLabel(VALUE_UNKNOWN_STRING));
    else
    {    
        valueWidget->addChild(new KLabel(increment ? "++" : "--"));
        KModule * inModule = getConnectorWithName(VALUE_IN)->getConnectedModule();
        if (inModule && inModule->getClassId() >= KValueModule::classId())
        {
            ((KValueModule*)inModule)->addToWidget (valueWidget, depth+1);
        }
                    
        KModule * switchModule = getConnectorWithName(RESET_IN)->getConnectedModule();
        if (switchModule)
        {
            valueWidget->addChild(new KLabel("|"));
            ((KValueModule*)switchModule)->addToWidget (valueWidget, depth+1);
            valueWidget->addChild(new KLabel("|"));            
        }
    }
}
