/*
 *  KConnectorModulatorOut.cpp
 *  kodisein
 */

#include "KConnectorModulatorOut.h"
#include "KObjectModule.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorModulatorOut, KDS_CONNECTOR_MODULATOR_OUT, KDS_CONNECTOR_MODULATOR_IN)

// --------------------------------------------------------------------------------------------------------
void KConnectorModulatorOut::render ()
{
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  1.0, -0.5,  0.5, 0.0);
    glEnd();
}
