/*
 *  KMoveHandle.cpp
 *  kodisein
 */

#include "KMoveHandle.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_1 (KMoveHandle, KHandle)

// --------------------------------------------------------------------------------------------------------
void KMoveHandle::display ( int mode )
{
    preDisplay(mode);
    glMultMatrix();
    kDisplaySolidSphere(0.25, 5);
    postDisplay(mode);
}

