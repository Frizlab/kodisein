/*
 *  KTextureSets.cpp
 *  kodisein
 */

#include "KTextureSets.h"
#include "KFileTreeWindow.h"
#include "KTextureSet.h"
#include "KModules.h"
#include "KController.h"
#include "KConsole.h"

#include <algorithm>

KDL_CLASS_INTROSPECTION_1 (KTextureSets, KObject)

// --------------------------------------------------------------------------------------------------------
KTextureSets::KTextureSets() : KObject ()
{
    current_index = -1;
}

// --------------------------------------------------------------------------------------------------------
void KTextureSets::reload ()
{
    vector<KTextureSet*>::iterator iter = texture_sets.begin();
    while (iter != texture_sets.end())
    {
        (*iter)->reload();
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KTextureSets::addTextureSet ( KTextureSet * textureSet )
{
    vector<KTextureSet*>::iterator result = find (texture_sets.begin(), texture_sets.end(), textureSet);
    if (result == texture_sets.end())
    {
        texture_sets.push_back(textureSet);
    }
}

// --------------------------------------------------------------------------------------------------------
void KTextureSets::removeTextureSet ( KTextureSet * textureSet )
{
    if (textureSet == NULL) return;
    int index = getIndexOfTextureSet(textureSet);
    if (index <= current_index) current_index--;
    texture_sets.erase(texture_sets.begin()+index);
    if (current_index < 0 && texture_sets.size() > 0) current_index = 0;
}

// --------------------------------------------------------------------------------------------------------
void KTextureSets::setCurrentTextureSetFileName ( const string & fn )
{
    string textureSetFile = fn;
    
    current_index = getIndexOfTextureSet(getTextureSetWithFileName(textureSetFile));
    if (current_index < 0)
    {
        KTextureSet * textureSet = KTextureSet::newTextureSetFromFile (textureSetFile);
        if (textureSet)
        {
            if (Controller.modules->getShowTextures())
            {
                Controller.modules->active_root_modules.push_back(textureSet);
            }
            else
            {
                Controller.modules->toggleModuleHierarchy(false, textureSet);
                Controller.modules->hidden_root_modules.push_back(textureSet);
            }
            addTextureSet(textureSet);
            current_index = texture_sets.size()-1;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
string KTextureSets::getCurrentTextureSetFileName () const
{
    if (current_index >= 0) return texture_sets[current_index]->getFileName();
    return "";
}

// --------------------------------------------------------------------------------------------------------
KTextureSet * KTextureSets::getCurrentTextureSet () const
{
    if (current_index >= 0) return texture_sets[current_index];
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KTextureSet * KTextureSets::getNextTextureSet () const
{
    return texture_sets[kMin((int)texture_sets.size()-1, current_index+1)];
}

// --------------------------------------------------------------------------------------------------------
KTextureSet * KTextureSets::getPrevTextureSet () const
{
    return texture_sets[kMax(0, current_index-1)];
}

// --------------------------------------------------------------------------------------------------------
KTextureSet * KTextureSets::getTextureSetAtIndex ( unsigned int index ) const
{
    return texture_sets[kMax(0, kMin(index, texture_sets.size()))];
}

// --------------------------------------------------------------------------------------------------------
KTextureSet * KTextureSets::getTextureSetWithFileName ( const string & fn ) const
{
    vector<KTextureSet*>::const_iterator iter = texture_sets.begin();
    while (iter != texture_sets.end())
    {
        if (((KTextureSet*)*iter)->getFileName() == fn) return *iter;
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
int KTextureSets::getIndexOfTextureSet ( KTextureSet * ts ) const
{
    if (ts == NULL) return -1;
    vector<KTextureSet*>::const_iterator result = find(texture_sets.begin(), texture_sets.end(), ts);
    if (result == texture_sets.end()) return -1;
    unsigned int index = (result-texture_sets.begin());
    return index;
}

// --------------------------------------------------------------------------------------------------------
void KTextureSets::openFile ( const string & fn )
{
    string textureSetFile = fn;

    KTextureSet * newTextureSet = KTextureSet::newTextureSetFromFile (textureSetFile);
    if (newTextureSet)
    {
        Controller.file_browser->hide();
        Controller.modules->unpick();
        Controller.modules->deleteModuleHierarchy(getTextureSetWithFileName(textureSetFile));        
        addTextureSet(newTextureSet);
    }
}

// --------------------------------------------------------------------------------------------------------
void KTextureSets::open ()
{
    Controller.file_browser->addReceiverCallback(this, (KSetStringPtr)&KTextureSets::openFile);
    Controller.file_browser->show();
}

// --------------------------------------------------------------------------------------------------------
void KTextureSets::save ()
{
    KModule * pickedModule = Controller.modules->getModuleForPickable(Controller.modules->getPickedPickable());
    if (pickedModule && pickedModule->getRootModule()->getClassId() >= KTextureSet::classId())
    {
        ((KTextureSet*)pickedModule->getRootModule())->save();
        return;
    }
    if (current_index >= 0) texture_sets[current_index]->save();
}

// --------------------------------------------------------------------------------------------------------
void KTextureSets::close ()
{
    KModule * pickedModule = Controller.modules->getModuleForPickable(Controller.modules->getPickedPickable());
    if (pickedModule == NULL)
    {
        if (current_index >= 0) Controller.modules->deleteModuleHierarchy(texture_sets[current_index]);
    }
    else if (pickedModule->getRootModule()->getClassId() >= KTextureSet::classId())
    {
        Controller.modules->deleteModuleHierarchy(pickedModule->getRootModule());
    }
}

