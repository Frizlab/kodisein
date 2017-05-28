/*
 *  KRotationHandle.cpp
 *  kodisein
 */

#include "KRotationHandle.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 (KRotationHandle, KHandle)

// --------------------------------------------------------------------------------------------------------
void KRotationHandle::display ( int mode )
{
    preDisplay(mode);        
    glMultMatrix();
    glutSolidTorus(0.075, 0.25, 5, 15);
    postDisplay(mode);
}
