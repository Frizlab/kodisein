/*
 *  KMatrixHandle.cpp
 *  kodisein
 */

#include "KMatrixHandle.h"
#include "KController.h"
#include "KModules.h"
#include "KObjects.h"
#include "KProjection.h"
#include "KMoveHandle.h"
#include "KScaleHandle.h"
#include "KRotationHandle.h"
#include "KOneDirectionHandle.h"
#include "KTwoDirectionHandle.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 (KMatrixHandle, KHandlesObject)

#define ANGLE(x,y) 			(((x)==0 && (y)==0) ? 0.0 : (((y)>=0) ? (((x)>=0) ? \
                                        (      RAD2DEG(acos((x)/hypot((x),(y))))) : \
                                        (180.0-RAD2DEG(acos(-(x)/hypot((x),(y)))))) : (((x)>=0) ? \
                                        (360.0-RAD2DEG(acos((x)/hypot((x),(y))))) : \
                                        (180.0+RAD2DEG(acos(-(x)/hypot((x),(y))))))))

// --------------------------------------------------------------------------------------------------------
KMatrixHandle::KMatrixHandle () : KHandlesObject ()
{
}

// --------------------------------------------------------------------------------------------------------
KMatrixHandle::KMatrixHandle ( KMatrixModule * m ) : KHandlesObject ()
{
    module = m;
    Controller.modules->objects->addPickable(this);
    initTranslateHandles();
    initRotateHandles();
    initScaleHandles();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::setPicked ( bool p )
{
    if (p != picked)
    {
        KHandlesObject::setPicked(p);
        handles[0]->setPicked(p);
    }
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::initTranslateHandles ()
{
    KHandle * handle = new KMoveHandle (this);
    handle->translate(0.0, 0.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KHandlesObject::setOrigin, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);
    
    handle = new KOneDirectionHandle (this);
    handle->translate(1.0, 0.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::xHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);

    handle = new KOneDirectionHandle (this);
    handle->translate(0.0, 1.0, 0.0);
    handle->rotate(0.0, 0.0, 90.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::yHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);
    
    handle = new KOneDirectionHandle (this);
    handle->translate(0.0, 0.0, 1.0);
    handle->rotate(0.0, -90.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::zHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);
    
    handle = new KTwoDirectionHandle (this);
    handle->translate(1.0, 1.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::xyHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);

    handle = new KTwoDirectionHandle (this);
    handle->translate(1.0, 0.0, 1.0);
    handle->rotate(90.0, 0.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::xzHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);
    
    handle = new KTwoDirectionHandle (this);
    handle->translate(0.0, 1.0, 1.0);
    handle->rotate(0.0, 90.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::yzHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::initScaleHandles ()
{
    KHandle * handle = new KScaleHandle (this);
    handle->translate(0.9f, 0.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::xsHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);

    handle = new KScaleHandle (this);
    handle->translate(0.0, 0.9f, 0.0);
    handle->rotate(0.0, 0.0, 90.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::ysHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);
    
    handle = new KScaleHandle (this);
    handle->translate(0.0, 0.0, 0.9f);
    handle->rotate(0.0, -90.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::zsHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::initRotateHandles ()
{
    KHandle * handle = new KRotationHandle (this);
    handle->translate(1.0, 1.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::zrHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);

    handle = new KRotationHandle (this);
    handle->translate(1.0, 0.0, 1.0);
    handle->rotate(90.0, 0.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::yrHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);
    
    handle = new KRotationHandle (this);
    handle->translate(0.0, 1.0, 1.0);
    handle->rotate(0.0, 90.0, 0.0);
    handle->addReceiverCallback(this, (KSetDataPtr)&KMatrixHandle::xrHandleMoved, 								KDL_NOTIFICATION_TYPE_HANDLE_MOVED );
    addHandle(handle);
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::xsHandleMoved ( void * handleData )
{
    KPosition delta = ((KHandleData*)handleData)->mouseEvent->delta;
    
    scale(1.0 + Controller.modules->objects->getProjection()->getXValueForScreenDeltasAndMatrix
                                                        (delta.x, delta.y, getWorldMatrix()), 1.0, 1.0);
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::ysHandleMoved ( void * handleData )
{
    KPosition delta = ((KHandleData*)handleData)->mouseEvent->delta;
    
    scale(1.0, 1.0 + Controller.modules->objects->getProjection()->getYValueForScreenDeltasAndMatrix
                                                            (delta.x, delta.y, getWorldMatrix()), 1.0);
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::zsHandleMoved ( void * handleData )
{
    KPosition delta = ((KHandleData*)handleData)->mouseEvent->delta;
    
    scale (1.0, 1.0, 1.0 + Controller.modules->objects->getProjection()->getZValueForScreenDeltasAndMatrix
                                                                (delta.x, delta.y, getWorldMatrix()));
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::xrHandleMoved ( void * handleData )
{
    KPosition newPos = ((KHandleData*)handleData)->mouseEvent->pos;
    KPosition oldPos = ((KHandleData*)handleData)->mouseEvent->pos - ((KHandleData*)handleData)->mouseEvent->delta;
    
    GLdouble ox, oy;
    KMatrix fm = getWorldMatrix();
    Controller.modules->objects->getProjection()->getScreenCoordinates (fm.getPosition(), &ox, &oy);
    
    KVector look 	 = *(KMatrix*)Controller.modules->objects->getProjection() * KVector(0.0, 0.0, 1.0, 0.0);
    KVector orientation  = fm * KVector(1.0, 0.0, 0.0, 0.0);
    GLfloat d 		 = look * orientation;
    
    if (d < 0)
    {
        rotate(-(ANGLE(newPos.x-ox,newPos.y-oy)-
                 ANGLE(oldPos.x-ox,oldPos.y-oy)), 0.0, 0.0);
    }
    else
    {
        rotate(ANGLE(newPos.x-ox,newPos.y-oy)-
                ANGLE(oldPos.x-ox,oldPos.y-oy), 0.0, 0.0);
    }
    
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::yrHandleMoved ( void * handleData )
{
    KPosition newPos = ((KHandleData*)handleData)->mouseEvent->pos;
    KPosition oldPos = ((KHandleData*)handleData)->mouseEvent->pos - ((KHandleData*)handleData)->mouseEvent->delta;
    
    GLdouble ox, oy; 
    KMatrix fm = getWorldMatrix();
    Controller.modules->objects->getProjection()->getScreenCoordinates (fm.getPosition(), &ox, &oy);
    
    KVector look 	 = *(KMatrix*)Controller.modules->objects->getProjection() * KVector(0.0, 0.0, 1.0, 0.0);
    KVector orientation  = fm * KVector(0.0, 1.0, 0.0, 0.0);
    GLfloat d 		 = look * orientation;
    
    if (d < 0)
    {
        rotate(0.0, -(ANGLE(newPos.x-ox,newPos.y-oy)-
                        ANGLE(oldPos.x-ox,oldPos.y-oy)), 0.0);
    }
    else
    {
        rotate(0.0, ANGLE(newPos.x-ox,newPos.y-oy)-
                        ANGLE(oldPos.x-ox,oldPos.y-oy), 0.0);
    }

    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::zrHandleMoved ( void * handleData )
{
    KPosition newPos = ((KHandleData*)handleData)->mouseEvent->pos;
    KPosition oldPos = ((KHandleData*)handleData)->mouseEvent->pos - ((KHandleData*)handleData)->mouseEvent->delta;

    GLdouble ox, oy;
    KMatrix fm = getWorldMatrix();
    Controller.modules->objects->getProjection()->getScreenCoordinates (fm.getPosition(), &ox, &oy);
    
    KVector look 	 = *(KMatrix*)Controller.modules->objects->getProjection() * KVector(0.0, 0.0, 1.0, 0.0);
    KVector orientation  = fm * KVector(0.0, 0.0, 1.0, 0.0);
    GLfloat d 		 = look * orientation;
    
    if (d < 0)
    {
        rotate(0.0, 0.0, -(ANGLE(newPos.x-ox,newPos.y-oy)-
                            ANGLE(oldPos.x-ox,oldPos.y-oy)));
    }
    else
    {
        rotate(0.0, 0.0, ANGLE(newPos.x-ox,newPos.y-oy)-
                            ANGLE(oldPos.x-ox,oldPos.y-oy));
    }

    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::xyHandleMoved ( void * handleData )
{
    KPosition delta = ((KHandleData*)handleData)->mouseEvent->delta;

    GLfloat x, y;
    Controller.modules->objects->getProjection()->getXYValuesForScreenDeltasAndMatrix 
                                                            (delta.x, delta.y, getWorldMatrix(), &x, &y);
    translate(x, y, 0.0);
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::xzHandleMoved ( void * handleData )
{
    KPosition delta = ((KHandleData*)handleData)->mouseEvent->delta;

    GLfloat x, z;
    Controller.modules->objects->getProjection()->getXZValuesForScreenDeltasAndMatrix 
                                                            (delta.x, delta.y, getWorldMatrix(), &x, &z);
    translate(x, 0.0, z);
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::yzHandleMoved ( void * handleData )
{
    KPosition delta = ((KHandleData*)handleData)->mouseEvent->delta;

    GLfloat y, z;
    Controller.modules->objects->getProjection()->getYZValuesForScreenDeltasAndMatrix 
                                                            (delta.x, delta.y, getWorldMatrix(), &y, &z);
    translate(0.0, y, z);
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::xHandleMoved ( void * handleData )
{
    KPosition delta = ((KHandleData*)handleData)->mouseEvent->delta;

    GLfloat x = Controller.modules->objects->getProjection()->getXValueForScreenDeltasAndMatrix
                                                                    (delta.x, delta.y, getWorldMatrix());
    translate(x, 0.0, 0.0);
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::yHandleMoved ( void * handleData )
{
    KPosition delta = ((KHandleData*)handleData)->mouseEvent->delta;

    GLfloat y = Controller.modules->objects->getProjection()->getYValueForScreenDeltasAndMatrix
                                                                    (delta.x, delta.y, getWorldMatrix());
    translate(0.0, y, 0.0);
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KMatrixHandle::zHandleMoved ( void * handleData )
{
    KPosition delta = ((KHandleData*)handleData)->mouseEvent->delta;

    GLfloat z = Controller.modules->objects->getProjection()->getZValueForScreenDeltasAndMatrix 
                                                                    (delta.x, delta.y, getWorldMatrix());
    translate(0.0, 0.0, z);
    notify();
}

