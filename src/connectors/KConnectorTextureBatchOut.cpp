/*
 *  KConnectorTextureBatchOut.cpp
 *  kodisein
 */

#include "KConnectorTextureBatchOut.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorTextureBatchOut, KDS_CONNECTOR_TEXTURE_BATCH_OUT, KDS_CONNECTOR_TEXTURE_BATCH_IN)

// --------------------------------------------------------------------------------------------------------
void KConnectorTextureBatchOut::render ()
{
    float g = 0.25;
    
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  -g, -1.0,  -g, -2*g);
    RECTANGLE_ZX(   g, 1.0, -1.0,  -g, -2*g);
    RECTANGLE_ZX(   g, 1.0,    g, 1.0, -2*g);
    RECTANGLE_ZX(-1.0,  -g,    g, 1.0, -2*g);
    glEnd();
}
