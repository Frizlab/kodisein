/*
 *  KModuleLSystem.cpp
 *  kodisein
 */

#include "KModuleLSystem.h"
#include "KConnectorMatrixOut.h"
#include "KConnectorMatrixIn.h"
#include "KConnectorValueInOut.h"
#include "KBoolValueObject.h"
#include "KMatrixHandle.h"
#include "KObjects.h"
#include "KModules.h"
#include "KConsole.h"
#include "KController.h"

KDL_CLASS_INTROSPECTION_1	(KModuleLSystem, KMatrixModule)
KDS_MODULE_VALUES		(KModuleLSystem, "LSystem", 1.0f, 1.0f, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModuleLSystem::KModuleLSystem () : KMatrixModule ()
{
    matrix_object = new KMatrixHandle (this);

    createConnectors();

    leaf_mode = false;
    
    ls_display_list = 0;
    depth[0] = depth[1] = 0.0;
    depth[2] = depth[3] = 0.0;
}

// --------------------------------------------------------------------------------------------------------
void KModuleLSystem::displayBranch ( int index, float depth, 
                                        vector<KMatrixModule*> & modules, vector<float> & depths, int mode )
{
    if (depth < 1) return;

    glPushMatrix();

    modules[index]->getMatrixObject()->glMultMatrix();

    if (ls_display_list)
    {
        if (leaf_mode == false || depth == 1) 
        {
            glCallList(ls_display_list);
        }
    }
    else
    {
        vector<KModule*> hierarchy;
        modules[index]->getModulesInHierarchy(hierarchy);
        
        vector<KModule*>::iterator iter = hierarchy.begin();
        while (iter != hierarchy.end())
        {
            if ((*iter)->getClassId() >= KMatrixModule::classId())
            {
                ((KMatrixModule*)*iter)->getMatrixObject()->glMultMatrix();
            }
            iter++;
        }
        if (depth == 1 || leaf_mode == false) 
        {
            getConnectorWithName("matrix out")->getConnectedModule()->display(mode);
        }
    }

    depth = depth - 1; 
    if (depth >= 1)
    {
        for ( index = 0; index < (int)modules.size(); index++)
        {
            displayBranch(index, kMin(depth, depths[index]), modules, depths, mode);
        }
    }

    glPopMatrix();
}

// --------------------------------------------------------------------------------------------------------
void KModuleLSystem::displayTree ( int mode )
{
    glPushMatrix();
    KModule * outModule = ((KConnector*)connectors[4])->getConnectedModule();
    
    if (outModule)
    {
        bool saveFlag = Controller.modules->objects->flags[KDS_OBJECTS_FLAG_DISPLAY_HANDLES];
        Controller.modules->objects->flags[KDS_OBJECTS_FLAG_DISPLAY_HANDLES] = false;
        
        vector<KMatrixModule*>	modules;
        vector<float>	 	depths;

        for (int c = 0; c < 4; c++) // c == matrix 'in' connectors
        {
            KConnectorMatrixOut * matrixConnector = (KConnectorMatrixOut*)(connectors[c+5]);
            KMatrixModule * matrixModule = (KMatrixModule*)matrixConnector->getConnectedModule();
            if (matrixModule)
            {
                modules.push_back(matrixModule);
                depths.push_back (depth[c]);
            }
        }
        
        for (int index = 0; index < (int)modules.size(); index++)
        {
            displayBranch(index, depths[index], modules, depths, mode);
        }
        
	Controller.modules->objects->flags[KDS_OBJECTS_FLAG_DISPLAY_HANDLES] = saveFlag;
    }
    
    glPopMatrix();
}

// --------------------------------------------------------------------------------------------------------
void KModuleLSystem::display ( int mode )
{
    ls_display_list = 0; // paranoid, display list was delete

    if (mode == KDS_APPLICATION_MODE_EDIT_MODULES || leaf_mode == false)
    {
        KMatrixModule::display(mode);
    }
    else if (leaf_mode && mode != KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        glPushMatrix();
        matrix_object->glMultMatrix();
        displayChildModules(mode);
        glPopMatrix();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleLSystem::displayChildModules ( int mode )
{
    if (mode != KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        GLint currentList;
        glGetIntegerv(GL_LIST_INDEX, &currentList);
        if (currentList == 0) // we only generate a list if there is no other list in creation
        {
            ls_display_list = glGenLists(1);
            if (ls_display_list)
            {
                Controller.modules->addDisplayListName(ls_display_list); // 

                glNewList(ls_display_list, leaf_mode ? GL_COMPILE : GL_COMPILE_AND_EXECUTE);
                KModule::displayChildModules(mode);
                glEndList();

                displayTree (mode);

                return;
            }
            else
            {
                KConsole::printError("unable to create display list for l-system module");
            }
        }

        ls_display_list = 0;
        KModule::displayChildModules(mode);
        
        if (!leaf_mode)
        {
            displayTree (mode);
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleLSystem::createConnectors ()
{
    KValueObject * value;

    value = new KBoolValueObject( "leaf mode" );
    values.push_back(value);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KModuleLSystem::setLeafMode);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KModuleLSystem::getLeafMode);

    KConnectorValueInOut * ioConnector;

    NEW_IO_CONNECTOR_TR("1. depth",  1.4f,1.4f, 0.0,0,  0,-45,
                                                    (KObject*)this,KModuleLSystem,setDepth1,getDepth1)
    NEW_IO_CONNECTOR_TR("2. depth",  0.0,1.4f,-1.4f,0, 90,-45,
                                                    (KObject*)this,KModuleLSystem,setDepth2,getDepth2)
    NEW_IO_CONNECTOR_TR("3. depth", -1.4f,1.4f, 0.0,0,  0, 45,
                                                    (KObject*)this,KModuleLSystem,setDepth3,getDepth3)
    NEW_IO_CONNECTOR_TR("4. depth",  0.0,1.4f, 1.4f,0,-90,-45,
                                                    (KObject*)this,KModuleLSystem,setDepth4,getDepth4)
    
    KConnector * connector;
    
    connector = new KConnectorMatrixOut( this, "matrix out" ); 
    connector->translate (0.0, 2.0, 0.0); // top
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix in 1" ); 
    connector->translate (1.5, 0.0, 0.0); // right
    connector->rotate (0.0, 0.0, -90.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix in 2" ); 
    connector->translate (0.0, 0.0, -1.5); // back 
    connector->rotate (270.0, 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix in 3" ); 
    connector->translate (-1.5, 0.0, 0.0); // left
    connector->rotate (0.0, 0.0, 90.0);
    addConnector(connector);

    connector = new KConnectorMatrixOut( this, "matrix in 4" ); 
    connector->translate (0.0, 0.0, 1.5); // front 
    connector->rotate (90.0, 0.0, 0.0);
    addConnector(connector);
    
    connector = new KConnectorMatrixIn( this ); 
    connector->translate (0.0, -1.5, 0.0); // bottom
    connector->rotate (180.0, 0.0, 0.0);
    addConnector(connector);
}

// --------------------------------------------------------------------------------------------------------
static void fillGap ()
{
    glBegin(GL_QUADS);
    glNormal3f( 0.0, -1.0,  0.0); // matrix connector frame
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.5);
    glVertex3f(-1.0,  1.0,  1.5);
    
    glNormal3f( 0.0,  1.0,  0.0);
    glVertex3f(-1.0, -1.0,  1.5);
    glVertex3f( 1.0, -1.0,  1.5);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);

    glNormal3f(-1.0,  0.0,  0.0);
    glVertex3f( 1.0,  1.0,  1.5);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.5);    

    glNormal3f( 1.0,  0.0,  0.0);
    glVertex3f(-1.0, -1.0,  1.5);    
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.5);

    float c = cos(DEG2RAD(45.0));

    glNormal3f(c, 0.0, c); // right/front
    glVertex3f(1.0,   1.0,  1.5);
    glVertex3f(1.0,  -1.0,  1.5);
    glVertex3f(1.5,  -1.0,  1.0);
    glVertex3f(1.5,   1.0,  1.0);
    
    glNormal3f(0.0, c, c); // front/top
    glVertex3f( 1.0,  1.5,  1.0);
    glVertex3f(-1.0,  1.5,  1.0);
    glVertex3f(-1.0,  1.0,  1.5);
    glVertex3f( 1.0,  1.0,  1.5);

    glNormal3f(0.0, -c, c); // front/bottom
    glVertex3f( 1.0, -1.0,  1.5);
    glVertex3f(-1.0, -1.0,  1.5);
    glVertex3f(-1.0, -1.5,  1.0);
    glVertex3f( 1.0, -1.5,  1.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.5, c, 0.5); // right/front/top
    glVertex3f( 1.0,  1.5,  1.0);
    glVertex3f( 1.0,  1.0,  1.5);
    glVertex3f( 1.5,  1.0,  1.0);

    glNormal3f(0.5, -c, 0.5); // right/front/bottom
    glVertex3f( 1.5,  -1.0,  1.0);
    glVertex3f( 1.0,  -1.0,  1.5);
    glVertex3f( 1.0,  -1.5,  1.0);
    glEnd();
}

// --------------------------------------------------------------------------------------------------------
void KModuleLSystem::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    loadId();

    glPushMatrix();
    fillGap(); glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap(); glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap(); glRotatef(90.0, 0.0, 1.0, 0.0);
    fillGap();
    glPopMatrix();
}

