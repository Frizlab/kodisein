/*
 *  KConnectorParticleIn.cpp
 *  kodisein
 */

#include "KConnectorParticleIn.h"
#include "KController.h"

#include <glut.h>

KDS_CONNECTION_VALUES (KConnectorParticleIn, KDS_CONNECTOR_PARTICLE_IN, KDS_CONNECTOR_PARTICLE_OUT)

// --------------------------------------------------------------------------------------------------------
void KConnectorParticleIn::render ()
{
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutSolidTorus(0.25, 0.5, 8, Controller.getFastDisplay() ? 4 : 8);
    glPopMatrix();
}
