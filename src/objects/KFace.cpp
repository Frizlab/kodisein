/*
 *  KFace.cpp
 *  kodisein
 */

#include "KFace.h"
#include "KModuleTexture.h"
#include "KConsole.h"
#include "KObjects.h"
#include "KController.h"
#include "KXMLTools.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KFace, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KFace::KFace ( KMatrixModule * m ) : KMatrixHandle ( m )
{
    addVertex(new KVertexHandle(this,-1.0, -1.0, 0.0));
    addVertex(new KVertexHandle(this, 1.0, -1.0, 0.0));
    addVertex(new KVertexHandle(this, 1.0,  1.0, 0.0));
    addVertex(new KVertexHandle(this,-1.0,  1.0, 0.0));
}

// --------------------------------------------------------------------------------------------------------
void KFace::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        KMatrixHandle::display(mode);
        unloadId();
        glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        glBegin(GL_LINE_LOOP);
        for (int index = 0; index < 4; index++) vertices[index]->getPosition().glVertex();
        glEnd();
        glPopAttrib();
    }
    else if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        glMultMatrixf(matrix);
        
        glBegin(GL_POLYGON);
        glNormal3f(0.0, 0.0, 1.0);
        for (int index = 0; index < 4; index++)
        {
            if      (index == 0)	glTexCoord2d(0.0, 0.0);
            else if (index == 1)	glTexCoord2d(1.0, 0.0);
            else if (index == 2)	glTexCoord2d(1.0, 1.0);
            else			glTexCoord2d(0.0, 1.0);
            
            vertices[index]->getPosition().glVertex();
        }
        glEnd();
    }
}

// --------------------------------------------------------------------------------------------------------
void KFace::vertexMoved ( void * handleData )
{
    KVertexHandle * vertexHandle = (KVertexHandle*)handleData;
    vertexHandle->setPosition(KVector((*vertexHandle)[TX], (*vertexHandle)[TY]), false);
}

// --------------------------------------------------------------------------------------------------------
void KFace::addVertex( KVertexHandle * vertex )
{
    vertex->addReceiverCallback(this, (KSetDataPtr)&KFace::vertexMoved, KDL_NOTIFICATION_TYPE_VERTEX_MOVED);
    vertices.push_back(vertex);
    handles.push_back(vertex);
}

// --------------------------------------------------------------------------------------------------------
GLfloat KFace::getDepthValue ( ) const
{    
    GLdouble	model[16], proj[16];
    GLint	view[4];
    
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, view);
    
    KVector center;
    GLdouble wx, wy, wz;
    
    vector<KVertexHandle*>::const_iterator iter = vertices.begin();
    while (iter != vertices.end())
    {
        center += (*iter)->getPosition();
    }
    center /= vertices.size();
    
    if (gluProject(center[X], center[Y], center[Z], model, proj, view, &wx, &wy, &wz) == false)
    {
        KConsole::printError("gluProject failed!\n\nunable to calculate depth value of face!"); return 0.0;
    }
    
    return wz;
}

// --------------------------------------------------------------------------------------------------------
void KFace::setXMLValues ( string & values )
{
    vector<KVertexHandle*>::const_iterator iter = vertices.begin();
    while (iter != vertices.end())
    {
        KVector pos;
        if (kXMLParseValue(values, "vertex", KDL_XML_VALUE_VERTEX, &pos)) (*iter)->setPosition(pos);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
string KFace::getXMLValues ( int depth ) const
{
    string xml;
    vector<KVertexHandle*>::const_iterator iter = vertices.begin();
    while (iter != vertices.end())
    {
        KVector pos = (*iter)->getPosition();
        xml += kXMLValue("vertex", KDL_XML_VALUE_VERTEX, &pos, depth+KDL_XML_INDENT);
        iter++;
    }
    return xml;
}
