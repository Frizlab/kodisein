/*
 *  KVector.cpp
 *  kodisein
 */

#include "KVector.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION (KVector)

// --------------------------------------------------------------------------------------------------------
KVector::KVector ()
{
    reset();
}

// --------------------------------------------------------------------------------------------------------
KVector::KVector ( const KVector & v )
{
    vector[X] = v.vector[X]; vector[Y] = v.vector[Y]; vector[Z] = v.vector[Z]; vector[W] = v.vector[W]; 
}

// --------------------------------------------------------------------------------------------------------
KVector::KVector ( const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w )
{
    vector[X] = x; vector[Y] = y; vector[Z] = z; vector[W] = w;
}
