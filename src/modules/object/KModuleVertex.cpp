/*
 *  KModuleVertex.cpp
 *  kodisein
 */

#include "KModuleVertex.h"
#include "KConnectorMatrixOut.h"
#include "KConnectorMatrixIn.h"
#include "KBoolValueObject.h"
#include "KFloatValueObject.h"
#include "KVertex.h"
#include "KConsole.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleVertex, KMatrixModule)
KDS_MODULE_VALUES		(KModuleVertex, "Vertex", 1.0f, 1.0f, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
KModuleVertex::KModuleVertex () : KMatrixModule ()
{
    matrix_object = new KVertex (this);

    texture_s = 0.0;
    texture_t = 0.0;
    texture_coords = false;
    
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleVertex::apply ( KMatrix m ) const
{    
    if (texture_coords) glTexCoord2f(texture_s, texture_t);
    (m * (*matrix_object)).getPosition().glVertex();
    KMatrixModule::apply(m);
}

// --------------------------------------------------------------------------------------------------------
void KModuleVertex::createConnectors ()
{
    KConnector * connector;

    connector = new KConnectorMatrixOut( this, "matrix out 1" );
    connector->rotate(60.0, 0.0, 0.0);
    connector->translate (0.0, 1.5, 0.0); // top
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix out 2" );
    connector->rotate(-60.0,   0.0, 0.0);
    connector->translate (0.0, 1.5, 0.0); 
    addConnector(connector);

    connector = new KConnectorMatrixIn( this );
    connector->translate (0.0, -1.0, 0.0); // bottom
    connector->rotate    (180.0, 0.0, 0.0);
    addConnector(connector);
    
    KValueObject * value;

    value = new KBoolValueObject ( "texture coords" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KModuleVertex::setTextureCoords);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KModuleVertex::getTextureCoords);      
    
    value = new KFloatValueObject( "texture s" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetFloatPtr)&KModuleVertex::setTextureS);
    values.back()->setProviderCallback(this, (KGetFloatPtr)&KModuleVertex::getTextureS);      

    value = new KFloatValueObject( "texture t" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetFloatPtr)&KModuleVertex::setTextureT);
    values.back()->setProviderCallback(this, (KGetFloatPtr)&KModuleVertex::getTextureT);      
}

// --------------------------------------------------------------------------------------------------------
void fillGap ()
{
    float h = 0.8f;
    float s = sin(atan(1.0/h));
    float c = cos(atan(1.0/h));
    
    glBegin(GL_TRIANGLES);
    glNormal3f(s, -c, 0.0); // right
    glVertex3f(1.0, 1.0,    1.0);
    glVertex3f(0.0, 1.0-h,  0.0);
    glVertex3f(1.0, 1.0,   -1.0);
    
    glNormal3f(0.0, -c, s); // front
    glVertex3f(-1.0, 1.0,   1.0);
    glVertex3f( 0.0, 1.0-h, 0.0);
    glVertex3f( 1.0, 1.0,   1.0);
    
    glNormal3f(-s, -c, 0.0); // left
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f( 0.0, 1.0-h,  0.0);
    glVertex3f(-1.0, 1.0,  1.0);
    
    glNormal3f(0.0, -c, -s); // back
    glVertex3f( 1.0,  1.0,   -1.0);
    glVertex3f( 0.0,  1.0-h,  0.0);
    glVertex3f(-1.0,  1.0,   -1.0);
    glEnd();
}

// --------------------------------------------------------------------------------------------------------
void KModuleVertex::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    loadId();

    glPushMatrix();
    glRotatef(60.0, 1.0, 0.0, 0.0);
    fillGap();
    glRotatef(120, 1.0, 0.0, 0.0);
    fillGap();
    glRotatef(120.0, 1.0, 0.0, 0.0);
    fillGap();
    glPopMatrix();
        
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    kDisplaySolidSphere(0.5, 10);
    glPopMatrix();
}

