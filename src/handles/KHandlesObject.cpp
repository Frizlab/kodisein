/*
 *  KHandlesObject.cpp
 *  kodisein
 */

#include "KHandlesObject.h"
#include "KController.h"
#include "KObjects.h"
#include "KModules.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 (KHandlesObject, KHandle)

// --------------------------------------------------------------------------------------------------------
KHandlesObject::KHandlesObject () : KHandle ()
{
    module = NULL;
}

// --------------------------------------------------------------------------------------------------------
KHandlesObject::KHandlesObject ( KMatrixModule * m ) : KHandle ()
{
    module = m; 
    Controller.modules->objects->addPickable(this);
}

// --------------------------------------------------------------------------------------------------------
KHandlesObject::~KHandlesObject ()
{
    if (module) Controller.modules->objects->removePickable(this);
    deleteHandles();
}

// --------------------------------------------------------------------------------------------------------
void KHandlesObject::setPicked ( bool p )
{
    if (p != picked)
    {
        KPickable::setPicked(p);
        if (p) Controller.modules->pickModule(module);
        else   Controller.modules->pickModule(NULL);
    }
}

// -------------------------------------------------------------------------------------------------------- 
KMatrix KHandlesObject::getWorldMatrix () const
{
    if (parent) return (parent->getWorldMatrix() * (*this));
    if (module && module->getParentModule()) 
    {
        return ((KMatrixModule*)module->getParentModule())->getWorldMatrix() * (*this);
    }
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
void KHandlesObject::setOrigin ( void * handleData )
{
    KMatrix fm = getWorldMatrix();
    translate(fm.getInverse() * (*((KHandleData*)handleData)->pos - fm.getPosition()));
    notify();
}

// --------------------------------------------------------------------------------------------------------
void KHandlesObject::setPosition ( const KVector & pos, bool sendNotification ) 
{
    KSeparatedMatrix::setPosition(pos);
    if (sendNotification) notify();
}

// --------------------------------------------------------------------------------------------------------
void KHandlesObject::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        glPushAttrib( GL_CURRENT_BIT | GL_LIGHTING_BIT );

        if (module) 
        {
            module->getMatrixObject()->glMultMatrix();
            module->getModuleColor().glColor();
        }
        else
        {
            glColor4f(0.5, 0.5, 0.5, 1.0);
            glMultMatrix();
        }
        
        if (module == NULL || Controller.modules->objects->shouldModuleDisplayHandles(module))
        {
            PickableVector::const_iterator iter = handles.begin();
            while (iter != handles.end())
            {
                (*iter)->display(mode);
                iter++;
            }
        }
        else
        {
            glDisable(GL_LIGHTING);
            glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.5, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.5, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 0.5);
            glEnd();
        }
            
        glPopAttrib();
    }
}

// --------------------------------------------------------------------------------------------------------
void KHandlesObject::addHandle ( KHandle * handle )
{
    handles.push_back(handle);
}

// --------------------------------------------------------------------------------------------------------
void KHandlesObject::deleteHandles ()
{
    while (handles.empty() == false)
    {
        delete handles.back();
        handles.pop_back();
    }
}

