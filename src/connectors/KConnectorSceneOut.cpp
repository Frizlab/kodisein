/*
 *  KConnectorSceneOut.cpp
 *  kodisein
 */

#include "KConnectorSceneOut.h"


KDS_CONNECTION_VALUES (KConnectorSceneOut, KDS_CONNECTOR_SCENE_OUT, KDS_CONNECTOR_SCENE_IN)

// --------------------------------------------------------------------------------------------------------
void KConnectorSceneOut::render ()
{
    float h = 0.5;
    float c = 1/sqrt(1.25);
    float s = 0.5*c;

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(s, c, 0.0);
    glVertex3f(0.0, h, 0.0);
    glVertex3f( 1.0, 0.0,  1.0);
    glVertex3f( 1.0, 0.0, -1.0);
    glNormal3f(0.0, c, -s);
    glVertex3f( 1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glNormal3f(-s, c, 0.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0,  1.0);
    glNormal3f(0.0, c, s);
    glVertex3f(-1.0, 0.0,  1.0);
    glVertex3f( 1.0, 0.0,  1.0);
    glEnd();
}
