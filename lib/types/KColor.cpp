/*
 *  KColor.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KColor.h"

KDL_CLASS_INTROSPECTION (KColor)

// --------------------------------------------------------------------------------------------------------
KColor::KColor ()
{
    values[R] = 1.0;
    values[G] = 1.0;
    values[B] = 1.0;
    values[A] = 1.0;
}

// --------------------------------------------------------------------------------------------------------
KColor::KColor ( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
    values[R] = r;
    values[G] = g;
    values[B] = b;
    values[A] = a;
}

// --------------------------------------------------------------------------------------------------------
KColor::KColor ( const KColor & object )
{
    values[R] = object.values[R];
    values[G] = object.values[G];
    values[B] = object.values[B];
    values[A] = object.values[A];
}

// --------------------------------------------------------------------------------------------------------
void KColor::setValues ( const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a )
{
    values[R] = r; values[G] = g; values[B] = b; values[A] = a;
}

// --------------------------------------------------------------------------------------------------------
void KColor::setValues4fv ( const GLfloat * v )
{
    values[R] = v[R]; values[G] = v[G]; values[B] = v[B]; values[A] = v[A];
}

// --------------------------------------------------------------------------------------------------------
void KColor::operator= ( const KColor & c )
{
    values[R] = c.values[R]; values[G] = c.values[G]; values[B] = c.values[B]; values[A] = c.values[A];
}