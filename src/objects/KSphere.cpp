/*
 *  KSphere.cpp
 *  kodisein
 */

#include "KSphere.h"
#include "KModuleColor.h"
#include "KConsole.h"
#include "KController.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KSphere, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KSphere::KSphere ( KMatrixModule * m ) : KMatrixHandle (m)
{
    slices      = 10;
    stacks      = 10;
    orientation = GLU_OUTSIDE;
    normals	= GLU_SMOOTH;
}

// --------------------------------------------------------------------------------------------------------
void KSphere::setStacks ( float f )
{
    stacks = kMax(1, (int)f);
}

// --------------------------------------------------------------------------------------------------------
void KSphere::setSlices ( float f )
{
    slices = kMax(1, (int)f);
}

// --------------------------------------------------------------------------------------------------------
void KSphere::display ( int mode )
{
    GLUquadric * quad = gluNewQuadric();

    glPushAttrib(GL_ENABLE_BIT);
    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        KMatrixHandle::display(mode);
        unloadId();
        glDisable(GL_LIGHTING);
        glEnable(GL_CULL_FACE);
        gluQuadricDrawStyle(quad, GLU_LINE);
        gluQuadricOrientation(quad, orientation);
        gluSphere(quad, 1.0, slices, stacks);
    }
    else if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        glMultMatrixf(matrix);
        GLboolean texture;
        glGetBooleanv(GL_TEXTURE_2D, &texture);
        gluQuadricTexture(quad, texture);
        gluQuadricOrientation(quad, orientation);
        gluQuadricNormals(quad, normals);
        gluSphere(quad, 1.0, slices, stacks);
    }
    glPopAttrib();

    gluDeleteQuadric(quad);
}

