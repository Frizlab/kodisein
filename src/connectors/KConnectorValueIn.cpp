/*
 *  KConnectorValueIn.cpp
 *  kodisein
 */

#include "KConnectorValueIn.h"
#include "KConnectorValueInOut.h"
#include "KController.h"
#include "KModules.h"
#include "KValueModule.h"
#include "KModuleVariable.h"
#include "KProjection.h"
#include "KConsole.h"
#include "KTools.h"

#include <glut.h>

KDL_CLASS_INTROSPECTION_1(KConnectorValueIn, KValueConnector)
const int KConnectorValueIn::type = KDS_CONNECTOR_VALUE_IN;
const int KConnectorValueIn::connection_type = KDS_CONNECTOR_VALUE_OUT;

// --------------------------------------------------------------------------------------------------------
KConnectorValueIn::KConnectorValueIn ( KModule * m, const string & n ) : KValueConnector(m, n)
{
    parent_connector = false;
    time   = 0;
    value  = 0.0;
}

// --------------------------------------------------------------------------------------------------------
void KConnectorValueIn::connectWithConnector ( KConnector * c )
{
    KConnector::connectWithConnector(c);
    
    if (c->getModule()->getClassId() >= KModuleVariable::classId())
    {
        value = ((KModuleVariable*)c->getModule())->getValue();
    }
    else if (c->getClassId() >= KConnectorValueInOut::classId())
    {
        value = ((KConnectorValueIn*)c)->getValue();
    }

    time = 0;
}

// --------------------------------------------------------------------------------------------------------
void KConnectorValueIn::setValue ( float newValue )
{
    if (value != newValue)
    {
        value = newValue;
        time  = Controller.frame_time;
        ((KValueModule*)module)->propagateValue(time);
    }
    else if (time != Controller.frame_time)
    {
        time  = 0;
    }
}

// --------------------------------------------------------------------------------------------------------
void KConnectorValueIn::render ()
{
    glLineWidth(1);

    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslated(0.0, -KDS_VALUECONNECTOR_RADIUS, 0.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    
    kDisplaySolidSphere(KDS_VALUECONNECTOR_RADIUS, (Controller.getFastDisplay() ? 4 : 8));
    glPopMatrix();
    
    if (isConnected() && Controller.modules->flags[KDS_MODULES_FLAG_SHOW_MODULATORS] && 
        Controller.modules->flags[KDS_MODULES_FLAG_SHOW_CONNECTIONS])
    {
        glLineWidth  (KDS_CONNECTOR_LINE_WIDTH);
        glDisable    (GL_LIGHTING);
        
        KConnector * oc = connected_connectors[0];
          
        glPushMatrix();
        
        getInverse().glMultMatrix(); // undo connector transformation
        module->getInverse().glMultMatrix(); // undo module transformation

        glBegin(GL_LINES);
        ((*module) * (*this)).getPosition().glVertex();
        ((*(oc->getModule())) * (*oc)).getPosition().glVertex();
        glEnd();
        
        glPopMatrix();
    }
}

