/*
 *  KOneDirectionHandle.cpp
 *  kodisein
 */

#include "KOneDirectionHandle.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KOneDirectionHandle, KHandle)

// --------------------------------------------------------------------------------------------------------
void KOneDirectionHandle::display ( int mode )
{
    preDisplay(mode);
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_CULL_FACE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMultMatrix();
    glRotated(90.0, 0.0, 1.0, 0.0);
    
    GLUquadric * quad = gluNewQuadric();
    gluCylinder(quad, 0.25, 0.0, 0.5, 15, 1);
    gluDeleteQuadric(quad);
    
    glPopAttrib();
    postDisplay(mode);
}


