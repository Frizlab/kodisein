/*
 *  KConnectorTextureVersionOut.cpp
 *  kodisein
 */

#include "KConnectorTextureVersionOut.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorTextureVersionOut, KDS_CONNECTOR_TEXTURE_VERSION_OUT, KDS_CONNECTOR_TEXTURE_VERSION_IN)

// --------------------------------------------------------------------------------------------------------
void KConnectorTextureVersionOut::render ()
{
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  1.0, -0.25,  0.25, -0.25);
    glEnd();
}


