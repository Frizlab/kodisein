/*
 *  KFilterModule.cpp
 *  kodisein
 */

#include "KFilterModule.h"
#include "KModulator.h"
#include "KNumberField.h"
#include "KBoolValueObject.h"
#include "KFloatValueObject.h"
#include "KConnectorValueInOut.h"
#include "KConnectorValueIn.h"
#include "KConnectorValueOut.h"
#include "KConsole.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_1 (KFilterModule, KValueModule)

KDL_CLASS_INTROSPECTION_1 	(KModuleInvert, KFilterModule)
KDS_MODULE_VALUES		(KModuleInvert, "Invert", 1.0f, 1.0f, 0.0, 0.6f)

KDL_CLASS_INTROSPECTION_1 	(KModuleAttack, KFilterModule)
KDS_MODULE_VALUES 		(KModuleAttack, "Attack", 1.0f, 0.0, 0.0, 0.6f)

KDL_CLASS_INTROSPECTION_1 	(KModuleDecay, KFilterModule)
KDS_MODULE_VALUES 		(KModuleDecay, "Decay", 0.0, 1.0f, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KFilterModule::KFilterModule ( int type ) : KValueModule ()
{	
    filter_type = type;
    pos 	= 0.0;
    length 	= 1.0;
    smooth	= true;
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
float KFilterModule::getValue () const
{
    KValueConnector * inConnector = (KValueConnector*)getConnectorWithName(VALUE_IN);

    GLfloat inValue = inConnector->getValue();
    
    if (inValue >= pos && inValue <= pos + length)
    {
        if (filter_type == FILTER_INVERT) 
        {
            return 1.0 - inValue;
        }
        else 
        {
            float mapped = (inValue-pos)/length;
            
            if (smooth)
            {
                mapped = sin((mapped-0.5)*M_PI)/2.0+0.5;
            }
            
            if (filter_type == FILTER_ATTACK) 
            {
                return mapped;
            }
            else if (filter_type == FILTER_DECAY)  
            {
                return 1.0-mapped;
            }
        }
    }
    else
    {
        if (filter_type == FILTER_INVERT) 
        {
            return inValue;
        }
        else 
        {
            return 0.0;
        }
    }
    
    return 0.0;
}

// --------------------------------------------------------------------------------------------------------
void KFilterModule::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    
    glPushMatrix();
    glTranslated(0.0, -KDS_VALUECONNECTOR_RADIUS*4,0.0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    kDisplaySolidCylinder(KDS_VALUECONNECTOR_RADIUS*2, 0, KDS_VALUECONNECTOR_RADIUS*2, 10);
    glRotated(180.0, 1.0, 0.0, 0.0);
    kDisplaySolidCylinder(KDS_VALUECONNECTOR_RADIUS*2, 0, KDS_VALUECONNECTOR_RADIUS*2, 10);
    glPopMatrix();
}

// --------------------------------------------------------------------------------------------------------
void KFilterModule::createConnectors ()
{
    KValueConnector * connector;
    
    connector = new KConnectorValueOut( this, VALUE_OUT );
    addConnector(connector);

    connector = new KConnectorValueIn( this, VALUE_IN );
    connector->makeParentConnector(true);
    connector->translate (0, -KDS_VALUECONNECTOR_RADIUS*6, 0);
    connector->rotate (0, 0, 180);
    addConnector(connector);

    KValueObject * value;

    value = new KFloatValueObject( "pos" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetFloatPtr)&KFilterModule::setStartPos);
    values.back()->setProviderCallback(this, (KGetFloatPtr)&KFilterModule::getStartPos);      

    value = new KFloatValueObject( "length" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetFloatPtr)&KFilterModule::setLength);
    values.back()->setProviderCallback(this, (KGetFloatPtr)&KFilterModule::getLength);      

    if (filter_type != FILTER_INVERT)
    {
        value = new KBoolValueObject( "smooth" );
        values.push_back(value);
        values.back()->addReceiverCallback(this, (KSetBoolPtr)&KFilterModule::setSmooth);
        values.back()->setProviderCallback(this, (KGetBoolPtr)&KFilterModule::getSmooth);      
    }
}

// --------------------------------------------------------------------------------------------------------
void KFilterModule::addToWidget ( KWidgetArray * valueWidget, int depth )
{
    if (depth >= VALUE_MAX_DEPTH) valueWidget->addChild(new KLabel(VALUE_UNKNOWN_STRING));
    else
    {
        string rangeString = kStringPrintf("[%g %g]", pos, length);
        if      (filter_type == FILTER_INVERT) valueWidget->addChild(new KLabel("!" + rangeString));
        else if (filter_type == FILTER_ATTACK) valueWidget->addChild(new KLabel("^" + rangeString));
        else if (filter_type == FILTER_DECAY)  valueWidget->addChild(new KLabel("v" + rangeString));

        KModule * inModule = getConnectorWithName(VALUE_IN)->getConnectedModule();
        if (inModule && inModule->getClassId() >= KValueModule::classId())
        {	
            ((KValueModule*)inModule)->addToWidget (valueWidget, depth+1);
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KFilterModule::initInspector ( KModuleInspector * inspector )
{
    KModule::initInspector(inspector);
}

