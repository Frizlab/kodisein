/*
 *  KTwoDirectionHandle.cpp
 *  kodisein
 */

#include "KTwoDirectionHandle.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 (KTwoDirectionHandle, KHandle)

// --------------------------------------------------------------------------------------------------------
void KTwoDirectionHandle::display ( int mode )
{
    preDisplay(mode);
    glMultMatrix();
    glutSolidCube(0.25);
    postDisplay(mode);
}

