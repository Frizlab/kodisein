/*
 *  KModuleParticle.cpp
 *  kodisein
 */

#include "KModuleParticle.h"
#include "KModuleVertex.h"
#include "KConnectorIntValueInOut.h"
#include "KConnectorValueInOut.h"
#include "KConnectorParticleIn.h"
#include "KConnectorMatrixOut.h"
#include "KMatrixHandle.h"
#include "KConsole.h"
#include "KController.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_1 	(KModuleParticle, KMatrixModule)
KDS_MODULE_VALUES		(KModuleParticle, "Particle", 1.0f, 1.0f, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleParticle::KModuleParticle () : KMatrixModule ()
{
    matrix_object = new KMatrixHandle (this);
    
    lifetime 	    = 4000;
    connection_mode = -1;

    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleParticle::createConnectors ()
{
    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR_TR("lifetime", 1.2f, 0.0, 0.0, 0.0, 0.0, -90.0, (KObject*)this, 
                                                            KModuleParticle, setLifeTime, getLifeTime)

    vector<string> names;
    names.push_back("objects");
    names.push_back("points");
    names.push_back("lines");
    names.push_back("line strip");
    names.push_back("triangles");
    names.push_back("triangle strip");
    names.push_back("triangle fan");
    names.push_back("quads");
    names.push_back("quad strip");
    names.push_back("polygon");
    vector<int> enums;
    enums.push_back(-1);
    enums.push_back(GL_POINTS);
    enums.push_back(GL_LINES);
    enums.push_back(GL_LINE_STRIP);
    enums.push_back(GL_TRIANGLES);
    enums.push_back(GL_TRIANGLE_STRIP);
    enums.push_back(GL_TRIANGLE_FAN);
    enums.push_back(GL_QUADS);
    enums.push_back(GL_QUAD_STRIP);
    enums.push_back(GL_POLYGON);
        
    ioConnector = new KConnectorIntValueInOut( this, names, enums, "mode" );
    ioConnector->translate (-1.2f, 0.0, 0.0); 
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetIntPtr)&KModuleParticle::setConnectionMode);
    values.back()->setProviderCallback(this, (KGetIntPtr)&KModuleParticle::getConnectionMode);  

    KConnector * connector;

    connector = new KConnectorMatrixOut( this ); 
    connector->translate (0.0, 1.5, 0.0); // top
    addConnector(connector);

    connector = new KConnectorParticleIn( this, "particle emitter" );
    connector->translate (0.0, -1.0, 0.0); // bottom
    connector->rotate    (180.0, 0.0, 0.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
void KModuleParticle::setLifeTime ( float f )
{
    lifetime = kMax(1, (int)f);
}

// --------------------------------------------------------------------------------------------------------
void KModuleParticle::emit ()
{
    particles.push_back(new KParticle());
    *((KMatrix*)particles.back()) = getWorldMatrix();
}

// --------------------------------------------------------------------------------------------------------
void KModuleParticle::display ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        KMatrixModule::display(mode);
    }
    else //(mode == KDS_APPLICATION_MODE_ANIMATION || mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        if (mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
        {
            KMatrixModule::display(mode);
        }
        glPushMatrix();
        unsigned int now = KEventHandler::getTime();
        
        KMatrixModule * parentModule = (KMatrixModule*)getParentModule();
        if (parentModule) parentModule->getWorldMatrix().getInverse().glMultMatrix();

        KMatrixModule * matrixModule = (KMatrixModule*)getConnectorWithName("matrix out")->getConnectedModule();

        if (connection_mode >= 0)
        {
            glBegin(connection_mode);
            vector<KParticle*>::iterator iter = particles.begin();
            while (iter != particles.end())
            {
                if ((*iter)->getAge(now) > lifetime) // delete old particles
                {
                    delete (*iter);
                    iter = particles.erase(iter);
                    continue;
                }
                
                if (matrixModule)
                {
                    matrixModule->apply(*(*iter));
                }
                else
                {
                    (*iter)->getPosition().glVertex();
                }
                iter++;
            }
            glEnd();
        }            
        else
        {
            if (matrixModule)
            {
                vector<KParticle*>::iterator iter = particles.begin();
                while (iter != particles.end())
                {
                    if ((*iter)->getAge(now) > lifetime) // delete old particles
                    {
                        delete (*iter);
                        iter = particles.erase(iter);
                        continue;
                    }
                    glPushMatrix();
                    (*iter)->glMultMatrix();
                    matrixModule->display(mode);
                    glPopMatrix();
                    iter++;
                }
            }
        }
        glPopMatrix();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleParticle::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    loadId();
        
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
    
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    kDisplaySolidSphere(1.0, Controller.getFastDisplay() ? 4 : 8);
    glPopMatrix();
}

