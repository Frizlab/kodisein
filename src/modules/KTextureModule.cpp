/*
 *  KTextureModule.cpp
 *  kodisein
 */

#include "KTextureModule.h"
#include "KConnectorIntValueInOut.h"
#include "KConnectorAttributeIn.h"
#include "KConnectorAttributeOut.h"

KDL_CLASS_INTROSPECTION_1	(KTextureModule, KAttributeModule)

// --------------------------------------------------------------------------------------------------------
KTextureModule::KTextureModule () : KAttributeModule ()
{
    color = KColor(0.0, 0.0, 0.0, 0.0);
    texture_env_mode  = GL_MODULATE;
    s_generation_mode = 0;
    t_generation_mode = 0;
}

// --------------------------------------------------------------------------------------------------------
void KTextureModule::apply ()
{
    glPushAttrib (GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_TEXTURE_BIT);
    
    if (getTextureId())
    {
        glBindTexture (GL_TEXTURE_2D, getTextureId());
        glEnable      (GL_TEXTURE_2D);
        glTexEnvi     (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, texture_env_mode);
        
        if (texture_env_mode == GL_BLEND)
        {
            glTexEnvfv (GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color.getValues());
        }
        
        if (s_generation_mode)
        {
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, s_generation_mode);
            glEnable(GL_TEXTURE_GEN_S);
        }
        if (t_generation_mode)
        {
            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, t_generation_mode);
            glEnable(GL_TEXTURE_GEN_T);
        }
    }
    KAttributeModule::apply();
}

// --------------------------------------------------------------------------------------------------------
void KTextureModule::postApply ()
{
    if (texture_env_mode == GL_BLEND)
    {
        glTexEnvfv (GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, KColor(0.0, 0.0, 0.0, 0.0).getValues());
    }
    glTexEnvi     (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    KAttributeModule::postApply();
}

// --------------------------------------------------------------------------------------------------------
void KTextureModule::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    vector<string> names;
    names.push_back("replace");
    names.push_back("modulate");
    names.push_back("decal");
    names.push_back("blend");
    vector<int> enums;
    enums.push_back(GL_REPLACE);
    enums.push_back(GL_MODULATE);
    enums.push_back(GL_DECAL);
    enums.push_back(GL_BLEND);
        
    ioConnector = new KConnectorIntValueInOut( this, names, enums, "env mode" );
    ioConnector->translate (1.2f, 0.0, 0.0); 
    ioConnector->rotate(0.0, 0.0, -90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KTextureModule::setTextureEnvMode);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KTextureModule::getTextureEnvMode);  

    names.clear();
    names.push_back("linear");
    names.push_back("sphere map");
    names.push_back("object linear");
    names.push_back("eye linear");
    enums.clear();
    enums.push_back(0);
    enums.push_back(GL_SPHERE_MAP);
    enums.push_back(GL_OBJECT_LINEAR);
    enums.push_back(GL_EYE_LINEAR);
        
    ioConnector = new KConnectorIntValueInOut( this, names, enums, "s generation mode" );
    ioConnector->translate (0.33f, 0.0, -1.2f);
    ioConnector->rotate(-90.0f, 90.0f, 0.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KTextureModule::setSGenerationMode);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KTextureModule::getSGenerationMode);  

    ioConnector = new KConnectorIntValueInOut( this, names, enums, "t generation mode" );
    ioConnector->translate (-0.33f, 0.0, -1.2f); 
    ioConnector->rotate(-90.0f, 90.0f, 0.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KTextureModule::setTGenerationMode);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KTextureModule::getTGenerationMode);
    
    NEW_IO_CONNECTOR("blend red",   0,  1, 1, 3, (KObject*)&color, KColor, setRed, 	getRed)
    NEW_IO_CONNECTOR("blend green", 0,  1, 2, 3, (KObject*)&color, KColor, setGreen,	getGreen)
    NEW_IO_CONNECTOR("blend blue",  0,  1, 3, 3, (KObject*)&color, KColor, setBlue, 	getBlue)

    KConnector * connector;

    connector = new KConnectorAttributeOut( this, "texture out" );
    connector->translate (0.0, -0.20f, 0.0); 
    connector->rotate (180.0f, 0.0, 0.0);
    addConnector(connector);
    
    KAttributeModule::createConnectors();

    connector = new KConnectorAttributeIn( this );
    connector->translate (0.0, KDS_VALUECONNECTOR_RADIUS + KDS_CONNECTOR_MIN_DISTANCE, 0.0);
    addConnector(connector);
}

