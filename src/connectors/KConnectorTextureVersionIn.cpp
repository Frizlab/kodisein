/*
 *  KConnectorTextureVersionIn.cpp
 *  kodisein
 */

#include "KConnectorTextureVersionIn.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorTextureVersionIn, KDS_CONNECTOR_TEXTURE_VERSION_IN, KDS_CONNECTOR_TEXTURE_VERSION_OUT)

// --------------------------------------------------------------------------------------------------------
void KConnectorTextureVersionIn::render ()
{
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  1.0, -0.25,  0.25, 0.0);
    glEnd();
}

