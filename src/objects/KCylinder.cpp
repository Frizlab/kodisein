/*
 *  KCylinder.cpp
 *  kodisein
 */

#include "KCylinder.h"
#include "KModuleColor.h"
#include "KConsole.h"
#include "KController.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KCylinder, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KCylinder::KCylinder ( KMatrixModule * m ) : KMatrixHandle (m)
{
    slices      = 10;
    stacks      = 10;
    top_radius  = 1.0;
    orientation = GLU_OUTSIDE;
    normals	= GLU_SMOOTH;
}

// --------------------------------------------------------------------------------------------------------
void KCylinder::display ( int mode )
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
        gluCylinder(quad, 1.0, top_radius, 1.0, slices, stacks);
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
        gluCylinder(quad, 1.0, top_radius, 1.0, slices, stacks);
    }

    gluDeleteQuadric(quad);
}

