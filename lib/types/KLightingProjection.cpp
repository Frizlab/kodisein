/*
 *  KLightingProjection.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KLightingProjection.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 (KLightingProjection, KPerspectiveProjection)

// -------------------------------------------------------------------------------------------------------- 
// -------------------------------------------------------------------------------------------------------- 
KLightingProjection::KLightingProjection (GLfloat f, GLfloat zn, GLfloat zf) : KPerspectiveProjection ()
{
}

// -------------------------------------------------------------------------------------------------------- 
KLightingProjection::KLightingProjection ( const KProjection & p ) : KPerspectiveProjection (p)
{
}

// --------------------------------------------------------------------------------------------------------
KProjection * KLightingProjection::copy() const
{
    return new KLightingProjection(*this);
}
 
// --------------------------------------------------------------------------------------------------------
void KLightingProjection::apply ()
{
    KPerspectiveProjection::apply();

    KVector pos = getPosition();
    KVector dir = -getZVector();
    pos = KVector(pos[X], pos[Y], pos[Z], 1.0);

    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir.getValues());
    glLightfv(GL_LIGHT0, GL_POSITION,       pos.getValues());
}

