/*
 *  KConnectorTextureBatchIn.cpp
 *  kodisein
 */

#include "KConnectorTextureBatchIn.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorTextureBatchIn, KDS_CONNECTOR_TEXTURE_BATCH_IN, KDS_CONNECTOR_TEXTURE_BATCH_OUT)

// --------------------------------------------------------------------------------------------------------
void KConnectorTextureBatchIn::render ()
{
    float g = 0.25;
    
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  -g, -1.0,  -g, 0.0);
    RECTANGLE_ZX(   g, 1.0, -1.0,  -g, 0.0);
    RECTANGLE_ZX(   g, 1.0,    g, 1.0, 0.0);
    RECTANGLE_ZX(-1.0,  -g,    g, 1.0, 0.0);
    glEnd();
}
