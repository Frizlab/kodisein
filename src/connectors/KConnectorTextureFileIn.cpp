/*
 *  KConnectorTextureFileIn.cpp
 *  kodisein
 */

#include "KConnectorTextureFileIn.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorTextureFileIn, KDS_CONNECTOR_TEXTURE_FILE_IN, KDS_CONNECTOR_TEXTURE_FILE_OUT)

// --------------------------------------------------------------------------------------------------------
void KConnectorTextureFileIn::render ()
{
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  1.0, -0.25,  0.25, 0.0);
    glEnd();
}

