/*
 *  KModuleSwitch.cpp
 *  kodisein
 */

#include "KModuleSwitch.h"
#include "KValueConnector.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleSwitch, KOperationModule)
KDS_MODULE_VALUES		(KModuleSwitch, "Switch", 0.0, 0.0, 1.0f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleSwitch::KModuleSwitch() : KOperationModule (OPERATION_SWITCH)
{
    old_value = 0.0;
    switched  = false;
}

// --------------------------------------------------------------------------------------------------------
float KModuleSwitch::getValue () const
{
    KValueConnector * v1Connector, * v2Connector, * switchConnector;
    switchConnector = (KValueConnector*)getConnectorWithName(OPERATION_VALUE_IN_SWITCH);
    v1Connector = (KValueConnector*)getConnectorWithName(OPERATION_VALUE_IN_1);
    v2Connector = (KValueConnector*)getConnectorWithName(OPERATION_VALUE_IN_2);
    
    float newValue = switchConnector->getValue();

    if (newValue < old_value)
    {
        ((KModuleSwitch*)this)->switched = !switched;
    }
    
    ((KModuleSwitch*)this)->old_value = newValue;
    
    if (switched)
    {
        return v2Connector->getValue();
    }
    else
    {
        return v1Connector->getValue();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleSwitch::displayConnectors ( int mode )
{
    PickableVector::iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        if (((KConnector*)*iter)->getName() == OPERATION_VALUE_IN_SWITCH)
        {
            module_color = KColor(0.5, 0.5, 1.0, 0.6);
            ((KConnector*)*iter)->display();
            module_color = KColor(0.0, 0.0, 1.0, 0.6);
        }
        else
        {
            ((KConnector*)*iter)->display();
        }
        iter++;
    }
}

