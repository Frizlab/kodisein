/*
 *  KDisk.cpp
 *  kodisein
 */

#include "KDisk.h"
#include "KModuleColor.h"
#include "KConsole.h"
#include "KController.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KDisk, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KDisk::KDisk ( KMatrixModule * m ) : KMatrixHandle (m)
{
    slices       = 10;
    loops        = 10;
    inner_radius = 0.0;
    start_angle  = 0.0;
    sweep_angle  = 360.0;
    orientation  = GLU_OUTSIDE;
    normals	 = GLU_SMOOTH;
}

// --------------------------------------------------------------------------------------------------------
void KDisk::setSweepAngle ( float f )
{
    sweep_angle = kMin(360.0, kMax(-360.0, f));
}

// --------------------------------------------------------------------------------------------------------
void KDisk::setInnerRadius ( float f )
{
    inner_radius = kMin(1.0, kMax(0.0, f));
}

// --------------------------------------------------------------------------------------------------------
void KDisk::setLoops ( float f )
{
    loops = kMax(1, (int)f);
}

// --------------------------------------------------------------------------------------------------------
void KDisk::setSlices ( float f )
{
    slices = kMax(1, (int)f);
}

// --------------------------------------------------------------------------------------------------------
void KDisk::display ( int mode )
{
    GLUquadric * quad = gluNewQuadric();

    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        KMatrixHandle::display(mode);
        unloadId();
        glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        gluQuadricOrientation(quad, orientation);
        gluQuadricNormals(quad, normals);
        gluPartialDisk(quad, inner_radius, 1.0, slices, loops, start_angle, sweep_angle);
        glPopAttrib();
    }
    else if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        glMultMatrixf(matrix);
        GLboolean texture;
        glGetBooleanv(GL_TEXTURE_2D, &texture);
        gluQuadricTexture(quad, texture);
        gluQuadricOrientation(quad, orientation);
        gluQuadricNormals(quad, normals);
        gluPartialDisk(quad, inner_radius, 1.0, slices, loops, start_angle, sweep_angle);
    }

    gluDeleteQuadric(quad);
}

