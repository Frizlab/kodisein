/*
 *  KText.cpp
 *  kodisein
 */

#include "KText.h"
#include "KFace.h"
#include "KController.h"
#include "KTools.h"

#include <GLUT/glut.h>

KDL_CLASS_INTROSPECTION_1 (KText, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KText::KText ( KMatrixModule * m ) : KMatrixHandle ( m )
{
    font = GLUT_STROKE_ROMAN;
    text = "text";
}

// --------------------------------------------------------------------------------------------------------
void KText::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        glPushAttrib(GL_ENABLE_BIT);
        KMatrixHandle::display(mode);
        unloadId();
        glDisable(GL_LIGHTING);
        KVector position;
        kDisplayString ( text, position, font );
        glPopAttrib();
    }
    else if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        glMultMatrixf(matrix);
        KVector position;
        kDisplayString ( text, position, font );
    }
}

