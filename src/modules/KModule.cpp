/*
 *  KModule.cpp
 *  kodisein
 */

#include "KModule.h"
#include "KEventHandler.h"
#include "KController.h"
#include "KModules.h"
#include "KObjects.h"
#include "KConsole.h"
#include "KValueModule.h"
#include "KModuleLabel.h"
#include "KAttributeModule.h"
#include "KConnectorValueInOut.h"
#include "KTextField.h"
#include "KXMLTools.h"

#include <algorithm>

KDL_CLASS_INTROSPECTION_2 (KModule, KMatrix, KSelectable)
KDS_MODULE_VALUES	  (KModule, "KModule", 0.5f, 0.5f, 0.5f, 0.6f)

// --------------------------------------------------------------------------------------------------------
KModule::KModule () : KMatrix (), KSelectable ()
{
    display_list = 0;
}

// --------------------------------------------------------------------------------------------------------
KModule::~KModule ()
{
    disconnect ();
    PickableVector::iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        delete (*iter);
        iter++;
    }
    connectors.clear();
        
    deleteDisplayList();
}

// --------------------------------------------------------------------------------------------------------
bool 
KModule::connectModule ( KModule * otherModule, KConnector * ownConnector, KConnector * otherConnector )
{
    if (ownConnector == NULL)
    {
        PickableVector::iterator iter = connectors.begin();
        
         while (iter != connectors.end())
         {
            ownConnector = (KConnector*)*iter;
            if (ownConnector->isChildConnector() && ownConnector->isAcceptingConnections() &&										otherModule->isAcceptingConnection(ownConnector))
            {
                return connectModule(otherModule, ownConnector, otherConnector);
            }
            iter++;
         }
    }
    else 
    {
        if (otherConnector == NULL) 
        {
            otherConnector = otherModule->getAcceptingConnector(ownConnector);
            if (otherConnector)
            {
                return connectModule(otherModule, ownConnector, otherConnector); // call virtual methods again
            }
        }

        if (otherConnector)
        {
            if (ownConnector->isChildConnector())
            {
                ownConnector->connectWithConnector(otherConnector);
            }
            else
            {
                otherConnector->connectWithConnector(ownConnector);
            }
            return true;
        }
        else
        {
            // just in case, that selected ownConnector is of wrong connection type 
            // -> try to connect with other ownConnector
            return connectModule(otherModule);
        }
    }
    
    return false;
}

// --------------------------------------------------------------------------------------------------------
void KModule::disconnectConnector ( KConnector * connector )
{
    if (connector == NULL) return;
    connector->disconnect();
}

// --------------------------------------------------------------------------------------------------------
void KModule::disconnect ()
{
    KConnector * parentModuleConnector = NULL;
    KConnector * childModuleConnector  = NULL;

    // try to keep module chains intact
    // check for connected parent connector and a connected child connector with matching types
    KConnector * parentConnector = getParentConnector();
    if (parentConnector && parentConnector->isConnected())
    {
        KConnector * childConnector = getConnectorOfType(parentConnector->getConnectionType(), KDS_USED_CONNECTOR);
        if (childConnector)
        {
            parentModuleConnector = parentConnector->getConnectedConnector();
            childModuleConnector  = childConnector->getConnectedConnector();
        }
    }
    
    PickableVector::iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        disconnectConnector((KConnector*)*iter);
        iter++;
    }
    
    // close the module chain again
    if (parentModuleConnector && childModuleConnector)
    {
        parentModuleConnector->connectWithConnector(childModuleConnector);
    }
}

// --------------------------------------------------------------------------------------------------------
bool KModule::isAcceptingConnection ( KConnector * c ) const
{
    return (hasConnectorOfType(c->getConnectionType(), KDS_FREE_CONNECTOR));
}

// --------------------------------------------------------------------------------------------------------
KConnector * KModule::getAcceptingConnector ( KConnector * c ) const
{
    return (getConnectorOfType(c->getConnectionType(), KDS_FREE_CONNECTOR));
}

// --------------------------------------------------------------------------------------------------------
void KModule::pushAttributes ( int mode ) 
{
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);

    if (mode == KDS_APPLICATION_MODE_ANIMATION) // || mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        vector<KModule*> attributeModules = getChildModulesOfType(KDS_CONNECTOR_ATTRIBUTE_IN);
        vector<KModule*>::iterator iter = attributeModules.begin();
        while (iter != attributeModules.end())
        {
            ((KAttributeModule*)*iter)->apply();
            iter++;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KModule::displayConnectors ( int mode )
{
    PickableVector::iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        ((KConnector*)*iter)->display();
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModule::preDisplay ( int mode ) 
{
    glPushMatrix();
    
    pushAttributes (mode);

    if (mode == KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        glMultMatrixf(matrix);
        loadId();
        
        if (KEventHandler::flags[KDL_DISPLAY_MODE_WIREFRAME] == true)
        {
            glPolygonMode(GL_FRONT_AND_BACK, (picked || selected) ? GL_FILL : GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if (picked) glColor3f (1.0, 1.0, 1.0); else getModuleColor().glColor();
        
        bool fastDisplay = Controller.getFastDisplay();
        
        // DL----------------
        if (display_list)
        {
            if (fastDisplay == false) 
            {
                deleteDisplayList();
            }
            else
            {
                glCallList(display_list); loadId();
                return;
            }
        }
        else if (fastDisplay)
        {
            if (selected && !picked) glColor3f (0.6f, 0.6f, 0.6f);
            display_list = glGenLists(1);
            if (display_list)
            {
                glNewList(display_list, GL_COMPILE_AND_EXECUTE);
            }
        }
        // DL--------------

        displayConnectors(mode);
        
        if ((picked || selected) && fastDisplay == false)
        {
            glPushAttrib( GL_POLYGON_BIT | GL_LINE_BIT | GL_LIGHTING_BIT );
            glLineWidth(2);
            glDisable(GL_LIGHTING);
            
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glEnable(GL_POLYGON_OFFSET_LINE);
            glPolygonOffset(0.0, -3.0);
            if (picked) 
            {
                KColor color = getModuleColor(); color.setAlpha(1.0); color.glColor();
            }
            else glColor3f (0.0, 0.0, 0.0);
            displayConnectors(mode);
            glPopAttrib();
        }

        // DL-----------
        if (display_list)
        {
            glEndList();
        }
        // DL-----------

        loadId();
    }
}

// --------------------------------------------------------------------------------------------------------
void KModule::display ( int mode )
{    
    preDisplay (mode);
    postDisplay(mode);
}

// --------------------------------------------------------------------------------------------------------
void KModule::postDisplay ( int mode )
{
    popAttributes(mode);
    displayChildModules(mode);
    glPopMatrix();
}

// --------------------------------------------------------------------------------------------------------
void KModule::popAttributes ( int mode )
{
    if (mode == KDS_APPLICATION_MODE_ANIMATION) // || mode == KDS_APPLICATION_MODE_EDIT_OBJECTS)
    {
        vector<KModule*> attributeModules = getChildModulesOfType(KDS_CONNECTOR_ATTRIBUTE_IN);
        vector<KModule*>::reverse_iterator iter = attributeModules.rbegin();
        while (iter != attributeModules.rend())
        {
            ((KAttributeModule*)*iter)->postApply();
            iter++;
        }
    }
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
void KModule::displayChildModules ( int mode )
{
    if (mode != KDS_APPLICATION_MODE_EDIT_MODULES)
    {
        PickableVector::iterator iter = connectors.begin();
        while (iter != connectors.end())
        {
            if (((KConnector*)*iter)->getType() == KDS_CONNECTOR_MATRIX_OUT && 
                ((KConnector*)*iter)->getConnectedModule())
            {
                ((KConnector*)*iter)->getConnectedModule()->display(mode);
            }
            iter++;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
bool KModule::isCutCopyPasteable () const
{
    KModule * parentModule = getParentModule();
    return (parentModule == NULL || parentModule->isSelected() == false);
}

// --------------------------------------------------------------------------------------------------------
void KModule::setPicked ( bool p )
{
    if (picked != p)
    {
        KPickable::setPicked(p);
        if (p) 
        {
            Controller.modules->select(this);
            Controller.inspector->setInspectedModule(this);        
        }
        else 	    
        {
            Controller.inspector->clear();
        }
    }

    deleteDisplayList();
}

// --------------------------------------------------------------------------------------------------------
void KModule::setSelected ( bool b )
{
    if (b != selected)
    {
        KSelectable::setSelected(b);
    }

    deleteDisplayList();
}

// --------------------------------------------------------------------------------------------------------
KConnector * KModule::getConnectorWithName ( const string & name ) const
{
    PickableVector::const_iterator iter = connectors.begin();
    while (iter != connectors.end())
    {    
        if (((KConnector*)*iter)->getName() == name)
        {
            return ((KConnector*)*iter);
        }
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KConnector * KModule::getConnectorForModule ( KModule * mod ) const
{
    if (mod == NULL) return NULL;
    PickableVector::const_iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        KConnector * connector = (KConnector*)*iter;
        vector<KModule*> connectedModules = connector->getConnectedModules();
        vector<KModule*>::iterator result;
        result = find(connectedModules.begin(), connectedModules.end(), mod);
        if (result != connectedModules.end())
        {
            return connector;
        }
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KConnector * KModule::getParentConnector () const
{
    PickableVector::const_iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        if (((KConnector*)*iter)->isParentConnector())
        {
            return (KConnector*)*iter;
        }
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KConnector * KModule::getConnectorOfType ( int type, int mode ) const
{
    PickableVector::const_iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        KConnector * connector = (KConnector*)*iter;
        if (connector->getType() == type)
        {
            if ((mode == KDS_ANY_CONNECTOR) ||
                (mode == KDS_USED_CONNECTOR && connector->isConnected()) ||
                (mode == KDS_FREE_CONNECTOR && connector->isUnconnected()))
            {
                return connector;
            }
        }
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
vector<KConnector*> KModule::getConnectorsOfType ( int type, int mode ) const
{	
    vector<KConnector*> typedConnectors;
    PickableVector::const_iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        KConnector * connector = (KConnector*)*iter;
        if (connector->getType() == type)
        {
            if ((mode == KDS_ANY_CONNECTOR) ||
                (mode == KDS_USED_CONNECTOR && connector->isConnected()) ||
                (mode == KDS_FREE_CONNECTOR && connector->isUnconnected()))
            {
                typedConnectors.push_back(connector);
            }
        }
        iter++;
    }
    return typedConnectors;
}

// --------------------------------------------------------------------------------------------------------
bool KModule::hasConnectorOfType ( int type, int mode ) const
{
    return (getConnectorOfType (type, mode) != NULL);
}

// --------------------------------------------------------------------------------------------------------
KConnector * KModule::getPickedConnector () const
{
    PickableVector::const_iterator iter = connectors.begin();
    
    while (iter != connectors.end())
    {
        if ((*iter)->isPicked()) return ((KConnector*)*iter);
        iter++;
    }
    
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KModule::addConnector ( KConnector * connector )
{
    connectors.push_back((KPickable*)connector);
}

// --------------------------------------------------------------------------------------------------------
void KModule::setPosition ( const KVector & p ) 
{
    KMatrix::setPosition(p);
    updateChildren();
}

// --------------------------------------------------------------------------------------------------------
void KModule::rotate ( const GLfloat x, const GLfloat y, const GLfloat z )		
{
    KMatrix::rotate(x, y, z);
    updateChildren();
}

// --------------------------------------------------------------------------------------------------------
void KModule::deleteDisplayList ()
{
    if (display_list) glDeleteLists(display_list, 1);
    display_list = 0;
}

// --------------------------------------------------------------------------------------------------------
void KModule::getLeafModules ( vector<KModule*> & leaves ) const
{
    vector<KModule*> childModules = getChildModulesOfType(getParentConnector()->getConnectionType());
    if (childModules.empty())
    {
        leaves.push_back((KModule*)this);
        return;
    }
    
    vector<KModule*>::iterator iter = childModules.begin();
    while (iter != childModules.end())
    {
        (*iter)->getLeafModules(leaves);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
vector<KModule*> KModule::getChildModulesOfType ( int type ) const
{
    vector<KModule*>childModules;
    PickableVector::const_iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        if (((KConnector*)*iter)->isChildConnector() && ((KConnector*)*iter)->isConnected() &&
            ((KConnector*)*iter)->getConnectedChildConnector() != NULL && // neutral value modules
            (type < 0 || ((KConnector*)*iter)->getType() == type))
        {
            childModules.push_back(((KConnector*)*iter)->getConnectedModule());
        }
        iter++;
    }
    return childModules;
}

// --------------------------------------------------------------------------------------------------------
vector<KModule*> KModule::getChildModules () const
{
    return getChildModulesOfType( -1 );
}

// --------------------------------------------------------------------------------------------------------
void KModule::getModulesInHierarchy ( vector<KModule*> & modules, bool activeOnly, const KClassId & cid ) const
{
    PickableVector::const_iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        KModule * connectedModule = ((KConnector*)*iter)->getConnectedModule();
        if (connectedModule && connectedModule->getParentModule() == this)
        {
            if (connectedModule->getClassId() >= cid)
            {
                modules.push_back(connectedModule);
            }
            if (activeOnly == false || 
                (connectedModule->getClassId() >= KModuleLabel::classId()) == false || 
                ((KModuleLabel*)connectedModule)->getActive())          
            {
                connectedModule->getModulesInHierarchy(modules, activeOnly, cid);
            }
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
vector<KModule*> KModule::getParentModules () const
{
    vector<KModule*> parentModules;
    KModule * parentModule = getParentModule();
    if (parentModule)
    {
        parentModules = parentModule->getParentModules();
        parentModules.push_back(parentModule);
    }
    return parentModules;
}

// --------------------------------------------------------------------------------------------------------
KModule * KModule::getParentModule () const
{
    KConnector * parentConnector = getParentConnector();
    if (parentConnector) return parentConnector->getConnectedModule();
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KModule * KModule::getRootModule () const
{
    KModule * parent = getParentModule();
    if (parent == NULL) return (KModule*)this;
    else return parent->getRootModule();
}

// --------------------------------------------------------------------------------------------------------
void KModule::updateChildren ()
{
    PickableVector::iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        KModule * connectedModule = ((KConnector*)*iter)->getConnectedModule();
        if (connectedModule && (connectedModule->getParentModule() == this))
        {
            connectedModule->updateMatrix();
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModule::updateMatrix ()
{
    KConnector * parentConnector = getParentConnector();
    if (parentConnector && parentConnector->isConnected())
    {
        KModule * parent = parentConnector->getConnectedModule();
        KMatrix::reset();
        // transform according to parent module
        KMatrix::transform (*parent); 
        // transform according to parent's connector
        KMatrix::transform (*(parentConnector->getConnectedConnector()));
        KMatrix::rotate	   (0.0, 180.0, 180.0);
        // translate to connector's origin
        KMatrix::transform (parentConnector->getInverse());
    }
    
    updateChildren();
}

// --------------------------------------------------------------------------------------------------------
string KModule::getPasteBufferString () const
{
    return getXML(0, true);
}

// --------------------------------------------------------------------------------------------------------
void KModule::initInspector ( KModuleInspector * inspector )
{
    string titleString = getDisplayName();
    if (connectors.size() > 1)
    {
        PickableVector::const_iterator iter = connectors.begin();
        while (iter != connectors.end())
        {
            bool append = false;
            KConnector * connector = (KConnector*)*iter;
            if (connector->isSelected() && inspector->isMinimized() || connector->isPicked())
            {
                if (append) titleString += ",";
                titleString += " " + connector->getName();
                append = true;
            }
            iter++;
        }
    }
    inspector->setTitle(titleString);

    // description field
    KWidgetArray * valueWidget = new KWidgetArray ();
    valueWidget->addChild(new KLabel("description"));
    
    KTextField * descriptionField = new KTextField ();
    descriptionField->setTextCols(25);
    descriptionField->addReceiverCallback(this, (KSetStringPtr)&KModule::setDescription );
    descriptionField->KWidget::flags[KDL_WIDGET_FLAG_FILL_X] = true;
    descriptionField->KWidget::flags[KDL_TEXTFIELD_FLAG_NOTIFY_ON_UNPICK] = true;
    // trying to see complete text, so setting it here instead of in constructor (fix later: setTextCols)
    descriptionField->setText(getDescription());
    inspector->addPickable(descriptionField);
    valueWidget->addChild(descriptionField);

    inspector->addValueWidget(valueWidget);
    
    // values
    vector<KValueObject*>::const_iterator valueIter = values.begin();
    while(valueIter != values.end())
    {	
        (*valueIter)->addToWidget(inspector->getValuesWidget());
        valueIter++;
    }
    
    inspector->layout();
}

// --------------------------------------------------------------------------------------------------------
void KModule::setXMLValues ( string & xml )
{
    kXMLParseValue(xml, "description", KDL_XML_VALUE_STRING, &description, false);

    vector<KValueObject*>::iterator iter = values.begin();
    while (iter != values.end())
    {
        (*iter)->setXMLValues(xml);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
string KModule::getXMLValues ( int depth ) const
{
    string xml;
    if (!description.empty()) 
    {
        xml += kXMLValue("description", KDL_XML_VALUE_STRING, &description, depth);
    }
    vector<KValueObject*>::const_iterator iter = values.begin();
    while (iter != values.end())
    {
        xml += (*iter)->getXMLValues(depth);
        iter++;
    }
    return xml;
}

// --------------------------------------------------------------------------------------------------------
void KModule::setXMLAttributes ( const string & attributes )
{
    if (attributes == "") return;
    
    string xPosString = kXMLReadNamedAttribute(attributes, "x");
    string yPosString = kXMLReadNamedAttribute(attributes, "y");
    string zPosString = kXMLReadNamedAttribute(attributes, "z");
    
    setPosition(KVector(atof(xPosString.c_str()), atof(yPosString.c_str()), atof(zPosString.c_str())));
}

// --------------------------------------------------------------------------------------------------------
string KModule::getXMLAttributes () const
{
    if (isRootModule())
    {
        return kStringPrintf("x='%g' y='%g' z='%g'", matrix[TX], matrix[TY], matrix[TZ]);
    }
    return "";
}

// --------------------------------------------------------------------------------------------------------
void KModule::setXML ( string & xml )
{
    vector<string> tags;
    string moduleEndTag("/");
    string connectorTag("Connector");
    moduleEndTag += getName();
    tags.push_back(connectorTag);
    tags.push_back(moduleEndTag);
    string values = kXMLParseToTagsInVector(xml, tags);
    setXMLValues(values);
    
    while (xml.substr(1, connectorTag.size()) == connectorTag)
    {
        string attributes;
        kXMLReadNamedOpenTag(xml, "Connector", &attributes);
    
        string name = kXMLReadNamedAttribute(attributes, "name");
        KConnector * connector = getConnectorWithName(name);
        if (connector)
        {
            connector->setXML(xml);
        }
        else
        {
            KConsole::printError(kStringPrintf("invalid XML:\nwrong connector name\n'%s [%s]'",
                                                    getName().c_str(), name.c_str()));
            kXMLParseToTagsInVector(xml, vector<string>(1, "/Connector"));
        }
        
        values = kXMLParseToTagsInVector(xml, tags);

        if (values.find_first_not_of(" \t\n") != string::npos)
        {
            KConsole::printError(kStringPrintf("invalid XML:\nunable to interprete data in xml for module\n'%s'\n%s", getName().c_str(), values.c_str()));
        }
    }
    if (kXMLParseNamedCloseTag(xml, getName()) == false)
    {
        KConsole::printError(kStringPrintf("invalid XML:\nmissing close tag for module\n'%s'", 
                                                    getName().c_str()));
    }
}

// --------------------------------------------------------------------------------------------------------
string KModule::getXML ( int depth, bool selectedChildrenOnly ) const
{
    string xml;
    
    xml += kXMLOpenTag(getName(), getXMLAttributes(), depth);
    xml += getXMLValues(depth+KDL_XML_INDENT);
    PickableVector::const_iterator iter = connectors.begin();
    while (iter != connectors.end())
    {
        if (((KConnector*)*iter)->isChildConnector())
        {
            xml += ((KConnector*)*iter)->getXML(depth+KDL_XML_INDENT, selectedChildrenOnly);
        }
        iter++;
    }

    xml += kXMLCloseTag(getName(), depth);
    return xml;
}
