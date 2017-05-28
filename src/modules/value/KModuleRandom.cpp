/*
 *  KModuleRandom.cpp
 *  kodisein
 */

#include "KModuleRandom.h"
#include "KWidgetArray.h"
#include "KController.h"
#include "KModules.h"
#include "KLabel.h"
#include "KConnectorValueOut.h"
#include "KConnectorValueIn.h"
#include "KConsole.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 	(KModuleRandom,  KValueModule)
KDS_MODULE_VALUES		(KModuleRandom, "Random", 1.0, 1.0, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KModuleRandom::KModuleRandom () : KValueModule ()
{	
    last_value = 0;
#ifdef WIN32
    old_random = (float)rand()/RAND_MAX;
    new_random = (float)rand()/RAND_MAX;
#else
    old_random = (float)random()/RAND_MAX;
    new_random = (float)random()/RAND_MAX;
#endif

    Controller.modules->addValueModule(this);
        
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
KModuleRandom::~KModuleRandom ()
{    
    Controller.modules->removeValueModule(this);
}

// --------------------------------------------------------------------------------------------------------
void KModuleRandom::randomize ( float newValue )
{
    old_random = new_random;
#ifdef WIN32
	new_random = (float)rand()/RAND_MAX;
#else
    new_random = (float)random()/RAND_MAX;
#endif
}

// --------------------------------------------------------------------------------------------------------
bool KModuleRandom::shouldPropagate ( int time )
{
    if (((KValueConnector*)getConnectorWithName(VALUE_IN))->isConnected() == false)
    {
        return true;
    }
    
    return KValueModule::shouldPropagate(time);
}

// --------------------------------------------------------------------------------------------------------
float KModuleRandom::getValue () const
{
    KValueConnector * inConnector;
    inConnector = (KValueConnector*)getConnectorWithName(VALUE_IN);
    
    if (inConnector->isConnected())
    {
        float newValue = inConnector->getValue();
    
        if (newValue < last_value)
        {
            ((KModuleRandom*)this)->randomize(newValue);
        }
        ((KModuleRandom*)this)->last_value = newValue;
        
        return old_random + newValue * (new_random - old_random);
    }

#ifdef WIN32
	return (float)rand()/RAND_MAX;
#else
    return (float)random()/RAND_MAX;
#endif
}

// --------------------------------------------------------------------------------------------------------
void KModuleRandom::createConnectors ()
{
    KValueConnector * connector;
    
    connector = new KConnectorValueOut( this, VALUE_OUT );
    connector->translate(0.0, 0.8, 0.0);
    connector->makeParentConnector(true);
    addConnector(connector);

    connector = new KConnectorValueIn( this, VALUE_IN );
    connector->translate(0.0, -2*KDS_VALUECONNECTOR_RADIUS, 0.0);
    connector->rotate (0, 0, 180);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleRandom::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    loadId();
    glPushAttrib(GL_LINE_BIT | GL_LIGHTING_BIT);
    glLineWidth(1);    
    glEnable(GL_LIGHTING);
    
    glPushMatrix();
    glTranslated(0.0, KDS_VALUECONNECTOR_RADIUS, 0.0);
    glutSolidTorus(KDS_VALUECONNECTOR_RADIUS/2, KDS_VALUECONNECTOR_RADIUS, 8, 20);
    glPopMatrix();
    
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
void KModuleRandom::addToWidget ( KWidgetArray * valueWidget, int depth )
{
    if (depth > VALUE_MAX_DEPTH) valueWidget->addChild(new KLabel(VALUE_UNKNOWN_STRING));
    else
    {    
        valueWidget->addChild(new KLabel("~"));
        KModule * inModule = getConnectorWithName(VALUE_IN)->getConnectedModule();
        if (inModule && inModule->getClassId() >= KValueModule::classId())
        {
            ((KValueModule*)inModule)->addToWidget (valueWidget, depth+1);
        }
    }
}
