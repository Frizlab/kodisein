/*
 *  KConnectorAttributeIn.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KConnectorAttributeIn.h"
#include "KObjectModule.h"
#include "KModuleTexture.h"
#include "KModuleColor.h"
#include "KModuleLight.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorAttributeIn, KDS_CONNECTOR_ATTRIBUTE_IN, KDS_CONNECTOR_ATTRIBUTE_OUT)

// --------------------------------------------------------------------------------------------------------
void KConnectorAttributeIn::render ()
{
    bool popAttributes = false;
    KModule * attribModule = NULL;
    if (module->getClassId() >= KAttributeModule::classId())
    {
        attribModule = module;
    }
    else if (isConnected())
    {
        attribModule = getConnectedModule();
    }
    
    GLint retval[2];
    glGetIntegerv(GL_POLYGON_MODE, retval);
    
    if (attribModule && retval[1] != GL_LINE &&
        (attribModule->getClassId() >= KTextureModule::classId() ||
         attribModule->getClassId() >= KModuleColor::classId()))
    {
        popAttributes = true;
        ((KAttributeModule*)attribModule)->apply();
    }
    
    glPushMatrix();
    glTranslatef(0.0f, -KDS_CONNECTOR_MIN_DISTANCE, 0.0f);
    
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);

    GLfloat h = 0.4f, bw = 0.4f, rbw = bw/2.0f;

    if (module == attribModule || module->getClassId() >= KModuleLight::classId())
    {
        glTexCoord2f(  1.0,   0.0); glVertex3f(-1.0, 0, -1.0); glEdgeFlag(false);
        glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, 0,  1.0); glEdgeFlag(true);
        glTexCoord2f(  rbw,   rbw); glVertex3f(bw-1, 0, 1-bw); glEdgeFlag(false);
        glTexCoord2f(1-rbw,   rbw); glVertex3f(bw-1, 0, bw-1); glEdgeFlag(true); 
                
        glTexCoord2f(  0.0,   1.0); glVertex3f( 1.0, 0,  1.0); glEdgeFlag(false);
        glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0, 0, -1.0); glEdgeFlag(true);
        glTexCoord2f(1-rbw, 1-rbw); glVertex3f(1-bw, 0, bw-1); glEdgeFlag(false);
        glTexCoord2f(  rbw, 1-rbw); glVertex3f(1-bw, 0, 1-bw); glEdgeFlag(true);
    
        glTexCoord2f(  1.0,   1.0); glVertex3f( 1.0, 0, -1.0); glEdgeFlag(false); 
        glTexCoord2f(  1.0,   0.0); glVertex3f(-1.0, 0, -1.0); glEdgeFlag(true); 
        glTexCoord2f(1-rbw,   rbw); glVertex3f(bw-1, 0, bw-1); glEdgeFlag(false); 
        glTexCoord2f(1-rbw, 1-rbw); glVertex3f(1-bw, 0, bw-1); glEdgeFlag(true); 
        
        glTexCoord2f(  0.0,   0.0); glVertex3f(-1.0, 0,  1.0); glEdgeFlag(false); 
        glTexCoord2f(  0.0,   1.0); glVertex3f( 1.0, 0,  1.0); glEdgeFlag(true); 
        glTexCoord2f(  rbw, 1-rbw); glVertex3f(1-bw, 0, 1-bw); glEdgeFlag(false);     
        glTexCoord2f(  rbw,   rbw); glVertex3f(bw-1, 0, 1-bw); glEdgeFlag(true); 
       
        RECTANGLE_XY(bw-1, 1-bw, -h,  0, bw-1);
        RECTANGLE_YX(bw-1, 1-bw, -h,  0, 1-bw);
        RECTANGLE_YZ(-h,  0, bw-1, 1-bw, bw-1);
        RECTANGLE_ZY(-h,  0, bw-1, 1-bw, 1-bw); 
    }
    else
    {
        glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, 0, -1.0); 
        glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 0,  1.0); 
        glTexCoord2f(0.0, 1.0); glVertex3f( 1.0, 0,  1.0); 
        glTexCoord2f(1.0, 1.0); glVertex3f( 1.0, 0, -1.0);      
    }
    glEnd();
    
    glPopMatrix();
    
    if (popAttributes) ((KAttributeModule*)attribModule)->postApply();
}
