/*
 *  KBox.cpp
 *  kodisein
 */

#include "KBox.h"
#include "KFace.h"
#include "KController.h"
#include "KConsole.h"

#include <glut.h>

KDL_CLASS_INTROSPECTION_1 (KBox, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KBox::KBox ( KMatrixModule * m ) : KMatrixHandle ( m )
{
    orientation = GLU_OUTSIDE;
}

// --------------------------------------------------------------------------------------------------------
void KBox::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        KMatrixHandle::display(mode);
        unloadId();
        glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glutWireCube(2.0);
        glPopAttrib();
    }
    else if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        glMultMatrixf(matrix);
        if (orientation == GLU_OUTSIDE)
        {
            glBegin(GL_QUADS);
            glNormal3f(0.0, -1.0, 0.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, -1.0, -1.0); // bottom
            glTexCoord2f(  1.0,   0.0); glVertex3f( 1.0, -1.0, -1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0, -1.0,  1.0);
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0, -1.0,  1.0);
    
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0, 1.0,  1.0); // top
            glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0, 1.0,  1.0);
            glTexCoord2f(  1.0,   0.0); glVertex3f( 1.0, 1.0, -1.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, 1.0, -1.0);
                
            glNormal3f(0.0, 0.0, -1.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, -1.0, -1.0); // back
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0,  1.0, -1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0,  1.0, -1.0);
            glTexCoord2f(  1.0,   0.0); glVertex3f( 1.0, -1.0, -1.0);
    
            glNormal3f(0.0, 0.0, 1.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, -1.0, 1.0); // front
            glTexCoord2f(  1.0,   0.0); glVertex3f( 1.0, -1.0, 1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0,  1.0, 1.0);
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0,  1.0, 1.0);
            
            glNormal3f(-1.0, 0.0, 0.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, -1.0, -1.0); // left
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0, -1.0,  1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f(-1.0,  1.0,  1.0);
            glTexCoord2f(  1.0,   0.0); glVertex3f(-1.0,  1.0, -1.0);
    
            glNormal3f(1.0, 0.0, 0.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(1.0, -1.0, -1.0); // right
            glTexCoord2f(  1.0,   0.0); glVertex3f(1.0,  1.0, -1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f(1.0,  1.0,  1.0);
            glTexCoord2f(  0.0,   1.0); glVertex3f(1.0, -1.0,  1.0);
            glEnd();
        }
        else
        {
            glBegin(GL_QUADS);
            glNormal3f(0.0, -1.0, 0.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0,  1.0, -1.0); // top
            glTexCoord2f(  1.0,   0.0); glVertex3f( 1.0,  1.0, -1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0,  1.0,  1.0);
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0,  1.0,  1.0);
    
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0, -1.0,  1.0); // bottom
            glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0, -1.0,  1.0);
            glTexCoord2f(  1.0,   0.0); glVertex3f( 1.0, -1.0, -1.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, -1.0, -1.0);
                
            glNormal3f(0.0, 0.0, -1.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, -1.0, 1.0); // front
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0,  1.0, 1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0,  1.0, 1.0);
            glTexCoord2f(  1.0,   0.0); glVertex3f( 1.0, -1.0, 1.0);
    
            glNormal3f(0.0, 0.0, 1.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, -1.0, -1.0); // back
            glTexCoord2f(  1.0,   0.0); glVertex3f( 1.0, -1.0, -1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0,  1.0, -1.0);
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0,  1.0, -1.0);
            
            glNormal3f(-1.0, 0.0, 0.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(1.0, -1.0, -1.0); // right
            glTexCoord2f(  0.0,   1.0); glVertex3f(1.0, -1.0,  1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f(1.0,  1.0,  1.0);
            glTexCoord2f(  1.0,   0.0); glVertex3f(1.0,  1.0, -1.0);
    
            glNormal3f(1.0, 0.0, 0.0);
            glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, -1.0, -1.0); // left
            glTexCoord2f(  1.0,   0.0); glVertex3f(-1.0,  1.0, -1.0);
            glTexCoord2f(  1.0,   1.0); glVertex3f(-1.0,  1.0,  1.0);
            glTexCoord2f(  0.0,   1.0); glVertex3f(-1.0, -1.0,  1.0);
            glEnd();
        }
    }
}

