/*
 *  KConnector.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KConnector.h"
#include "KController.h"
#include "KConsole.h"
#include "KModules.h"
#include "KValueModule.h"
#include "KConnectorValueOut.h"
#include "KTools.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_2 (KConnector, KMatrix, KSelectable )

const int KConnector::type = KDS_CONNECTOR_FLAT;
const int KConnector::connection_type = -1;

#define VALUEMODULE_LINK "ValueOutLink"

// --------------------------------------------------------------------------------------------------------
KConnector::KConnector ( KModule * m, const string & n ) : KMatrix (), KSelectable ()
{
    module = m;
    name   = n;
}

// --------------------------------------------------------------------------------------------------------
void KConnector::setPicked ( bool p )
{
    if (picked != p)
    {
        KPickable::setPicked(p);
        if (p) Controller.modules->select(this);
        module->setPicked(p);
    }
}

// --------------------------------------------------------------------------------------------------------
bool KConnector::isAcceptingConnections () const
{
    return (isUnlimited() || connected_connectors.empty());
}

// --------------------------------------------------------------------------------------------------------
void KConnector::connectWithConnector ( KConnector * c )
{
    if (isUnlimited() == false && connected_connectors.empty() == false)
    {
        KConnector * oldConnector = connected_connectors[0];
        oldConnector->removeConnectedConnector(this);
        removeConnectedConnector(oldConnector);
        oldConnector->getModule()->connectModule(c->getModule(), oldConnector);
    }
    
    c->addConnectedConnector(this);
    addConnectedConnector(c);

    if (isChildConnector() && c->isParentConnector()) 
    {
        c->getModule()->updateMatrix();
    }
}

// --------------------------------------------------------------------------------------------------------
KConnector * KConnector::getConnectedChildConnector () const
{
    KConnector * connector = getConnectedConnector();
    if (connector && connector->isParentConnector()) return connector;
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KConnector * KConnector::getConnectedConnector () const
{
    if (connected_connectors.empty()) return NULL;
    if (isUnlimited()) 
    {
        vector<KConnector*>::const_iterator iter = connected_connectors.begin();
        while (iter != connected_connectors.end())
        {	
            if ((*iter)->isParentConnector()) return (*iter);
            iter++;
        }
    }
    return connected_connectors[0];
}

// --------------------------------------------------------------------------------------------------------
KModule * KConnector::getConnectedModule () const
{
    if (connected_connectors.empty()) return NULL;
    return connected_connectors[0]->getModule();
}

// --------------------------------------------------------------------------------------------------------
vector<KModule*> KConnector::getConnectedModules () const
{
    vector<KModule*> connectedModules;
    vector<KConnector*>::const_iterator iter = connected_connectors.begin();
    while (iter != connected_connectors.end())
    {
        connectedModules.push_back((*iter)->getModule());
        iter++;
    }
    
    return connectedModules;
}

// --------------------------------------------------------------------------------------------------------
void KConnector::disconnect ( )
{
    vector<KConnector*>::iterator iter = connected_connectors.begin();
    while (iter != connected_connectors.end())
    {
        KConnector * connectedConnector = (*iter);
        connectedConnector->removeConnectedConnector(this);
        iter++;
    }
    
    connected_connectors.clear();
}

// --------------------------------------------------------------------------------------------------------
void KConnector::addConnectedConnector ( KConnector * c )
{
    vector<KConnector*>::iterator result = find(connected_connectors.begin(),connected_connectors.end(),c);
    if (result == connected_connectors.end())
    {
        connected_connectors.push_back(c);
    }
}

// --------------------------------------------------------------------------------------------------------
void KConnector::removeConnectedConnector ( KConnector * c )
{
    vector<KConnector*>::iterator result = find(connected_connectors.begin(),connected_connectors.end(),c);
    if (result != connected_connectors.end())
    {
        connected_connectors.erase(result);
    }
}

// --------------------------------------------------------------------------------------------------------
void KConnector::render ()
{
    glLoadName(module->getId());
    glBegin(GL_QUADS);
    RECTANGLE_ZX(-1.0,  1.0, -1.0,  1.0, 0.0);
    glEnd();
}

// --------------------------------------------------------------------------------------------------------
void KConnector::display ()
{
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);
    
    if (picked || selected && module->isPicked())
    {
        module->getModuleColor().glColor();
    }
    else if (selected)
    {
        glColor3f(1.0, 1.0, 1.0);
    }
    
    glPushMatrix();
    loadId();
    glMultMatrix();
    render();
    glPopMatrix();
    
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
string KConnector::getDisplayName () const
{
    return "[" + module->getName() + "] " + name;
}

// --------------------------------------------------------------------------------------------------------
string KConnector::getXMLAttributes ( bool targetIsPasteBuffer ) const
{
    return kStringPrintf("name='%s'", name.c_str());
}

// --------------------------------------------------------------------------------------------------------
void KConnector::setXML ( string & xml )
{
    string name, attributes;
    
    string openTag = kXMLParseNamedOpenTag(xml, "Connector", &attributes);
    setXMLAttributes(attributes);
    
    if (openTag[openTag.size()-2] == '/') return;
    
    kXMLParseOpenTag(xml, name, &attributes);
    
    if (name == VALUEMODULE_LINK)
    {
        long connectorId = atol(kXMLReadNamedAttribute(attributes, "id").c_str());
        Controller.modules->addConnectorLink(this, connectorId);
    }
    else
    {
        xml.insert(0, kXMLOpenTag(name));
        KModule * newModule = Controller.modules->parseXMLForModule(xml);
        if (newModule == NULL) 
        {
            KConsole::printError(kStringPrintf
            ("invalid XML:\nunable to parse module\n'%s'\nfor connector\n'%s [%s]'", 
                                        name.c_str(), module->getName().c_str(), getName().c_str()));
            kXMLParseToTagsInVector(xml, vector<string>(1, "/"+name));
            kXMLParseToTagsInVector(xml, vector<string>(1, "/Connector"));            
            return;
        }
        module->connectModule(newModule, this);
    }
    
    if (kXMLParseNamedCloseTag(xml, "Connector") == false)
    {
        KConsole::printError(kStringPrintf("invalid XML:\nmissing close tag for connector\n'%s [%s]'",
                                                module->getName().c_str(), getName().c_str()));
    }
}

// --------------------------------------------------------------------------------------------------------
string KConnector::getXML ( int depth, bool targetIsPasteBuffer ) const
{
    string xml;
    
    vector<KConnector*>::const_iterator connectorIter = connected_connectors.begin();
    while (connectorIter != connected_connectors.end())
    {
        KModule * connectedModule = (*connectorIter)->getModule();
        
        if ((*connectorIter)->getClassId() >= KConnectorValueOut::classId() &&
            connectedModule->getParentModule() != module && 
            connectedModule->getClassId() >= KValueModule::classId())
        {
            xml += kXMLOpenTag("Connector", getXMLAttributes(targetIsPasteBuffer), depth);
            xml += kXMLTag(VALUEMODULE_LINK, kStringPrintf("id='%ld'", 
                            ((KConnectorValueOut*)*connectorIter)->getObjectId()), depth+KDL_XML_INDENT);
            xml += kXMLCloseTag("Connector", depth);
            return xml;
        }
        else if ((targetIsPasteBuffer == false || connectedModule->isSelected()) &&
                  (connectedModule->getParentModule() == module))
        {
            xml += kXMLOpenTag("Connector", getXMLAttributes(targetIsPasteBuffer), depth);
            xml += connectedModule->getXML(depth+KDL_XML_INDENT, targetIsPasteBuffer);
            xml += kXMLCloseTag("Connector", depth);
            return xml;
        }
        connectorIter++;
    }
    
    return xml;
}