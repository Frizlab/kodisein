/*
 *  KConnectorMatrixOut.cpp
 *  kodisein
 */

#include "KConnectorMatrixOut.h"
#include "KObjectModule.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorMatrixOut, KDS_CONNECTOR_MATRIX_OUT, KDS_CONNECTOR_MATRIX_IN)

// --------------------------------------------------------------------------------------------------------
void KConnectorMatrixOut::render ()
{
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  1.0, -1.0,  1.0, -0.5);
    RECTANGLE_ZX(-0.5,  0.5, -0.5,  0.5, 0.0);
    RECTANGLE_XY(-0.5,  0.5,  -0.5,  0.0,  0.5);
    RECTANGLE_YX(-0.5,  0.5,  -0.5,  0.0, -0.5);
    RECTANGLE_YZ(-0.5,  0.0, -0.5,  0.5,  0.5);
    RECTANGLE_ZY(-0.5,  0.0, -0.5,  0.5, -0.5);
    glEnd();
}

