/*
 *  KModuleParticleEmitter.cpp
 *  kodisein
 */

#include "KModuleParticleEmitter.h"
#include "KModuleParticle.h"
#include "KConnectorValueInOut.h"
#include "KConnectorParticleOut.h"
#include "KConnectorMatrixIn.h"
#include "KMatrixHandle.h"
#include "KConsole.h"
#include "KController.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleParticleEmitter, KMatrixModule)
KDS_MODULE_VALUES		(KModuleParticleEmitter, "ParticleEmitter", 1.0f, 1.0f, 0.0f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleParticleEmitter::KModuleParticleEmitter () : KMatrixModule ()
{
    matrix_object = new KMatrixHandle (this);

    emitter_delay = 1;
    last_time	  = 0;

    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleParticleEmitter::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR_TR("emitter delay", 0.0, 1.2, 0.0, 0.0, 0.0, 0.0, (KObject*)this, 
                                                KModuleParticleEmitter, setEmitterDelay, getEmitterDelay)

    KConnector * connector;

    connector = new KConnectorParticleOut( this, "particle 1" );
    connector->translate (0.0, 0.0, 1.5); // front
    connector->rotate(90.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorParticleOut( this, "particle 2" );
    connector->translate (1.5, 0.0, 0.0); // right
    connector->rotate(0.0, 0.0, -90.0);
    addConnector(connector);

    connector = new KConnectorParticleOut( this, "particle 3" );
    connector->translate (0.0, 0.0, -1.5); // back
    connector->rotate(-90.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorParticleOut( this, "particle 4" );
    connector->translate (-1.5, 0.0, 0.0); // left
    connector->rotate(0.0, 0.0, 90.0);
    addConnector(connector);

    connector = new KConnectorMatrixIn( this ); 
    connector->translate (0.0, -1.0, 0.0); // bottom
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleParticleEmitter::display ( int mode )
{    
    if (mode == KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        KMatrixModule::display(mode);
    }
    else // (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS || mode == KDS_APPLICATION_MODE_ANIMATION)
    {
        preDisplay(mode);
        if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS) matrix_object->display(mode); 
        else matrix_object->glMultMatrix();

        bool emit = false;
        unsigned int now = SDL_GetTicks();
        if ((now - last_time) > emitter_delay) 
        {
            emit = true;
            last_time = now;
        }
        
        for (int i = 1; i < 5; i++)
        {
            KModule * particleModule;
            // WARNING: has to be changed (was getConnectorWithName(kStringPrintf("particle %d", i)))
            particleModule = ((KConnector*)connectors[i])->getConnectedModule();
            if (particleModule)
            {
                if (emit) ((KModuleParticle*)particleModule)->emit();
                particleModule->display(mode);
            }
        }
        postDisplay(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleParticleEmitter::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    loadId();
        
    float h = 0.8;
    float s = sin(atan(1.0/h));
    float c = cos(atan(1.0/h));
    
    glBegin(GL_TRIANGLES);
    glNormal3f(s, c, 0.0);	// right
    glVertex3f(1.0, -1.0,   -1.0);
    glVertex3f(0.0, -1.0+h,  0.0);
    glVertex3f(1.0, -1.0,    1.0);
    
    glNormal3f(0.0, c, s);	// front
    glVertex3f( 1.0, -1.0,   1.0);
    glVertex3f( 0.0, -1.0+h, 0.0);
    glVertex3f(-1.0, -1.0,   1.0);
    
    glNormal3f(-s, c, 0.0);	// left
    glVertex3f(-1.0, -1.0,    1.0);
    glVertex3f( 0.0, -1.0+h,  0.0);
    glVertex3f(-1.0, -1.0,   -1.0);
    
    glNormal3f(0.0, c, -s);	// back
    glVertex3f(-1.0, -1.0,   -1.0);
    glVertex3f( 0.0, -1.0+h,  0.0);
    glVertex3f( 1.0, -1.0,   -1.0);
    glEnd();
    
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    kDisplaySolidSphere(1.0, Controller.getFastDisplay() ? 4 : 8);
    glPopMatrix();
}

// --------------------------------------------------------------------------------------------------------
void KModuleParticleEmitter::setEmitterDelay ( float f )
{
    emitter_delay = kMax (1,(int)f);
}

// --------------------------------------------------------------------------------------------------------
KMatrixModule * KModuleParticleEmitter::getFirstChild () const
{
    KConnector * outConnector = getConnectorOfType(KDS_CONNECTOR_PARTICLE_OUT, KDS_USED_CONNECTOR);
    if (outConnector == NULL) return NULL;
    return (KMatrixModule*)outConnector->getConnectedModule();
}

