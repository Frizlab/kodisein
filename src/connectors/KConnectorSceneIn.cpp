/*
 *  KConnectorSceneIn.cpp
 *  kodisein
 */

#include "KConnectorSceneIn.h"


KDS_CONNECTION_VALUES (KConnectorSceneIn, KDS_CONNECTOR_SCENE_IN, KDS_CONNECTOR_SCENE_OUT)

// --------------------------------------------------------------------------------------------------------
void KConnectorSceneIn::render ()
{
    float h = 0.5;
    float c = 1/sqrt(1.25);
    float s = 0.5*c;

    glPushMatrix();
    glTranslatef(0.0, -0.25, 0.0);

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(-s, c, 0.0);
    glVertex3f(0.0, -h, 0.0);
    glVertex3f( 1.0, 0.0,  1.0);
    glVertex3f( 1.0, 0.0, -1.0);
    glNormal3f(0.0, c, s);
    glVertex3f( 1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glNormal3f(s, c, 0.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0,  1.0);
    glNormal3f(0.0, c, -s);
    glVertex3f(-1.0, 0.0,  1.0);
    glVertex3f( 1.0, 0.0,  1.0);
    glEnd();

    glPopMatrix();
}
