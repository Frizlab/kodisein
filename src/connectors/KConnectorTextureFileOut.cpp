/*
 *  KConnectorTextureFileOut.cpp
 *  kodisein
 */

#include "KConnectorTextureFileOut.h"
#include "KTextureFile.h"
#include "KTools.h"

KDS_CONNECTION_VALUES (KConnectorTextureFileOut, KDS_CONNECTOR_TEXTURE_FILE_OUT, KDS_CONNECTOR_TEXTURE_FILE_IN)

// --------------------------------------------------------------------------------------------------------
void KConnectorTextureFileOut::render ()
{
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  1.0, -0.25,  0.25, -0.25);
    glEnd();
}

// --------------------------------------------------------------------------------------------------------
bool KConnectorTextureFileOut::isAcceptingConnections () const
{
    if (module->getClassId() >= KTextureFile::classId() && 
        ((KTextureFile*)module)->isTextureVersion()) return false;
    return KConnector::isAcceptingConnections();
}
