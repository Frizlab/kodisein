/*
 *  KModuleObjectBox.cpp
 *  kodisein
 */

#include "KModuleObjectBox.h"
#include "KModuleObjectFace.h"
#include "KModuleMatrixHub.h"
#include "KConnectorIntValueInOut.h"
#include "KConnector.h"
#include "KBox.h"
#include "KModules.h"
#include "KSelectable.h"
#include "KXMLTools.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 	(KModuleObjectBox, KObjectModule)
KDS_MODULE_VALUES		(KModuleObjectBox, "Box", 0.0, 1.0f, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
KModuleObjectBox::KModuleObjectBox () : KObjectModule ()
{
    matrix_object = new KBox (this);
    
    createConnectors();
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectBox::createConnectors ()
{
    KConnectorIntValueInOut * ioConnector;
    vector<int>    enums;
    vector<string> names;
    
    names.push_back("outside");
    names.push_back("inside");
    enums.push_back(GLU_OUTSIDE);
    enums.push_back(GLU_INSIDE);
    ioConnector = new KConnectorIntValueInOut (this, names, enums, "orientation");
    ioConnector->translate (-1.2f, 0.0, 0.0);
    ioConnector->rotate(0.0, 0.0, 90.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(matrix_object, (KSetIntPtr)&KBox::setOrientation);
    values.back()->setProviderCallback(matrix_object, (KGetIntPtr)&KBox::getOrientation);  
}

// --------------------------------------------------------------------------------------------------------
void KModuleObjectBox::expand ()
{
/*
    KMatrixModule     * matrixModule = new KModuleMatrix();
    KModuleMatrixHub  * bottomHub = new KModuleMatrixHub();
    KModuleMatrixHub  * topHub 	= new KModuleMatrixHub();
    
    KModuleObjectFace * bottom 	= new KModuleObjectFace(*((*((KBox*)matrix_object)->getFaces())[0]));
    KModuleObjectFace * front 	= new KModuleObjectFace(*((*((KBox*)matrix_object)->getFaces())[1]));
    KModuleObjectFace * top 	= new KModuleObjectFace(*((*((KBox*)matrix_object)->getFaces())[2]));
    KModuleObjectFace * back 	= new KModuleObjectFace(*((*((KBox*)matrix_object)->getFaces())[3]));
    KModuleObjectFace * right 	= new KModuleObjectFace(*((*((KBox*)matrix_object)->getFaces())[4]));
    KModuleObjectFace * left 	= new KModuleObjectFace(*((*((KBox*)matrix_object)->getFaces())[5]));

    *((KSeparatedMatrix*)matrixModule->getMatrixObject()) = *((KSeparatedMatrix*)matrix_object);
    
    matrixModule->connectModule(bottomHub);
    bottomHub->connectModule(topHub);
    bottomHub->connectModule(bottom);
    topHub->connectModule(top);
    topHub->connectModule(front);
    topHub->connectModule(back);
    topHub->connectModule(left);
    topHub->connectModule(right);

    KConnector * inConnector = getParentConnector();
    if (inConnector)
    {
        KModule * inModule = inConnector->getConnectedModule();
        inConnector->disconnect();
        inModule->connectModule(matrixModule);
    }
    
    if (hasConnectorOfType(KDS_CONNECTOR_ATTRIBUTE_IN, KDS_USED_CONNECTOR))
    {
        KConnector * inConnector = getConnectorOfType(KDS_CONNECTOR_ATTRIBUTE_IN, KDS_USED_CONNECTOR);
        KModule * inModule = inConnector->getConnectedModule();
        inConnector->disconnect();
        bottom->connectModule(inModule);
        KSelectable * attribModule = inModule->copy();
        front->connectModule((KModule*)attribModule); Controller.modules->addPickable(attribModule);
        attribModule = inModule->copy();
        top->connectModule((KModule*)attribModule); Controller.modules->addPickable(attribModule);
        attribModule = inModule->copy();
        left->connectModule((KModule*)attribModule); Controller.modules->addPickable(attribModule);
        attribModule = inModule->copy();
        right->connectModule((KModule*)attribModule); Controller.modules->addPickable(attribModule);
        attribModule = inModule->copy();
        back->connectModule((KModule*)attribModule); Controller.modules->addPickable(attribModule);
    }
    
    disconnect();

    Controller.modules->addPickable(bottomHub);
    Controller.modules->addPickable(topHub);    
    Controller.modules->addPickable(bottom);
    Controller.modules->addPickable(front);
    Controller.modules->addPickable(top);
    Controller.modules->addPickable(left);
    Controller.modules->addPickable(right);
    Controller.modules->addPickable(back);
    
    delete this;
     */
}

