/*
 *  KCamera.cpp
 *  kodisein
 */

#include "KCamera.h"
#include "KPerspectiveProjection.h"
#include "KOrthographicProjection.h"
#include "KModules.h"
#include "KObjects.h"
#include "KConsole.h"
#include "KController.h"

KDL_CLASS_INTROSPECTION_1 (KCamera, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KCamera::KCamera ( KMatrixModule * m ) : KMatrixHandle ( m )
{
    projection = new KPerspectiveProjection(60.0);
    projection->setViewport(0.0, 0.0, 1.0, 1.0);
    projection->transform(getWorldMatrix());
}

// --------------------------------------------------------------------------------------------------------
void KCamera::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        KMatrixHandle::display(mode);
        
        if (Controller.modules->objects->flags[KDS_OBJECTS_FLAG_DISPLAY_CAMERAS]) 
        {
            glPushAttrib( GL_CURRENT_BIT | GL_LIGHTING_BIT );
            module->getModuleColor().glColor();
            render();
            glPopAttrib();
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KCamera::setPerspective ( bool b ) 
{
    if (getPerspective() != b)
    {
        KProjection * oldProjection = projection;
        
        if (b)
        {
            projection = new KPerspectiveProjection (*oldProjection);
        }
        else
        {
            projection = new KOrthographicProjection (*oldProjection);
        }
        
        delete oldProjection;
    }
}

// --------------------------------------------------------------------------------------------------------
bool KCamera::getPerspective () const
{
    return (projection->getClassId() >= KPerspectiveProjection::classId());
}

// --------------------------------------------------------------------------------------------------------
void KCamera::notify () const
{
    *((KMatrix*)projection) = getWorldMatrix();
    KHandle::notify();
}

// --------------------------------------------------------------------------------------------------------
void KCamera::initInspector ( KModuleInspector * inspector )
{
    initInspectorPosition(inspector);
    initInspectorRotation(inspector);
}

// --------------------------------------------------------------------------------------------------------
void KCamera::render ()
{
    unloadId();
    glDisable(GL_LIGHTING);

    GLfloat zf	= projection->getZFar() / 10.0;
    GLfloat zn	= projection->getZNear();

    GLfloat sinus   = sin(DEG2RAD(projection->getFov()/2.0));
    GLfloat cosinus = cos(DEG2RAD(projection->getFov()/2.0));
    GLfloat ar	    = projection->getCurrentAspectRatio();
    GLfloat zback   = -cosinus * zf;
    GLfloat zfront  = -cosinus * zn;
 
    if (getPerspective())
    {   
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, zback);
        glVertex3f(sinus * ar * zn, 	-sinus * zn, 	zfront);
        glVertex3f(sinus * ar * zf, 	-sinus * zf,	zback);
        glVertex3f(-sinus * ar * zn, 	sinus * zn, 	zfront);
        glVertex3f(-sinus * ar * zf,	sinus * zf, 	zback);
        glVertex3f(-sinus * ar * zn, 	-sinus * zn, 	zfront);
        glVertex3f(-sinus * ar * zf,	-sinus * zf,	zback);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        glVertex3f(sinus * ar * zn,	sinus * zn,	zfront);
        glVertex3f(sinus * ar * zn,	-sinus * zn,	zfront);
        glVertex3f(-sinus * ar * zn,	-sinus * zn,	zfront);
        glVertex3f(-sinus * ar * zn,	sinus * zn, 	zfront);
        glVertex3f(sinus * ar * zn,	sinus * zn,	zfront);
        glVertex3f(sinus * ar * zf, 	sinus * zf,	zback);
        glVertex3f(sinus * ar * zf,	-sinus * zf,	zback);
        glVertex3f(-sinus * ar * zf,	-sinus * zf,	zback);
        glVertex3f(-sinus * ar * zf,	sinus * zf, 	zback);
        glVertex3f(sinus * ar * zf, 	sinus * zf,	zback);
        glEnd();
    }
    else
    {
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, zback);
        glVertex3f(sinus * ar * zf, 	-sinus * zf, 	zfront);
        glVertex3f(sinus * ar * zf, 	-sinus * zf,	zback);
        glVertex3f(-sinus * ar * zf, 	sinus * zf, 	zfront);
        glVertex3f(-sinus * ar * zf,	sinus * zf, 	zback);
        glVertex3f(-sinus * ar * zf, 	-sinus * zf, 	zfront);
        glVertex3f(-sinus * ar * zf,	-sinus * zf,	zback);
        glVertex3f(sinus * ar * zf, 	sinus * zf, 	zfront);
        glVertex3f(sinus * ar * zf,	sinus * zf,	zback);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex3f(sinus * ar * zf,	sinus * zf,	zfront);
        glVertex3f(sinus * ar * zf,	-sinus * zf,	zfront);
        glVertex3f(-sinus * ar * zf,	-sinus * zf,	zfront);
        glVertex3f(-sinus * ar * zf,	sinus * zf, 	zfront);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex3f(sinus * ar * zf, 	sinus * zf,	zback);
        glVertex3f(sinus * ar * zf,	-sinus * zf,	zback);
        glVertex3f(-sinus * ar * zf,	-sinus * zf,	zback);
        glVertex3f(-sinus * ar * zf,	sinus * zf, 	zback);
        glEnd();
    }
}