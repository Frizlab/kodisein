/*
 *  KOperationModule.cpp
 *  kodisein
 */

#include "KOperationModule.h"
#include "KModulator.h"
#include "KNumberField.h"
#include "KConnectorValueInOut.h"
#include "KConnectorValueOut.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 	(KOperationModule, KValueModule)

KDL_CLASS_INTROSPECTION_1 	(KModuleAdd, KOperationModule)
KDS_MODULE_VALUES		(KModuleAdd, "Add", 0.0, 1.0f, 0.0, 0.6f)

KDL_CLASS_INTROSPECTION_1 	(KModuleMultiply, KOperationModule)
KDS_MODULE_VALUES		(KModuleMultiply, "Multiply", 1.0f, 0.0, 0.0, 0.6f)

KDL_CLASS_INTROSPECTION_1 	(KModuleModulo, KOperationModule)
KDS_MODULE_VALUES		(KModuleModulo, "Modulo", 1.0f, 1.0f, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KOperationModule::KOperationModule ( int o ) : KValueModule ()
{	
    operation = o;
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
KOperationModule::~KOperationModule ()
{
    disconnect();
}

// --------------------------------------------------------------------------------------------------------
void KOperationModule::disconnect ()
{
    // disconnect connected io connectors first, to avoid problems when rechaining im KModule::disconnect
    PickableVector::iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        KConnector * connector = (KConnector*)*iter;
        if (!(connector->getName() == VALUE_OUT) &&
            connector->getConnectedModule() &&
            (connector->getConnectedModule()->getClassId() >= KValueModule::classId()) == false)
        {
            connector->disconnect();
        }
        iter++;
    }
    KModule::disconnect();
}

// --------------------------------------------------------------------------------------------------------
void KOperationModule::disconnectConnector ( KConnector * connector )
{
    if (connector->getName() == VALUE_OUT)
    {
        KConnector * inConnector = getConnectorWithName(OPERATION_VALUE_IN_1);
        KModule * inModule = inConnector->getConnectedModule();
        if (inModule == NULL || inModule->getClassId() >= KValueModule::classId())
        {
            inConnector = getConnectorWithName(OPERATION_VALUE_IN_2);
            inModule = inConnector->getConnectedModule();
        }
        if (inModule && (inModule->getClassId() >= KValueModule::classId()) == false)
        {
            inConnector->disconnect();
            resetInConnectors();
        }
    }
    KModule::disconnectConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KOperationModule::connectInOutConnector ( KConnectorValueInOut * ioConnector )
{
    KValueConnector * viConnector    = (KValueConnector*)getConnectorWithName(OPERATION_VALUE_IN_1);
    KValueConnector * otherConnector = (KValueConnector*)getConnectorWithName(OPERATION_VALUE_IN_2);
    
    if (viConnector->isConnected())
    {
        // first in connector is used -> exchange with second in connector
        KValueConnector * tmp = viConnector;
        viConnector = otherConnector;
        otherConnector = tmp;
    }
    
    if (viConnector->isConnected()) 
    {
        // both in connectors already used -> do nothing
        return;
    }

    // first in connector is free -> connect with inout connector
    viConnector->connectWithConnector(ioConnector);
        
    viConnector->reset();
    viConnector->scale(0.0, 0.0, 0.0);
    otherConnector->reset();
    otherConnector->translate(0,-KDS_VALUECONNECTOR_RADIUS * 4,0);
    otherConnector->rotate(0, 0, 180);
    
    updateChildren();
}

// --------------------------------------------------------------------------------------------------------
float KOperationModule::getValue () const
{
    KValueConnector * v1Connector, * v2Connector;
    v1Connector = (KValueConnector*)getConnectorWithName(OPERATION_VALUE_IN_1);
    v2Connector = (KValueConnector*)getConnectorWithName(OPERATION_VALUE_IN_2);
    
    GLfloat v1 = v1Connector->getValue();
    GLfloat v2 = v2Connector->getValue();
    
    if (operation == OPERATION_MULTIPLY) return    v1 * v2;
    else if (operation == OPERATION_ADD) return    v1 + v2;
    else if (operation == OPERATION_MODULO) 
    {
        if (v2 != 0) 
        {
            return v1 - floor (v1 / v2) * v2;
        }
        else return v1;
    }
    
    return 0.0;
}

// --------------------------------------------------------------------------------------------------------
void KOperationModule::changeSex ( int sex )
{            
    ((KValueConnector*)getConnectorWithName(VALUE_OUT))->makeParentConnector
                                                                        (sex == VALUEMODULE_SEX_MALE);    
    ((KValueConnector*)getConnectorWithName(OPERATION_VALUE_IN_1))->makeParentConnector
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
void KOperationModule::resetInConnectors ()
{
    KConnector * connector;
    float x = cos(DEG2RAD(30))*KDS_VALUECONNECTOR_RADIUS*2.13;
    float y = (1+sin(DEG2RAD(30)))*KDS_VALUECONNECTOR_RADIUS*2.13;
    
    connector = getConnectorWithName(OPERATION_VALUE_IN_1);
    connector->reset();
    if (operation == OPERATION_MULTIPLY)
    {
        connector->translate (-x, -y, 0);
        connector->rotate (0, 0, 120);
    }
    else
    {
        connector->translate (0, -y, -x); 
        connector->rotate (-120, 0, 0);
    }

    connector = getConnectorWithName(OPERATION_VALUE_IN_2);
    connector->reset();
    if (operation == OPERATION_MULTIPLY)
    {
        connector->translate (x, -y, 0);
        connector->rotate (0, 0, -120);
    }
    else
    {
        connector->translate (0, -y, x);
        connector->rotate (120, 0, 0);
    }
}

// --------------------------------------------------------------------------------------------------------
void KOperationModule::createConnectors ()
{
    KValueConnector * connector;
    
    connector = new KConnectorValueOut( this, VALUE_OUT );
    connector->makeParentConnector(true);
    addConnector(connector);

    connector = new KConnectorValueIn( this, OPERATION_VALUE_IN_1 );
    addConnector(connector);

    connector = new KConnectorValueIn( this, OPERATION_VALUE_IN_2 );
    addConnector(connector);
    
    resetInConnectors();
    
    if (operation == OPERATION_SWITCH)
    {
        connector = new KConnectorValueIn( this, OPERATION_VALUE_IN_SWITCH );
        float x = cos(DEG2RAD(30))*KDS_VALUECONNECTOR_RADIUS*2.13;
        float y = (1+sin(DEG2RAD(30)))*KDS_VALUECONNECTOR_RADIUS*2.13;
        connector->translate (-x, -y, 0);
        connector->rotate (0, 0, 120);
        addConnector(connector);
    }
}

// --------------------------------------------------------------------------------------------------------
void KOperationModule::addToWidget ( KWidgetArray * valueWidget, int depth )
{
    if (depth >= VALUE_MAX_DEPTH)  valueWidget->addChild(new KLabel(VALUE_UNKNOWN_STRING));
    else
    {
        bool ioConnected = false;
        KConnector * v1Connector = getConnectorWithName(OPERATION_VALUE_IN_1);
        KConnector * v2Connector = getConnectorWithName(OPERATION_VALUE_IN_2);

        KModule * v1Module = v1Connector->getConnectedModule();
        KModule * v2Module = v2Connector->getConnectedModule();

        //if (v1Module && (v1Module->getClassId() >= KValueModule::classId()) == false)
        if (v1Module && (v1Connector->getConnectedConnector()->getClassId() >= KConnectorValueInOut::classId()))
        {
            v1Module = NULL;
            ioConnected = true;
        }
        //else if (v2Module && (v2Module->getClassId() >= KValueModule::classId()) == false)
        else if (v2Module && (v2Connector->getConnectedConnector()->getClassId() >= KConnectorValueInOut::classId()))
        {
            v2Module = v1Module;
            v1Module = NULL;
            ioConnected = true;        
        }
        else if (operation == OPERATION_ADD)
        {
            valueWidget->addChild(new KLabel("("));
        }

        if (v1Module && v1Module->getClassId() >= KValueModule::classId())
        {	
            ((KValueModule*)v1Module)->addToWidget (valueWidget, depth+1);
        }
    
        if      (operation == OPERATION_ADD)		valueWidget->addChild(new KLabel("+"));
        else if (operation == OPERATION_MULTIPLY)	valueWidget->addChild(new KLabel("*"));
        else if (operation == OPERATION_MODULO)		valueWidget->addChild(new KLabel("%"));
        else if (operation == OPERATION_SWITCH)		
        {
            valueWidget->addChild(new KLabel("|"));
            KModule * switchModule = getConnectorWithName(OPERATION_VALUE_IN_SWITCH)->getConnectedModule();
            if (switchModule)
            {
                ((KValueModule*)switchModule)->addToWidget (valueWidget, depth+1);
            }
            valueWidget->addChild(new KLabel("|"));            
        }

        if (v2Module && v2Module->getClassId() >= KValueModule::classId())
        {	
            ((KValueModule*)v2Module)->addToWidget (valueWidget, depth+1);
        }
        
        if (ioConnected == false && (operation == OPERATION_ADD))
        {
            valueWidget->addChild(new KLabel(")"));
        }
    }
}


