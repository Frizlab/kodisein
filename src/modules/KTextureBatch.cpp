/*
 *  KTextureBatch.cpp
 *  kodisein
 */

#include "KTextureBatch.h"
#include "KConnectorTextureBatchIn.h"
#include "KConnectorTextureBatchOut.h"
#include "KConnectorTextureFileOut.h"
#include "KTextureFile.h"
#include "KTexture.h"
#include "KConsole.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_1 	(KTextureBatch, KModule)
KDS_MODULE_VALUES       	(KTextureBatch, "TextureBatch", 0.5, 0.5, 0.5, 0.6f)

#define PREV_BATCH	"previous batch"
#define NEXT_BATCH 	"next batch"
#define FIRST_TEXTURE	"first texture"

// --------------------------------------------------------------------------------------------------------
KTextureBatch::KTextureBatch () : KModule ()
{
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KTextureBatch::createConnectors ()
{
    KConnector * connector;

    connector = new KConnectorTextureBatchOut( this, NEXT_BATCH );
    connector->translate (0.0, 0.75, 0.0); // top
    connector->rotate (0.0, -90.0, 0.0);
    addConnector(connector);

    connector = new KConnectorTextureFileOut( this, FIRST_TEXTURE );
    connector->translate (1.25, 0.0, 0.0); // right
    connector->rotate (90.0, 0.0, -90.0);
    addConnector(connector);

    connector = new KConnectorTextureBatchIn( this , PREV_BATCH );
    connector->translate (0.0, -0.25, 0.0); // bottom
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
static void fillGap ()
{
    float g = 0.25;
    glBegin(GL_QUADS);
    glNormal3f(-sin(atan(g/(1.0-g))), cos(atan(g/(1.0-g))), 0.0);
    glVertex3f(g,   0.0, -g);
    glVertex3f(g,   0.0,  g);
    glVertex3f(1.0,   g,  g);
    glVertex3f(1.0,   g, -g);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(g,   0.0, -g);
    glVertex3f(1.0,   g, -g);
    glVertex3f(g,     g, -g);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(g,   0.0,  g);
    glVertex3f(g,     g,  g);
    glVertex3f(1.0,   g,  g);
    glEnd();
}

// --------------------------------------------------------------------------------------------------------
void KTextureBatch::displayConnectors (int mode)
{	
    KModule::displayConnectors(mode);
    loadId();

    float g = 0.25;
   
    glPushMatrix();
    fillGap();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap();    
    glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap();
    glRotatef(90.0,  0.0, 1.0, 0.0);
    glRotatef(180.0, 1.0, 0.0, 0.0);
    fillGap();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap();    
    glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap();    
    glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap();    
    glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap();    
    glPopMatrix();

    glBegin(GL_QUADS);
    RECTANGLE_XY(-1.0,   1.0, -g,  g,  1.0); // front
    RECTANGLE_YX(-1.0,   1.0, -g,  g, -1.0); // back
    RECTANGLE_ZY(-g, g,  -1.0,   1.0, -1.0); // left
    glEnd();
}

// --------------------------------------------------------------------------------------------------------
int KTextureBatch::getIndex () const
{
    KModule * parentModule = getConnectorWithName(PREV_BATCH)->getConnectedModule();
    if (parentModule && parentModule->getClassId() >= KTextureBatch::classId())
    {
        return ((KTextureBatch*)parentModule)->getIndex()+1;
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
KTextureBatch * KTextureBatch::getNthChildBatch ( int n ) const
{
    if (n == 0) return (KTextureBatch*)this;
    KModule * childModule = getConnectorWithName(NEXT_BATCH)->getConnectedModule();
    if (childModule)
    {
        return ((KTextureBatch*)childModule)->getNthChildBatch(n-1);
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KTextureBatch::reload ()
{
    KTextureFile * textureFile = (KTextureFile*)getConnectorWithName(FIRST_TEXTURE)->getConnectedModule();
    if (textureFile)
    {
        textureFile->reload();
    }

    KTextureBatch * nextBatch = (KTextureBatch*)getConnectorWithName(NEXT_BATCH)->getConnectedModule();
    if (nextBatch)
    {
        nextBatch->reload();
    }
}

// --------------------------------------------------------------------------------------------------------
int KTextureBatch::getNumberOfChildBatches () const
{
    KModule * childModule = getConnectorWithName(NEXT_BATCH)->getConnectedModule();
    if (childModule)
    {
        return ((KTextureBatch*)childModule)->getNumberOfChildBatches()+1;
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
string KTextureBatch::getDisplayName () const
{ 
    return kStringPrintf("[%s %d]", getName().c_str(), getIndex()); 
}
 
// --------------------------------------------------------------------------------------------------------
KTexture * KTextureBatch::getIndexedTexture ( int textureIndex, int versionIndex ) const
{
    int textures = 0;
    KTextureFile * textureFile = (KTextureFile*)getConnectorWithName(FIRST_TEXTURE)->getConnectedModule();
    if (textureFile)
    {
        textures = textureFile->getNumberOfChildFiles() + 1;
    }
    else return NULL;

    return textureFile->getNthChildFile(textureIndex % textures)->getIndexedTexture(versionIndex);
}

