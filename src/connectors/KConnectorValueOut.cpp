/*
 *  KConnectorValueOut.cpp
 *  kodisein
 */

#include "KConnectorValueOut.h"
#include "KController.h"
#include "KValueModule.h"
#include "KProjection.h"
#include "KModules.h"
#include "KConsole.h"
#include "KTools.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1(KConnectorValueOut, KValueConnector)
const int KConnectorValueOut::type = KDS_CONNECTOR_VALUE_OUT;
const int KConnectorValueOut::connection_type = KDS_CONNECTOR_VALUE_IN;

// --------------------------------------------------------------------------------------------------------
float KConnectorValueOut::getValue () const
{ 
    return ((KValueModule*)module)->getValue();
}
 
// --------------------------------------------------------------------------------------------------------
void KConnectorValueOut::render ()
{
    glPushAttrib(GL_LINE_BIT | GL_LIGHTING_BIT);
    glLineWidth(1);
    glEnable(GL_LIGHTING);
    
    glPushMatrix();
    glTranslated(0.0, -KDS_VALUECONNECTOR_RADIUS, 0.0);

    int subdivisions = (Controller.getFastDisplay() ? 4 : 8);
    
    glPushMatrix();
    glTranslated(0.0, sin(M_PI/subdivisions)*KDS_VALUECONNECTOR_RADIUS, 0.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    kDisplaySolidCylinder(cos(M_PI/subdivisions)*KDS_VALUECONNECTOR_RADIUS, 0.0, KDS_VALUECONNECTOR_RADIUS*2.0f, subdivisions);
    glPopMatrix();
    glPushMatrix();
    glRotated(-90, 1.0, 0.0, 0.0);
    kDisplaySolidSphere(KDS_VALUECONNECTOR_RADIUS, subdivisions);
    glPopMatrix();

    glPopMatrix();
    
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
string KConnectorValueOut::getIdString () const
{ 
    return kStringPrintf("%ld", object_id); 
}

// --------------------------------------------------------------------------------------------------------
void KConnectorValueOut::setXMLAttributes ( const string & attributes )
{
    string idString = kXMLReadNamedAttribute(attributes, "id");
    if (!idString.empty())
    {
        setObjectId(atol(idString.c_str()));
    }
}

// --------------------------------------------------------------------------------------------------------
string KConnectorValueOut::getXMLAttributes ( bool targetIsPasteBuffer ) const
{
    if (targetIsPasteBuffer) return KConnector::getXMLAttributes(targetIsPasteBuffer);
    else return (KConnector::getXMLAttributes(targetIsPasteBuffer) + kStringPrintf(" id='%ld'", object_id));
}

// --------------------------------------------------------------------------------------------------------
string KConnectorValueOut::getXML ( int depth, bool targetIsPasteBuffer ) const
{
    string xml = KConnector::getXML(depth, targetIsPasteBuffer);
    if (xml == "" && connected_connectors.empty() == false && targetIsPasteBuffer == false)
    {
        xml = kXMLTag("Connector", getXMLAttributes(targetIsPasteBuffer), depth);
    }
    return xml;
}
