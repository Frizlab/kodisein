/*
 *  KLandscape.cpp
 *  kodisein
 */

#include "KLandscape.h"
#include "KVertexHandle.h"
#include "KConsole.h"
#include "KObjects.h"
#include "KController.h"
#include "KXMLTools.h"

#include <algorithm>

KDL_CLASS_INTROSPECTION_1 (KLandscape, KMatrixHandle)

// --------------------------------------------------------------------------------------------------------
KLandscape::KLandscape ( KMatrixModule * m ) : KMatrixHandle ( m )
{
    u_order = 3;
    v_order = 3;
    
    u_steps = 10;
    v_steps = 10;
    
    createControllPoints();
}

// --------------------------------------------------------------------------------------------------------
void KLandscape::createControllPoints ()
{
    while (vertices.empty() == false)
    {
        handles.erase(find(handles.begin(), handles.end(), vertices.back()));
        delete vertices.back();
        vertices.pop_back();
    }

    for (int u = 0; u < u_order; u++)
    {
        for (int v = 0; v < v_order; v++)
        {
            vertices.push_back(new KVertexHandle(this, (float)u/u_order, u+v, (float)v/v_order ));
            handles.push_back(vertices.back());
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KLandscape::setUOrder ( float i )
{
    if (u_order != i)
    {
        u_order = kMin(5, kMax(2, (int)i));
        createControllPoints();
    }
}

// --------------------------------------------------------------------------------------------------------
void KLandscape::setVOrder ( float i )
{
    if (v_order != i)
    {
        v_order = kMin(5, kMax(2, (int)i));
        createControllPoints();
    }
}

// --------------------------------------------------------------------------------------------------------
void KLandscape::display ( int mode )
{
    GLint polygonMode = GL_LINE;

    glPushAttrib(GL_LIGHTING_BIT | GL_EVAL_BIT);

    if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        KMatrixHandle::display(mode);
        unloadId();
        glDisable(GL_LIGHTING);
    }
    else if (mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        glMultMatrixf(matrix);
        glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
        
        GLboolean texture;
        glGetBooleanv(GL_TEXTURE_2D, &texture);

        if (texture)
        {
            glEnable(GL_MAP2_TEXTURE_COORD_2);
            GLdouble texcoords[8] = { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 };
            glMap2d(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, texcoords);
        }
    }
    
    GLdouble * controllpoints = (GLdouble *)malloc(sizeof(GLdouble) * 3 * u_order * v_order);

    int index = 0;
    vector<KVertexHandle*>::iterator iter = vertices.begin();
    while (iter != vertices.end())
    {	
        KVector point = (*iter)->getPosition();
        controllpoints[index*3]   = point[X];
        controllpoints[index*3+1] = point[Y];
        controllpoints[index*3+2] = point[Z];

        iter++; 
        index++;
    }
    
    glEnable(GL_MAP2_VERTEX_3);
    glMap2d(GL_MAP2_VERTEX_3, 0, 1, 3, u_order, 0, 1, 3*u_order, v_order, controllpoints);
    glMapGrid2d(u_steps, 0, 1, v_steps, 0, 1);
    glEvalMesh2(polygonMode, 0, u_steps, 0, v_steps);
    
    glPopAttrib();
    
    free (controllpoints);
}

// --------------------------------------------------------------------------------------------------------
void KLandscape::setXMLValues ( string & values )
{
    vector<KVertexHandle*>::const_iterator iter = vertices.begin();
    while (iter != vertices.end())
    {
        KVector pos;
        if (kXMLParseValue(values, "controlpoint", KDL_XML_VALUE_VERTEX, &pos)) (*iter)->setPosition(pos);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
string KLandscape::getXMLValues ( int depth ) const
{
    string xml;
    vector<KVertexHandle*>::const_iterator iter = vertices.begin();
    while (iter != vertices.end())
    {
        KVector pos = (*iter)->getPosition();
        xml += kXMLValue("controlpoint", KDL_XML_VALUE_VERTEX, &pos, depth+KDL_XML_INDENT);
        iter++;
    }
    return xml;
}
