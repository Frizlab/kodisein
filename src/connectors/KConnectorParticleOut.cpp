/*
 *  KConnectorParticleOut.cpp
 *  kodisein
 */

#include "KConnectorParticleOut.h"
#include "KController.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorParticleOut, KDS_CONNECTOR_PARTICLE_OUT, KDS_CONNECTOR_PARTICLE_IN)

// --------------------------------------------------------------------------------------------------------
void KConnectorParticleOut::render ()
{
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    kDisplaySolidSphere(0.5, Controller.getFastDisplay() ? 4 : 8);
    glPopMatrix();
}
