/*
 *  KConnectorModulatorIn.cpp
 *  kodisein
 */

#include "KConnectorModulatorIn.h"
#include "KModule.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorModulatorIn, KDS_CONNECTOR_MODULATOR_IN, KDS_CONNECTOR_MODULATOR_OUT)

// --------------------------------------------------------------------------------------------------------
void KConnectorModulatorIn::render ()
{
    glPushMatrix();
    glTranslatef(0.0f, -KDS_CONNECTOR_MIN_DISTANCE, 0.0f);
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  1.0, -0.5,  0.5, 0.0);
    glEnd();
    glPopMatrix();
}
