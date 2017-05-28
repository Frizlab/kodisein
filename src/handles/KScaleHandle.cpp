/*
 *  KScaleHandle.cpp
 *  kodisein
*/

#include "KScaleHandle.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 (KScaleHandle, KHandle)

// --------------------------------------------------------------------------------------------------------
void KScaleHandle::display ( int mode )
{
    preDisplay(mode);
    glMultMatrix();
    glutSolidCube(0.2);
    postDisplay(mode);
}
