/*
 *  KConnectorAttributeOut.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KConnectorAttributeOut.h"

KDS_CONNECTION_VALUES (KConnectorAttributeOut, KDS_CONNECTOR_ATTRIBUTE_OUT, KDS_CONNECTOR_ATTRIBUTE_IN)

// --------------------------------------------------------------------------------------------------------
void KConnectorAttributeOut::render ()
{
    float bw = 0.4f;

    glBegin(GL_QUADS);
    
    glNormal3f(0.0, 1.0, 0.0);
    
    glVertex3f(-1.0, 0, -1.0); glEdgeFlag(false);
    glVertex3f(-1.0, 0,  1.0); glEdgeFlag(true);
    glVertex3f(bw-1, 0, 1-bw); glEdgeFlag(false); 
    glVertex3f(bw-1, 0, bw-1); glEdgeFlag(true); 
            
    glVertex3f(1-bw, 0, bw-1); glEdgeFlag(false);
    glVertex3f(1-bw, 0, 1-bw); glEdgeFlag(true);
    glVertex3f( 1.0, 0,  1.0); glEdgeFlag(false);
    glVertex3f( 1.0, 0, -1.0); glEdgeFlag(true);

    glVertex3f( 1.0, 0, -1.0); glEdgeFlag(false); 
    glVertex3f(-1.0, 0, -1.0); glEdgeFlag(true); 
    glVertex3f(bw-1, 0, bw-1); glEdgeFlag(false); 
    glVertex3f(1-bw, 0, bw-1); glEdgeFlag(true); 
    
    glVertex3f(1-bw, 0, 1-bw); glEdgeFlag(false);     
    glVertex3f(bw-1, 0, 1-bw); glEdgeFlag(true); 
    glVertex3f(-1.0, 0,  1.0); glEdgeFlag(false); 
    glVertex3f( 1.0, 0,  1.0); glEdgeFlag(true); 

    glEnd();
}
