/*
 *  KModuleTexture.cpp
 *  kodisein
 */

#include "KModuleTexture.h"
#include "KController.h"
#include "KConnectorIntValueInOut.h"
#include "KTextureSets.h"
#include "KTextureSet.h"
#include "KTexture.h"

KDL_CLASS_INTROSPECTION_1	(KModuleTexture, KTextureModule)
KDS_MODULE_VALUES		(KModuleTexture, "Texture", 0.5f, 0.5f, 0.5f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleTexture::KModuleTexture () : KTextureModule ()
{
    batch_index   = 0.0;
    texture_index = 0.0;
    version_index = 0.0;
    
    createIndexConnectors();
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
GLuint KModuleTexture::getTextureId ()
{
    KTextureSet * textureSet = Controller.texture_sets->getCurrentTextureSet();
    if (textureSet == NULL) return 0;
    KTexture * texture = textureSet->getIndexedTexture (batch_index, texture_index, version_index);
    if (texture) return texture->getTextureId();
    return 0;
}

// --------------------------------------------------------------------------------------------------------
void KModuleTexture::createIndexConnectors ()
{
    KConnectorValueInOut * ioConnector;
 
    NEW_IO_CONNECTOR("batch index", -1, 0, 3, 3, (KObject*)this, KModuleTexture, 
                                                                    setBatchIndex,   getBatchIndex)
    NEW_IO_CONNECTOR("texture index", -1, 0, 2, 3, (KObject*)this, KModuleTexture, 
                                                                    setTextureIndex, getTextureIndex)
    NEW_IO_CONNECTOR("version index", -1, 0, 1, 3, (KObject*)this, KModuleTexture, 
                                                                    setVersionIndex, getVersionIndex)
}

