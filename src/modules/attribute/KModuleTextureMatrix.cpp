/*
 *  KModuleTextureMatrix.cpp
 *  kodisein
 */

#include "KModuleTextureMatrix.h"
#include "KConnectorValueInOut.h"
#include "KConnectorAttributeOut.h"
#include "KConnectorAttributeIn.h"

KDL_CLASS_INTROSPECTION_1	(KModuleTextureMatrix, KAttributeModule)
KDS_MODULE_VALUES   	(KModuleTextureMatrix, "TextureMatrix", 1.0, 1.0, 1.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleTextureMatrix::KModuleTextureMatrix () : KAttributeModule ()
{
    createConnectors();
    createMatrixConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleTextureMatrix::apply ()
{    
    glPushAttrib(GL_TEXTURE_BIT);
    
    GLint matrixMode;
    glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    texture_matrix.glMultMatrix();
    glMatrixMode(matrixMode);
    
    KAttributeModule::apply();
}

// --------------------------------------------------------------------------------------------------------
void KModuleTextureMatrix::postApply ()
{
    GLint matrixMode;
    glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(matrixMode);

    KAttributeModule::postApply();
}

// --------------------------------------------------------------------------------------------------------
void KModuleTextureMatrix::createMatrixConnectors () 
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR("pos x", 0, -1, 1, 2, (KObject*)&texture_matrix, KSeparatedMatrix, setTX, getTX)
    NEW_IO_CONNECTOR("pos y", 0, -1, 2, 2, (KObject*)&texture_matrix, KSeparatedMatrix, setTY, getTY)

    NEW_IO_CONNECTOR("size x", 0,  1, 1, 2, (KObject*)&texture_matrix, KSeparatedMatrix, setSX, getSX)
    NEW_IO_CONNECTOR("size y", 0,  1, 2, 2, (KObject*)&texture_matrix, KSeparatedMatrix, setSY, getSY)

    NEW_IO_CONNECTOR("rot x", 1,  0, 1, 2, (KObject*)&texture_matrix, KSeparatedMatrix, setRX, getRX)
    NEW_IO_CONNECTOR("rot y", 1,  0, 2, 2, (KObject*)&texture_matrix, KSeparatedMatrix, setRY, getRY)

    KConnector * connector;
        
    connector = new KConnectorAttributeOut( this, "texture matrix out" ); 
    connector->translate (0.0, -0.20f, 0.0); 
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
    
    KAttributeModule::createConnectors();

    connector = new KConnectorAttributeIn( this ); 
    connector->translate (0.0, KDS_VALUECONNECTOR_RADIUS + KDS_CONNECTOR_MIN_DISTANCE, 0.0);
    addConnector(connector);
}


