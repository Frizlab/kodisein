/*
 *  KVertexHandle.cpp
 *  kodisein
 */

#include "KVertexHandle.h"
#include "KController.h"
#include "KModules.h"
#include "KObjects.h"
#include "KProjection.h"
#include "KConsole.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 (KVertexHandle, KHandle)

// --------------------------------------------------------------------------------------------------------
KVertexHandle::KVertexHandle ( KHandle * p, GLfloat x, GLfloat y, GLfloat z ) : KHandle (p)
{
    setPosition (KVector(x, y, z));
}

// --------------------------------------------------------------------------------------------------------
KVertexHandle::KVertexHandle ( KHandle * p, const KVector & v ) : KHandle (p)
{
    setPosition (v);
}

// --------------------------------------------------------------------------------------------------------
void KVertexHandle::moved ( const KMouseEvent & mouseEvent )
{
    KVector pos = getWorldMatrix().getPosition();
            
    if (Controller.modules->objects->getProjection()->moveObjectRelativeToWindow (mouseEvent.delta, pos))
    {
        KVector direction = pos - parent->getWorldMatrix().getPosition();
    
        setPosition(parent->getWorldMatrix().getInverse() * direction);
    }
    else
    {
        KConsole::printError("moving handle failed!", false);
    }
}

// --------------------------------------------------------------------------------------------------------
void KVertexHandle::setPosition ( const KVector & pos, bool sendNotification ) 
{
    KSeparatedMatrix::setPosition(pos);
    if (sendNotification) notify();
}

// --------------------------------------------------------------------------------------------------------
void KVertexHandle::notify () const
{
    notifyReceivers((void*)this, KDL_NOTIFICATION_TYPE_VERTEX_MOVED);
    KHandle::notify();
}

// --------------------------------------------------------------------------------------------------------
void KVertexHandle::display ( int mode )
{
    preDisplay(mode);
    glMultMatrix();
    glutSolidCube(0.25);
    postDisplay(mode);
}