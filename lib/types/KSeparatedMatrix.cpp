/*
 *  KSeparatedMatrix.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KSeparatedMatrix.h"

KDL_CLASS_INTROSPECTION_1 (KSeparatedMatrix, KMatrix)

// --------------------------------------------------------------------------------------------------------
KSeparatedMatrix::KSeparatedMatrix () : KMatrix ()
{
    scl[X] = 1.0; scl[Y] = 1.0; scl[Z] = 1.0;
    rot[X] = 0.0; rot[Y] = 0.0; rot[Z] = 0.0;
}

// --------------------------------------------------------------------------------------------------------
KSeparatedMatrix::KSeparatedMatrix ( const KSeparatedMatrix & m ) : KMatrix (m)
{
    scl[X] = m.scl[X]; scl[Y] = m.scl[Y]; scl[Z] = m.scl[Z];
    rot[X] = m.rot[X]; rot[Y] = m.rot[Y]; rot[Z] = m.rot[Z];
}

// --------------------------------------------------------------------------------------------------------
void  KSeparatedMatrix::operator= ( const KSeparatedMatrix & m )
{
    KMatrix::operator=(m);
    scl[X] = m.scl[X]; scl[Y] = m.scl[Y]; scl[Z] = m.scl[Z];
    rot[X] = m.rot[X]; rot[Y] = m.rot[Y]; rot[Z] = m.rot[Z];
}

// --------------------------------------------------------------------------------------------------------
void  KSeparatedMatrix::operator= ( const KMatrix & m )
{
    KMatrix::operator=(m);
    scl[X] = 1.0; scl[Y] = 1.0; scl[Z] = 1.0;
    rot[X] = 0.0; rot[Y] = 0.0; rot[Z] = 0.0;
}

// --------------------------------------------------------------------------------------------------------
void KSeparatedMatrix::reset()
{
    KMatrix::reset();
    scl[X] = 1.0; scl[Y] = 1.0; scl[Z] = 1.0;
    rot[X] = 0.0; rot[Y] = 0.0; rot[Z] = 0.0;
}

// --------------------------------------------------------------------------------------------------------
void KSeparatedMatrix::rotate ( const GLfloat x, const GLfloat y, const GLfloat z )		
{
    KMatrix::rotate(x, y, z);
    rot[X] += x;
    rot[Y] += y;
    rot[Z] += z;    
}

// --------------------------------------------------------------------------------------------------------
void KSeparatedMatrix::scale ( const GLfloat x, const GLfloat y, const GLfloat z )		
{
    KMatrix::scale(x, y, z);    
    scl[X] *= x;
    scl[Y] *= y;
    scl[Z] *= z;
}

// --------------------------------------------------------------------------------------------------------
void KSeparatedMatrix::setSX ( const GLfloat x )
{
    GLfloat tx = getTX(), ty = getTY(), tz = getTZ();
    GLfloat sy = scl[Y], sz = scl[Z];
    GLfloat rx = rot[X], ry = rot[Y], rz = rot[Z];
    reset();
    translate(tx, ty, tz);
    rotate(rx, ry, rz);
    scale(x, sy, sz);
}

// --------------------------------------------------------------------------------------------------------
void KSeparatedMatrix::setSY ( const GLfloat y )
{
    GLfloat tx = getTX(), ty = getTY(), tz = getTZ();
    GLfloat sx = scl[X], sz = scl[Z];
    GLfloat rx = rot[X], ry = rot[Y], rz = rot[Z];
    reset();
    translate(tx, ty, tz);
    rotate(rx, ry, rz);
    scale(sx, y, sz);
}

// --------------------------------------------------------------------------------------------------------
void KSeparatedMatrix::setSZ ( const GLfloat z )
{
    GLfloat tx = getTX(), ty = getTY(), tz = getTZ();
    GLfloat sx = scl[X], sy = scl[Y];
    GLfloat rx = rot[X], ry = rot[Y], rz = rot[Z];
    reset();
    translate(tx, ty, tz);
    rotate(rx, ry, rz);
    scale(sx, sy, z);
}

// --------------------------------------------------------------------------------------------------------
void KSeparatedMatrix::setRX ( const GLfloat x )
{
    GLfloat tx = getTX(), ty = getTY(), tz = getTZ();
    GLfloat sx = scl[X], sy = scl[Y], sz = scl[Z];
    GLfloat ry = rot[Y], rz = rot[Z];
    reset();
    translate(tx, ty, tz);
    rotate(x, ry, rz);
    scale(sx, sy, sz);
}

// --------------------------------------------------------------------------------------------------------
void KSeparatedMatrix::setRY ( const GLfloat y )
{
    GLfloat tx = getTX(), ty = getTY(), tz = getTZ();
    GLfloat sx = scl[X], sy = scl[Y], sz = scl[Z];
    GLfloat rx = rot[X], rz = rot[Z];
    reset();
    translate(tx, ty, tz);
    rotate(rx, y, rz);
    scale(sx, sy, sz);
}

// --------------------------------------------------------------------------------------------------------
void KSeparatedMatrix::setRZ ( const GLfloat z )
{
    GLfloat tx = getTX(), ty = getTY(), tz = getTZ();
    GLfloat sx = scl[X], sy = scl[Y], sz = scl[Z];
    GLfloat rx = rot[X], ry = rot[Y];
    reset();
    translate(tx, ty, tz);
    rotate(rx, ry, z);
    scale(sx, sy, sz);
}

