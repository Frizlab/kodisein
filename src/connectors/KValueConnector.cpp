/*
 *  KValueConnector.cpp
 *  kodisein
 */

#include "KValueConnector.h"
#include "KModule.h"

KDL_CLASS_INTROSPECTION_1 (KValueConnector, KConnector)

// --------------------------------------------------------------------------------------------------------
void KValueConnector::display ()
{
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT | GL_LINE_BIT);
    
    if (picked || selected)	glColor3f(1.0, 1.0, 1.0);
    else 			module->getModuleColor().glColor();
    
    loadId();
    
    glPushMatrix();
    glMultMatrix();
    render();
    glPopMatrix();
    
    glPopAttrib();
}

