/*
 *  KMatrix.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KMatrix.h"
#include "KConsole.h"

#include <GLUT/vvector.h> // INVERT_4X4

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KMatrix, KObject)

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix () : KObject ()
{
    reset();
}

// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix ( const KMatrix & m ) : KObject ()
{
    matrix[0]=m.matrix[0];matrix[1]=m.matrix[1];matrix[2]=m.matrix[2];matrix[3]=m.matrix[3];
    matrix[4]=m.matrix[4];matrix[5]=m.matrix[5];matrix[6]=m.matrix[6];matrix[7]=m.matrix[7];
    matrix[8]=m.matrix[8];matrix[9]=m.matrix[9];matrix[10]=m.matrix[10];matrix[11]=m.matrix[11];
    matrix[12]=m.matrix[12];matrix[13]=m.matrix[13];matrix[14]=m.matrix[14];matrix[15]=m.matrix[15];
}

// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix ( const GLfloat * m ) : KObject ()
{
    matrix[0]=m[0];matrix[1]=m[1];matrix[2]=m[2];matrix[3]=m[3];
    matrix[4]=m[4];matrix[5]=m[5];matrix[6]=m[6];matrix[7]=m[7];
    matrix[8]=m[8];matrix[9]=m[9];matrix[10]=m[10];matrix[11]=m[11];
    matrix[12]=m[12];matrix[13]=m[13];matrix[14]=m[14];matrix[15]=m[15];
}

// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix ( const KVector & x, const KVector & y, const KVector & z ) : KObject ()
{
    matrix[0] = x.vector[X]; matrix[4] = y.vector[X]; matrix[8]  = z.vector[X]; matrix[12] = 0.0;
    matrix[1] = x.vector[Y]; matrix[5] = y.vector[Y]; matrix[9]  = z.vector[Y]; matrix[13] = 0.0; 
    matrix[2] = x.vector[Z]; matrix[6] = y.vector[Z]; matrix[10] = z.vector[Z]; matrix[14] = 0.0;
    matrix[3] = x.vector[W]; matrix[7] = y.vector[W]; matrix[11] = z.vector[W]; matrix[15] = 1.0;
}

// --------------------------------------------------------------------------------------------------------
void  KMatrix::operator= ( const KMatrix & m )
{
    matrix[0]=m.matrix[0];matrix[1]=m.matrix[1];matrix[2]=m.matrix[2];matrix[3]=m.matrix[3];
    matrix[4]=m.matrix[4];matrix[5]=m.matrix[5];matrix[6]=m.matrix[6];matrix[7]=m.matrix[7];
    matrix[8]=m.matrix[8];matrix[9]=m.matrix[9];matrix[10]=m.matrix[10];matrix[11]=m.matrix[11];
    matrix[12]=m.matrix[12];matrix[13]=m.matrix[13];matrix[14]=m.matrix[14];matrix[15]=m.matrix[15];
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::operator*= ( const KMatrix & m )
{
    *this = (*this * m);
}

// --------------------------------------------------------------------------------------------------------
KMatrix KMatrix::operator* ( const KMatrix & m ) const
{
    KMatrix mm;
    mm.matrix[0]=matrix[0]*m.matrix[0]+matrix[4]*m.matrix[1]+matrix[8]*m.matrix[2]+matrix[12]*m.matrix[3];
    mm.matrix[1]=matrix[1]*m.matrix[0]+matrix[5]*m.matrix[1]+matrix[9]*m.matrix[2]+matrix[13]*m.matrix[3];
    mm.matrix[2]=matrix[2]*m.matrix[0]+matrix[6]*m.matrix[1]+matrix[10]*m.matrix[2]+matrix[14]*m.matrix[3];
    mm.matrix[3]=matrix[3]*m.matrix[0]+matrix[7]*m.matrix[1]+matrix[11]*m.matrix[2]+matrix[15]*m.matrix[3];
    mm.matrix[4]=matrix[0]*m.matrix[4]+matrix[4]*m.matrix[5]+matrix[8]*m.matrix[6]+matrix[12]*m.matrix[7];
    mm.matrix[5]=matrix[1]*m.matrix[4]+matrix[5]*m.matrix[5]+matrix[9]*m.matrix[6]+matrix[13]*m.matrix[7];
    mm.matrix[6]=matrix[2]*m.matrix[4]+matrix[6]*m.matrix[5]+matrix[10]*m.matrix[6]+matrix[14]*m.matrix[7];
    mm.matrix[7]=matrix[3]*m.matrix[4]+matrix[7]*m.matrix[5]+matrix[11]*m.matrix[6]+matrix[15]*m.matrix[7];
    mm.matrix[8]=matrix[0]*m.matrix[8]+matrix[4]*m.matrix[9]+matrix[8]*m.matrix[10]+matrix[12]*m.matrix[11];
    mm.matrix[9]=matrix[1]*m.matrix[8]+matrix[5]*m.matrix[9]+matrix[9]*m.matrix[10]+matrix[13]*m.matrix[11];
    mm.matrix[10]=matrix[2]*m.matrix[8]+matrix[6]*m.matrix[9]+matrix[10]*m.matrix[10]+matrix[14]*m.matrix[11]; 
    mm.matrix[11]=matrix[3]*m.matrix[8]+matrix[7]*m.matrix[9]+matrix[11]*m.matrix[10]+matrix[15]*m.matrix[11]; 
    mm.matrix[12]=matrix[0]*m.matrix[12]+matrix[4]*m.matrix[13]+matrix[8]*m.matrix[14]+matrix[12]*m.matrix[15]; 
    mm.matrix[13]=matrix[1]*m.matrix[12]+matrix[5]*m.matrix[13]+matrix[9]*m.matrix[14]+matrix[13]*m.matrix[15]; 
    mm.matrix[14]=matrix[2]*m.matrix[12]+matrix[6]*m.matrix[13]+matrix[10]*m.matrix[14]+matrix[14]*m.matrix[15]; 
    mm.matrix[15]=matrix[3]*m.matrix[12]+matrix[7]*m.matrix[13]+matrix[11]*m.matrix[14]+matrix[15]*m.matrix[15]; 
    return mm;
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::operator* ( const KVector & v ) const
{
    return KVector( 
        matrix[0]*v.vector[0] + matrix[4]*v.vector[1] + matrix[8] *v.vector[2] + matrix[12]*v.vector[3],
        matrix[1]*v.vector[0] + matrix[5]*v.vector[1] + matrix[9] *v.vector[2] + matrix[13]*v.vector[3],
	matrix[2]*v.vector[0] + matrix[6]*v.vector[1] + matrix[10]*v.vector[2] + matrix[14]*v.vector[3],
	matrix[3]*v.vector[0] + matrix[7]*v.vector[1] + matrix[11]*v.vector[2] + matrix[15]*v.vector[3] );
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::reset()
{
    matrix[0]=matrix[5]=matrix[10]=matrix[15]=1.0; 
    matrix[1]=matrix[4]=matrix[8] =matrix[12]=0.0;
    matrix[2]=matrix[6]=matrix[9] =matrix[13]=0.0; 
    matrix[3]=matrix[7]=matrix[11]=matrix[14]=0.0;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::transform ( const KMatrix & m ) 
{
    *this *= m;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::rotate ( const GLfloat x, const GLfloat y, const GLfloat z )		
{
    GLfloat rx = DEG2RAD(x), ry = DEG2RAD(y), rz = DEG2RAD(z);
    GLfloat cx=cos(rx), sx=sin(rx), cy=cos(ry), sy=sin(ry), cz = cos(rz), sz = sin(rz);

    GLfloat b0 = cy*cz, b1 = sx*sy*cz+cx*sz, b2 = -cx*sy*cz+sx*sz, b4 = -cy*sz; 
    GLfloat b5 = -sx*sy*sz+cx*cz, b6 = cx*sy*sz+sx*cz, b8 = sy, b9 = -sx*cy, b10 = cx*cy; 
    GLfloat a0 = matrix[0], a1 = matrix[1], a2  = matrix[2],   a3 = matrix[3]; 
    GLfloat a4 = matrix[4], a5 = matrix[5], a6  = matrix[6],   a7 = matrix[7];
    GLfloat a8 = matrix[8], a9 = matrix[9], a10 = matrix[10], a11 = matrix[11];
    
    matrix[0]=a0*b0+a4*b1+a8*b2;
    matrix[1]=a1*b0+a5*b1+a9*b2;
    matrix[2]=a2*b0+a6*b1+a10*b2;
    matrix[3]=a3*b0+a7*b1+a11*b2;
    matrix[4]=a0*b4+a4*b5+a8*b6;
    matrix[5]=a1*b4+a5*b5+a9*b6;
    matrix[6]=a2*b4+a6*b5+a10*b6;
    matrix[7]=a3*b4+a7*b5+a11*b6;
    matrix[8]=a0*b8+a4*b9+a8*b10;
    matrix[9]=a1*b8+a5*b9+a9*b10;
    matrix[10]=a2*b8+a6*b9+a10*b10;
    matrix[11]=a3*b8+a7*b9+a11*b10;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::scale ( const GLfloat x, const GLfloat y, const GLfloat z )		
{
    matrix[0] *= x; matrix[1] *= x; matrix[2]  *= x; matrix[3]  *= x;
    matrix[4] *= y; matrix[5] *= y; matrix[6]  *= y; matrix[7]  *= y;
    matrix[8] *= z; matrix[9] *= z; matrix[10] *= z; matrix[11] *= z;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::invert ()
{
    GLfloat t[4][4], inv[4][4], det;
    t[0][0] = matrix[0];  t[0][1] = matrix[1];  t[0][2] = matrix[2];  t[0][3] = matrix[3];
    t[1][0] = matrix[4];  t[1][1] = matrix[5];  t[1][2] = matrix[6];  t[1][3] = matrix[7]; 
    t[2][0] = matrix[8];  t[2][1] = matrix[9];  t[2][2] = matrix[10]; t[2][3] = matrix[11]; 
    t[3][0] = matrix[12]; t[3][1] = matrix[13]; t[3][2] = matrix[14]; t[3][3] = matrix[15]; 
    INVERT_4X4(inv,det,t);
    matrix[0]  = inv[0][0]; matrix[1]  = inv[0][1]; matrix[2]  = inv[0][2]; matrix[3]  = inv[0][3];
    matrix[4]  = inv[1][0]; matrix[5]  = inv[1][1]; matrix[6]  = inv[1][2]; matrix[7]  = inv[1][3];
    matrix[8]  = inv[2][0]; matrix[9]  = inv[2][1]; matrix[10] = inv[2][2]; matrix[11] = inv[2][3];
    matrix[12] = inv[3][0]; matrix[13] = inv[3][1]; matrix[14] = inv[3][2]; matrix[15] = inv[3][3];
}

// --------------------------------------------------------------------------------------------------------
GLfloat KMatrix::getDepthValue () const
{
    GLdouble	model[16], proj[16], wx, wy, wz;
    GLint	view[4];
    
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, view);
    
    if (gluProject(matrix[TX], matrix[TY], matrix[TZ], model, proj, view, &wx, &wy, &wz) == false)
    {
        KConsole::printError("unable to calculate depth value"); return 0.0;
    }
    
    return wz;
}

