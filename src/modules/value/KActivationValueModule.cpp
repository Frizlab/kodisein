/*
 *  KActivationValueModule.cpp
 *  kodisein
 */

#include "KActivationValueModule.h"
#include "KController.h"
#include "KModules.h"
#include "KKeyActionHandler.h"
#include "KConnectorValueInOut.h"
#include "KStringTools.h"

#include <algorithm>

KDL_CLASS_INTROSPECTION_1 (KActivationValueModule, KValueModule)

// --------------------------------------------------------------------------------------------------------
KActivationValueModule::KActivationValueModule () : KValueModule ()
{
    activated = false;
}

// --------------------------------------------------------------------------------------------------------
KActivationValueModule::~KActivationValueModule ()
{
    Controller.mod_key_handler.removeSequenceCallback(activation_key, this,
                                            (KCallbackPtr)&KActivationValueModule::toggleActivation);
}

// --------------------------------------------------------------------------------------------------------
void KActivationValueModule::toggleActivation ()
{
    if (activated)
    {
        deactivate();
    }
    else
    {
        activate();
    }
}

// --------------------------------------------------------------------------------------------------------
void KActivationValueModule::setActivationKey ( const string & activationString )
{
    if (activationString != activation_key)
    {
        Controller.mod_key_handler.removeSequenceCallback(activation_key, this, 
                                            (KCallbackPtr)&KActivationValueModule::toggleActivation);
        activation_key = activationString;
        if (!activation_key.empty())
        {
            Controller.mod_key_handler.addSequenceCallback(activation_key, this, 
                                            (KCallbackPtr)&KActivationValueModule::toggleActivation);
        }
        Controller.modules->updateModuleInspector();
    }
}
  
// --------------------------------------------------------------------------------------------------------
string KActivationValueModule::getDocumentation ()
{
    string documentation;

    documentation += kStringPrintf("<a name='%s'></a>\n", activation_key.c_str());
    documentation += kStringPrintf("[%s] ", activation_key.c_str()) + getDescription();
    documentation += "<blockquote>\n";
    
    vector<KConnectorValueInOut*> leafConnectors;
    vector<KModule*> modules;
    getLeafConnectors (leafConnectors);
    vector<KConnectorValueInOut*>::iterator iter = leafConnectors.begin();
    while (iter != leafConnectors.end()) // collect modules
    {
        KModule * module = (*iter)->getModule();
        if (find(modules.begin(), modules.end(), module) == modules.end())
        {
            modules.push_back(module);
        }
        iter++;
    }
    
    vector<KModule*>::iterator moduleIter = modules.begin();
    while (moduleIter != modules.end())
    {
        documentation += (*moduleIter)->getDisplayName() + "&nbsp;" + (*moduleIter)->getDescription();
        documentation += "\n<blockquote>\n";
        iter = leafConnectors.begin();
        while (iter != leafConnectors.end())
        {
            if ((*iter)->getModule() == (*moduleIter))
            {
                documentation += (*iter)->getName() + "<br>";
            }
            iter++;
        }
        documentation += "</blockquote>\n";
        moduleIter++;
    }
    
    documentation += "</blockquote>\n";
    
    return documentation;
}