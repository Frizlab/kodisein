/*
 *  KValueModule.cpp
 *  kodisein
 */

#include "KValueModule.h"
#include "KModulator.h"
#include "KNumberField.h"
#include "KConnectorValueInOut.h"
#include "KConnectorValueOut.h"
#include "KController.h"
#include "KConsole.h"

#define DEBUG_VALUES 0

KDL_CLASS_INTROSPECTION_1 	(KValueModule, KModule)

// --------------------------------------------------------------------------------------------------------
KValueModule::KValueModule () : KModule ()
{
}

// --------------------------------------------------------------------------------------------------------
KConnectorValueOut * KValueModule::getTargetOutConnector () const
{
    KConnector * outConnector = getConnectorOfType(KDS_CONNECTOR_VALUE_OUT);
    KConnector * outConnectedConnector = outConnector->getConnectedConnector();
    if (outConnectedConnector &&
        outConnectedConnector->getModule()->getClassId() >= KValueModule::classId())
    {
        return ((KValueModule*)outConnectedConnector->getModule())->getTargetOutConnector();
    }
    return (KConnectorValueOut*)outConnector;
}

// --------------------------------------------------------------------------------------------------------
int KValueModule::getSex () const
{
    KConnector * parentConnector = getParentConnector();
    if (parentConnector) 
    {
        if (parentConnector->getType() == KDS_CONNECTOR_VALUE_OUT)  return VALUEMODULE_SEX_MALE;
        
        return VALUEMODULE_SEX_FEMALE;
    }
    return VALUEMODULE_SEX_NEUTRUM;
}

// --------------------------------------------------------------------------------------------------------
void KValueModule::changeSex ( int sex )
{            
    ((KValueConnector*)getConnectorWithName(VALUE_OUT))->makeParentConnector
                                                                        (sex == VALUEMODULE_SEX_MALE);    
    ((KValueConnector*)getConnectorWithName(VALUE_IN))->makeParentConnector
                                                                        (sex == VALUEMODULE_SEX_FEMALE);
    KModule * outModule = getConnectorWithName(VALUE_OUT)->getConnectedModule();
    if (sex != VALUEMODULE_SEX_NEUTRUM && 
        outModule && outModule->getClassId() >= KValueModule::classId() &&
        ((KValueModule*)outModule)->getSex() != sex)
    {
        ((KValueModule*)outModule)->changeSex(sex);
    }
}

// --------------------------------------------------------------------------------------------------------
bool KValueModule::connectModule 
                    ( KModule * otherModule, KConnector * ownConnector, KConnector * otherConnector )
{
    if (ownConnector && ownConnector->getClassId() >= KConnectorValueOut::classId() && 
        (otherModule->getClassId() >= KValueModule::classId()))
    {
        if ((getSex() == VALUEMODULE_SEX_FEMALE) && 
            (((KValueModule*)otherModule)->getSex() != VALUEMODULE_SEX_FEMALE) &&
             ((KValueModule*)otherModule)->getTargetOutConnector()->isConnected() == false)
        {
            if (ownConnector->isUnlimited() && ownConnector->getConnectedChildConnector())
            {
                // ownConnector has already a child connected -> make other module a neutrum
                ((KValueModule*)otherModule)->changeSex(VALUEMODULE_SEX_NEUTRUM);
            }
            else
            {
                ((KValueModule*)otherModule)->changeSex(VALUEMODULE_SEX_FEMALE);
            }
        }
    }
    return KModule::connectModule (otherModule, ownConnector, otherConnector);    
}

// --------------------------------------------------------------------------------------------------------
void KValueModule::initInspector ( KModuleInspector * inspector )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    KNumberField * valueField;
    int depth = 0;

    string titleString = getDisplayName();
    KConnector * pickedConnector = getPickedConnector();
    if (pickedConnector) titleString += " " + pickedConnector->getName();
    inspector->setTitle(titleString);

    KConnector * outConnector = getConnectorOfType(KDS_CONNECTOR_VALUE_OUT, KDS_USED_CONNECTOR);
    if (outConnector) outConnector = outConnector->getConnectedConnector();
    if (outConnector && (outConnector->getModule()->getClassId() >= KValueModule::classId()) == false)
    {
        KLabel * label = new KLabel(outConnector->getName());
        valueWidget->addChild(label);

        inspector->setTitle(titleString + " > " + outConnector->getDisplayName());

        if (outConnector->getClassId() == KConnectorValueInOut::classId())
        {
            valueField = new KNumberField (((KConnectorValueIn*)outConnector)->getValue());
            valueField->addReceiverCallback((KConnectorValueIn*)outConnector,
                                                    (KSetFloatPtr)&KConnectorValueIn::setValue);
            inspector->addPickable(valueField);
            valueWidget->addChild(valueField);
        }
        else
        {
            KLabel * label = new KLabel(kStringPrintf("[0,%d]", 
                                                ((KConnectorValueInOut*)outConnector)->getRangeSize()-1));
            valueWidget->addChild(label);
        }
        depth = 1;
    }
    else
    {
        KLabel * label = new KLabel("... <");
        valueWidget->addChild(label);
    }

    inspector->addValueWidget(valueWidget);

    addToWidget(valueWidget, depth);
        
    vector<KValueObject*>::const_iterator valueIter = values.begin();
    while(valueIter != values.end())
    {	
        (*valueIter)->addToWidget(inspector->getValuesWidget());
        valueIter++;
    }

    inspector->layout();
}

// --------------------------------------------------------------------------------------------------------
bool KValueModule::shouldPropagate (int time)
{
    bool propagate = false;
    
    // find connected value in connectors
    vector<KConnector*> valueInConnectors;
    valueInConnectors = getConnectorsOfType(KDS_CONNECTOR_VALUE_IN, KDS_USED_CONNECTOR);
    vector<KConnector*>::iterator conIter = valueInConnectors.begin();
    while (conIter != valueInConnectors.end())
    {    
        if (((KConnectorValueIn*)*conIter)->time == Controller.frame_time)
        {
            // found a value in connector that was changed in this frame -> continue propagation
            propagate = true;
            break;
        }
        conIter++;
    }
    
    if (propagate) // mark all input connectors unchanged
    {
        conIter = valueInConnectors.begin();
        while (conIter != valueInConnectors.end())
        {    
            ((KConnectorValueIn*)*conIter)->time = 0;
            conIter++;
        }
    }
    
    return propagate;
}

// --------------------------------------------------------------------------------------------------------
void KValueModule::propagateValue ( int time )
{
    if (shouldPropagate(time) == false)
    {
        return;
    }
    
    float outValue = getValue();

    // iterate through connected value out connectors and propagate values to the modules
    vector<KConnector*> valueOutConnectors;
    valueOutConnectors = getConnectorsOfType(KDS_CONNECTOR_VALUE_OUT, KDS_USED_CONNECTOR);
    vector<KConnector*>::iterator iter = valueOutConnectors.begin();
    while (iter != valueOutConnectors.end())
    {
        // iterate through connected modules and apply modulation or continue propagating
        vector<KConnector*> connectedConnectors = (*iter)->getConnectedConnectors();
        vector<KConnector*>::iterator conIter = connectedConnectors.begin();
        while (conIter != connectedConnectors.end())
        {
            ((KConnectorValueIn*)*conIter)->setValue(outValue);
            conIter++;
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KValueModule::getLeafConnectors ( vector<KConnectorValueInOut*> & leafConnectors )
{
    vector<KConnector*> valueOutConnectors;
    valueOutConnectors = getConnectorsOfType(KDS_CONNECTOR_VALUE_OUT, KDS_USED_CONNECTOR);
    vector<KConnector*>::iterator iter = valueOutConnectors.begin();
        
    while (iter != valueOutConnectors.end()) // loop through conntected value out connectors
    {
        vector<KConnector*> connectedConnectors = (*iter)->getConnectedConnectors();
        vector<KConnector*>::iterator conIter = connectedConnectors.begin();
        while (conIter != connectedConnectors.end()) // loop through connected connectors
        {
            if ((*conIter)->getClassId() >= KConnectorValueInOut::classId())
            {
                // we found a KConnectorValueInOut -> add it to the leaf connectors, if not already included
                if (find(leafConnectors.begin(), leafConnectors.end(), *conIter) == leafConnectors.end())
                {
                    leafConnectors.push_back((KConnectorValueInOut*)*conIter);
                }
            }
            else
            {
                ((KValueModule*)(*conIter)->getModule())->getLeafConnectors(leafConnectors);
            }
            conIter++;
        }
        iter++;
    }
}
