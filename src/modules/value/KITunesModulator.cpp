/*
 *  KITunesModulator.cpp
 *  kodisein
 */

#include "KITunesModulator.h"
#include "KConnectorValueIn.h"
#include "KConnectorValueOut.h"
#include "KConnectorModulatorIn.h"
#include "KConnectorModulatorOut.h"
#include "KKeyValueObject.h"
#include "KStringTools.h"
#include "KKey.h"
#include "KController.h"
#include "KModules.h"
#include "KGlobalModulator.h"
#include "KPreferences.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 	(KITunesModulator, KModulator)
KDS_MODULE_VALUES		(KITunesModulator, "iTunesModulator", 1.0, 0.0, 0.0, 0.6)

// --------------------------------------------------------------------------------------------------------
KITunesModulator::KITunesModulator () : KModulator (false)
{
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
float KITunesModulator::getITunesValue ( int index )
{
    std::vector<KModulator*> * modulators = &Controller.modules->global_modulator->modulators;
    std::vector<KModulator*>::iterator iter = modulators->begin();
    while (iter != modulators->end())
    {
        if ((*iter)->getClassId() == KITunesModulator::classId())
        {
            return ((KITunesModulator*)(*iter))->iTunes_values[index];
        }
        iter++;
    }
    
    return 0.0;
}

// --------------------------------------------------------------------------------------------------------
void KITunesModulator::createConnectors ()
{
    int index;
    float ir = sqrt(3), h = 0.5;
        
    KConnector * connector;
    
    connector = new KConnectorValueOut( this, "value out max" );
    connector->translate(0.0, h+KDS_VALUECONNECTOR_RADIUS, 0.0);
    addConnector(connector);
    
    for (index = 1; index < 10; index++)
    {
        connector = new KConnectorValueOut( this, kStringPrintf("value out %d", index) );
        connector->rotate (0.0, index*36, 0.0);
        connector->translate(0.0, h+KDS_VALUECONNECTOR_RADIUS, 1.25);
        addConnector(connector);
    }
    
    connector = new KConnectorModulatorIn (this);
    connector->translate(0.0, 0.0, -ir - KDS_CONNECTOR_MIN_DISTANCE);
    connector->rotate (-90.0, 180.0, 0.0);
    addConnector(connector);

    for (index = 2; index < 7; index++)
    {
        connector = new KConnectorModulatorOut (this, kStringPrintf("modulator %d", index));
        connector->rotate (0.0, ((index % 5) + 1) * 60.0, 0.0);
        connector->translate(0.0, 0.0, -ir);
        connector->rotate (-90.0, 0.0, 0.0);
        addConnector(connector);
    }
    
    KValueObject * value;

    value = new KKeyValueObject( "activation key", 1 );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetStringPtr)&KModulator::setActivationKey);
    values.back()->setProviderCallback(this, (KGetStringPtr)&KModulator::getActivationKey);
}

// --------------------------------------------------------------------------------------------------------
float KITunesModulator::valueForConnector ( KConnector * connector )
{
    return iTunes_values[distance(connectors.begin(), find(connectors.begin(), connectors.end(), connector))];
}

// --------------------------------------------------------------------------------------------------------
void KITunesModulator::propagateValue ( int time )
{
    if (playing == false) return;

    // iterate through connected value out connectors and propagate values to the modules
    KConnector::List valueOutConnectors;
    valueOutConnectors = getConnectorsOfType(KDS_CONNECTOR_VALUE_OUT, KDS_USED_CONNECTOR);
    KConnector::Iter iter = valueOutConnectors.begin();
    while (iter != valueOutConnectors.end())
    {
        // iterate through connected modules and apply modulation or continue propagating
        KConnector::List connectedConnectors = (*iter)->getConnectedConnectors();
        KConnector::Iter conIter = connectedConnectors.begin();
        while (conIter != connectedConnectors.end())
        {
            ((KConnectorValueIn*)*conIter)->setValue(valueForConnector(*iter));
            conIter++;
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KITunesModulator::updateValue ()
{
    if (playing) // update value if playing
    {        
        kGetITunesData (iTunes_values);
        propagateValue (Controller.frame_time);
    }
}

// --------------------------------------------------------------------------------------------------------
bool KITunesModulator::handleKey ( const KKey & key )
{      
    if (key.name == Controller.preferences->getStartStopKey())  playing ? stop() : start();
    return false;
}

