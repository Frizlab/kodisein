/*
 *  KGlobalModulator.cpp
 *  kodisein
 */

#include "KGlobalModulator.h"
#include "KController.h"
#include "KPreferences.h"
#include "KKeyHandler.h"
#include "KController.h"
#include "KTextureSets.h"
#include "KConsole.h"
#include "KModules.h"
#include "KOrthographicProjection.h"
#include "KAttributeModule.h"
#include "KConnectorModulatorOut.h"
#include "KConnectorValueInOut.h"
#include "KConnectorValueOut.h"
#include "KConnectorIntValueInOut.h"
#include "KConnectorAttributeIn.h"
#include "KFileNameValueObject.h"
#include "KTextField.h"
#include "KModuleTrigger.h"
#include "KLabel.h"
#include "KKey.h"

KDL_CLASS_INTROSPECTION_1 	(KGlobalModulator, KModulator)
KDS_MODULE_VALUES		(KGlobalModulator, "GlobalModulator", 1.0f, 0.5f, 0.0, 0.6f)

// --------------------------------------------------------------------------------------------------------
KGlobalModulator::KGlobalModulator () : KModulator (false)
{
    mouse_x = 0.0;
    mouse_y = 0.0;
    clear_frame = true;
    mouse_modulation = true;
    setActivationKey(Controller.preferences->getGlobalActivationKey());
    createConnectors();
    setDescription("global modulator");
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::activate ()
{
    vector<KModulator*>::iterator iter = modulators.begin();
    while (iter != modulators.end()) // add deactivated modulators to key handlers
    {
        if ((*iter)->activated == false)
        {
            (*iter)->activate();
        }
        iter++;
    }
    activated = true;
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::deactivate ()
{
    vector<KModulator*>::iterator iter = modulators.begin();
    while (iter != modulators.end()) // deactivate all modulators
    {
        (*iter)->deactivate();
        iter++;
    }
    activated = false;
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::stopModulation ()
{
    vector<KModulator*>::iterator iter = modulators.begin();
    while (iter != modulators.end())
    {
        (*iter)->stop(); 
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::resetModulation ()
{
    vector<KModulator*>::iterator iter = modulators.begin();
    while (iter != modulators.end())
    {
        (*iter)->stopPlaying(); 
        (*iter)->reset();
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
KModulator * KGlobalModulator::getSelectedModulator ()
{
    vector<KModulator*>::iterator iter = modulators.begin();
    while (iter != modulators.end())
    {
        if ((*iter)->isSelected()) return (*iter);
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
bool activation_sort ( KModule * a, KModule * b )
{
    return (((KActivationValueModule*)a)->getActivationKey() < 
            ((KActivationValueModule*)b)->getActivationKey());
}
 
// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::addModulator ( KModulator * modulator )
{
    if (modulator != this) 
    {
        if (modulator->getActivationKey() == "")
        {
            int key;
            for (key = 1; key < 13; key++)
            {
                vector<KModulator*>::iterator iter = modulators.begin();
                while (iter != modulators.end())
                {
                    if ((*iter)->getActivationKey() == kStringPrintf("F%d", key)) break;
                    iter++;
                }
                if (iter == modulators.end()) break;
            }
            modulator->setActivationKey(kStringPrintf("F%d", key));
        }
        modulators.push_back(modulator);
	sort(modulators.begin(), modulators.end(), activation_sort);
    }
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::removeModulator ( KModulator * modulator )
{
    vector<KModulator*>::iterator result = find(modulators.begin(), modulators.end(), modulator);
    if (result != modulators.end()) modulators.erase(result);
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::updateModulatorValues ()
{
    // update and propagate values of all modulators
    vector<KModulator*>::iterator iter = modulators.begin(); 
    while (iter != modulators.end())
    {
        (*iter)->updateValue();
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::setMouseValues ( float x, float y )
{
    mouse_x = x; mouse_y = y;

    if (mouse_modulation)
    {
        // iterate through connected value out connectors and propagate values to the modules
        vector<KConnector*> valueOutConnectors;
        valueOutConnectors = getConnectorsOfType(KDS_CONNECTOR_VALUE_OUT, KDS_USED_CONNECTOR);
        vector<KConnector*>::iterator iter = valueOutConnectors.begin();
        while (iter != valueOutConnectors.end())
        {
            // iterate through connected modules and apply modulation or continue propagating
            vector<KConnector*> connectedConnectors = (*iter)->getConnectedConnectors();
            vector<KConnector*>::iterator conIter = connectedConnectors.begin();
            while (conIter != connectedConnectors.end())
            {
                // found value in connector -> continue propagating
                if ((*iter)->getName() == "value out mouse x")
                {
                    ((KConnectorValueIn*)*conIter)->setValue(mouse_x);
                }
                else
                {
                    ((KConnectorValueIn*)*conIter)->setValue(mouse_y);
                }
                conIter++;
            }
            iter++;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::displayStatus ( bool text )
{
    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    KOrthographicProjection projection; 
    projection.initProjection();
    
    glLineWidth(5);
    glLineStipple(1, 0x5555);
    
    int yoffset = -Controller.getScreenSize().h+1;
    int xoffset = 0;
    int size;
    int border  = 3;

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(0, yoffset); glVertex2i(Controller.getScreenSize().w, yoffset);
    glEnd();
    
    // ............................................................ display global modulator status text
    if (text)
    {
        glColor3f(1.0, 1.0, 1.0);
        string statusString;
    
        if (activated) statusString += "[" + activation_key + " " + (mouse_modulation ? "m" : " ") + "] ";
        else           statusString += " " + activation_key + " " + (mouse_modulation ? "m" : " ") + "  ";

        kDisplayString (statusString, KPosition(xoffset, yoffset+4), false);

        size = statusString.size()*8;
    }
    else
    {
        size = 56; // 7*8 '[F1 m] '
    }

    // ............................................................ display global modulator status line
    if (activated) 
    {
        glColor3f(1.0f, 0.0, 0.0);
        glDisable(GL_LINE_STIPPLE);
    }
    else 
    {	
        glColor3f(0.1f, 0.1f, 0.1f);
        glEnable(GL_LINE_STIPPLE);
    }
    
    glBegin(GL_LINES);
    glVertex2i(xoffset, yoffset);
    glVertex2i(xoffset+size, yoffset);
    glEnd();
    
    if (mouse_modulation) glColor3f(0.0, 0.0, 1.0f);
    else  glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2i(xoffset+border, yoffset);
    glVertex2i(xoffset+border+(GLint)((size/2-2*border)*mouse_x), yoffset);
    glVertex2i(xoffset+border+size/2, yoffset);
    glVertex2i(xoffset+border+size/2 + (GLint)((size/2-2*border)*mouse_y), yoffset);
    glEnd();

    xoffset += size;

    size = 48; // 6*8 '[>Fx] '

    vector<KModulator*>::iterator iter = modulators.begin();
    while (iter != modulators.end())
    {        
        // ............................................................ display the modulator status text
        if (text)
        {
            glColor3f(1.0, 1.0, 1.0);
            string statusString;
            if ((*iter)->activated) 		statusString += "[";
            else		    		statusString += " ";
            
            if ((*iter)->playing)
            {
                if ((*iter)->mouse_binding)	statusString += (((*iter)->mouse_binding == 1) ? "x" : "y");
                else 				statusString += ">";
            }
            else
            {
                if ((*iter)->mouse_binding)	statusString += "@";
                else				statusString += "#";
            }
    
            statusString += (*iter)->activation_key;
            
            if ((*iter)->activated)		statusString += "] ";
            else				statusString += "  ";
        
            kDisplayString (statusString, KPosition(xoffset,yoffset+4), false);
                            
            size = statusString.size()*8;
        }
                
        // ............................................................ display the modulator value lines

        if ((*iter)->activated) glDisable(GL_LINE_STIPPLE);
        else glEnable(GL_LINE_STIPPLE);
        
        if ((*iter)->playing) glColor3f(1.0f, 0.0, 0.0);
        else  glColor3f(0.0, 0.2f, 0.0);
        glBegin(GL_LINES);
        glVertex2i(xoffset, yoffset);
        glVertex2i(xoffset+size, yoffset);
        glEnd();
        
        if ((*iter)->mouse_binding) glColor3f(0.0, 0.0, 1.0f);
        else glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex2i(xoffset+border, yoffset);
        glVertex2i(xoffset+border+(GLint)((size-2*border)*(*iter)->value), yoffset);
        glEnd();
        
        xoffset += size;

        iter++;
    }    
    
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::initScene ()
{
    KAttributeModule * backgroundModule;
    backgroundModule = (KAttributeModule*)getConnectorWithName("background")->getConnectedModule();
    if (backgroundModule) 
    {
        backgroundModule->apply();
    }
    else
    {
        glColor3f(0.0, 0.0, 0.0);
    }

    if (clear_frame)
    {        
        GLfloat clearColor[4];
        glGetFloatv(GL_CURRENT_COLOR, clearColor);
        glClearColor(clearColor[R], clearColor[G], clearColor[B], clearColor[A]);
        glClear(GL_COLOR_BUFFER_BIT);
        GLboolean texture;
        glGetBooleanv(GL_TEXTURE_2D, &texture);
        
        if (texture)
        {
            KOrthographicProjection projection;
            projection.initProjection();
            glPushAttrib(GL_LIGHTING_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT);
            glDisable(GL_LIGHTING);
            glDepthFunc(GL_ALWAYS);
            glBegin(GL_QUADS);
                KSize screenSize = projection.getViewportSize();
                glTexCoord2f(0.0, 1.0); glVertex2i (0, -screenSize.h);
                glTexCoord2f(1.0, 1.0); glVertex2i (screenSize.w, -screenSize.h);
                glTexCoord2f(1.0, 0.0); glVertex2i (screenSize.w, 0);
                glTexCoord2f(0.0, 0.0); glVertex2i (0, 0);                
            glEnd();
            glPopAttrib();
        }
    }
    else
    {
        glPushAttrib(GL_PIXEL_MODE_BIT);
        glReadBuffer(GL_FRONT);
        glAccum(GL_LOAD, 0.5);
        glDrawBuffer(GL_BACK);
        glAccum(GL_RETURN, 1.0);
        glPopAttrib();
    }

    // always clear the depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);
        
    if (backgroundModule) 
    {
        backgroundModule->postApply();
    }

    glColor3f(1.0, 1.0, 1.0);
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::createConnectors ()
{
    KConnector * connector;

    float ir = sqrt(3);

    connector = new KConnectorValueOut( this, "value out mouse x" );
    connector->translate (0.5f, 0.9f, -1.5f); 
    connector->rotate(-RAD2DEG(0.5/asin((ir-1)*(ir-1)+0.25)), 0.0, 0.0);
    addConnector(connector);

    connector = new KConnectorValueOut( this, "value out mouse y" );
    connector->translate (-.5f, 0.9f, -1.5f); 
    connector->rotate(-RAD2DEG(0.5/asin((ir-1)*(ir-1)+0.25)), 0.0, 0.0);
    addConnector(connector);

    for (int index = 0; index < 6; index++)
    {
        connector = new KConnectorModulatorOut (this, kStringPrintf("modulator %d", index+1));
        connector->rotate (0.0, index * 60.0, 0.0);
        connector->translate(0.0, 0.0, -ir);
        connector->rotate (-90.0, 0.0, 0.0);        
        addConnector(connector);
    }

    KFileNameValueObject * value;

    value = new KFileNameValueObject( "texture set", true );
    values.push_back(value);
    values.back()->addReceiverCallback(Controller.texture_sets, 
                                            (KSetStringPtr)&KTextureSets::setCurrentTextureSetFileName);
    values.back()->setProviderCallback(Controller.texture_sets,
                                            (KGetStringPtr)&KTextureSets::getCurrentTextureSetFileName);
                                                                                
    connector = new KConnectorAttributeIn ( this, "background" ); 
    connector->translate (0.0, 1.1f, 0.0); // top
    addConnector(connector);

    KConnectorIntValueInOut * ioConnector;

    vector<string> names;
    names.push_back("yes");
    names.push_back("no");
    vector<int> bools;
    bools.push_back(true);
    bools.push_back(false);
    ioConnector = new KConnectorIntValueInOut( this, names, bools, "clear frame" );
    ioConnector->translate (0.0, 0.9f, 1.5f); 
    ioConnector->rotate(RAD2DEG(0.5/asin((ir-1)*(ir-1)+0.25)), 0.0, 0.0);
    addConnector(ioConnector);
    values.push_back((KConnectorValueInOut*)ioConnector);
    values.back()->addReceiverCallback(this, (KSetBoolPtr)&KGlobalModulator::setClearFrame);
    values.back()->setProviderCallback(this, (KGetBoolPtr)&KGlobalModulator::getClearFrame);    
}

// --------------------------------------------------------------------------------------------------------
static void fillGap ()
{
    float c = cos(DEG2RAD(30.0));
    float s = sin(DEG2RAD(30.0));
    float ir = sqrt(3);

    glBegin(GL_QUADS);
    glNormal3f(0.0, c, s); // front/top
    glVertex3f( 1.0,   0.5,   ir);
    glVertex3f( 1.0,   1.0,  1.0);
    glVertex3f(-1.0,   1.0,  1.0);
    glVertex3f(-1.0,   0.5,   ir);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.5, cos(DEG2RAD(45.0)), 0.5); // right/top/front
    glVertex3f( 2.0,  0.5,  0.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0,  0.5,   ir);
    glNormal3f(s, c, 0.0); // right/top
    glVertex3f( 2.0,  0.5,  0.0);
    glVertex3f( 1.0,  1.0,  -1.0);
    glVertex3f( 1.0,  1.0,   1.0);
    glNormal3f(0.5, cos(DEG2RAD(45.0)), -0.5); // right/top/back
    glVertex3f( 2.0,  0.5,  0.0);
    glVertex3f( 1.0,  0.5,  -ir);
    glVertex3f( 1.0,  1.0, -1.0);
    glEnd();
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::displayConnectors ( int mode )
{
    KModule::displayConnectors(mode);
    loadId();

    float ir = sqrt(3), h = 0.5;

    glPushMatrix();
    fillGap(); glRotatef(180.0, 0.0, 1.0, 0.0);
    fillGap(); 
    glPopMatrix();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-1.0, -h, ir);
    glVertex3f(-2.0, -h, 0.0);
    glVertex3f(-1.0, -h, -ir);
    glVertex3f( 1.0, -h, -ir);
    glVertex3f( 2.0, -h, 0.0);
    glVertex3f( 1.0, -h, ir);
    glVertex3f(-1.0, -h, ir);
    glEnd();
}

// --------------------------------------------------------------------------------------------------------
void KGlobalModulator::initInspector ( KModuleInspector * inspector )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    valueWidget->addChild(new KLabel ("project file"));
    valueWidget->addChild(new KLabel (kStringPrintf("%s", Controller.modules->getFileName().c_str())));
    inspector->addValueWidget(valueWidget);

    KModule::initInspector(inspector);
} 
 
// --------------------------------------------------------------------------------------------------------
string KGlobalModulator::getDocumentation ()
{
    string documentation;
    
    documentation += kStringPrintf("<h2>modulators</h2>\n<blockquote>\n");
    documentation += kStringPrintf("<a href='#%s'>[%s]</a>&nbsp;%s<br>\n", activation_key.c_str(), activation_key.c_str(), getDescription().c_str());
    
    string modDoc;
    modDoc += KModulator::getDocumentation();

    // .................................................................... documentation for modulators
    sort(modulators.begin(), modulators.end(), activation_sort);
    vector<KModulator*>::iterator iter = modulators.begin();
    while (iter != modulators.end())
    {
        modDoc += (*iter)->getDocumentation();
        const char * key = (*iter)->getActivationKey().c_str();
        documentation += kStringPrintf("<a href='#%s'>[%s]</a>&nbsp;%s<br>\n", key, key, 
                                                                (*iter)->getDescription().c_str());
        iter++;
    }

    documentation += "</blockquote>\n";
    
    // .................................................................... documentation for triggers
    
    documentation += kStringPrintf("<h2>triggers</h2>\n<blockquote>\n");

    string triDoc;

    vector<KModule*> triggers;
    Controller.modules->getModulesOfType(triggers, false, KModuleTrigger::classId());
    if (triggers.empty()) 
    {
        documentation += "none";
    }
    else
    {
        sort(triggers.begin(), triggers.end(), activation_sort);
        vector<KModule*>::iterator triggerIter = triggers.begin();
        while (triggerIter != triggers.end())
        {
            triDoc += ((KActivationValueModule*)(*triggerIter))->getDocumentation();
            const char * key = ((KActivationValueModule*)(*triggerIter))->getActivationKey().c_str();
            documentation += kStringPrintf("<a href='#%s'>%s</a>&nbsp;%s<br>\n", key, key,
                                                            (*triggerIter)->getDescription().c_str());
            triggerIter++;
        }
    }
    documentation += "</blockquote>\n";
    
    documentation += "<h2>details</h2>\n<blockquote><h3>modulators</h3>\n<blockquote>\n";
    documentation += modDoc;
    documentation += "</blockquote>\n<h3>triggers</h3>\n<blockquote>\n";
    documentation += triDoc;
    documentation += "</blockquote>\n</blockquote>\n";

    return documentation;
}

// --------------------------------------------------------------------------------------------------------
string KGlobalModulator::getXML ( int depth ) const
{
    string xml;
    xml += KModule::getXML(depth);
    vector<KModulator*>::const_iterator iter = modulators.begin();
    while (iter != modulators.end())
    {
        if ((*iter)->isRootModule()) 
        {
            xml += (*iter)->getXML(depth);
        }
        iter++;
    }
    return xml;
}