/*
 *  KConnectorMatrixIn.cpp
 *  kodisein
 */

#include "KConnectorMatrixIn.h"
#include "KObjectModule.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorMatrixIn, KDS_CONNECTOR_MATRIX_IN, KDS_CONNECTOR_MATRIX_OUT)

// --------------------------------------------------------------------------------------------------------
void KConnectorMatrixIn::render ()
{
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);

    glVertex3f(-1.0, 0.0, -1.0); glEdgeFlag(false);
    glVertex3f(-1.0, 0.0,  1.0); glEdgeFlag(true);
    glVertex3f(-0.5, 0.0,  0.5); glEdgeFlag(false);
    glVertex3f(-0.5, 0.0, -0.5); glEdgeFlag(true);
            
    glVertex3f( 0.5, 0.0, -0.5); glEdgeFlag(false);
    glVertex3f( 0.5, 0.0,  0.5); glEdgeFlag(true);
    glVertex3f( 1.0, 0.0,  1.0); glEdgeFlag(false);
    glVertex3f( 1.0, 0.0, -1.0); glEdgeFlag(true);

    glVertex3f( 1.0, 0.0, -1.0); glEdgeFlag(false);
    glVertex3f(-1.0, 0.0, -1.0); glEdgeFlag(true);
    glVertex3f(-0.5, 0.0, -0.5); glEdgeFlag(false);
    glVertex3f( 0.5, 0.0, -0.5); glEdgeFlag(true);
 
    glVertex3f( 0.5, 0.0,  0.5); glEdgeFlag(false);     
    glVertex3f(-0.5, 0.0,  0.5); glEdgeFlag(true);
    glVertex3f(-1.0, 0.0,  1.0); glEdgeFlag(false);
    glVertex3f( 1.0, 0.0,  1.0); glEdgeFlag(true);

    GLfloat h = 0.38f;
    
    glEdgeFlag(false);
    RECTANGLE_ZX(-0.5,  0.5, -0.5,  0.5, -h);    
    glEdgeFlag(true);
    RECTANGLE_XY(-0.5,  0.5,  -h,  0.0, -0.5);
    RECTANGLE_YX(-0.5,  0.5,  -h,  0.0,  0.5);
    RECTANGLE_YZ( -h,  0.0, -0.5,  0.5, -0.5);
    RECTANGLE_ZY( -h,  0.0, -0.5,  0.5,  0.5);
    glEnd();
}
