/*
 *  KTrash.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KTrash.h"
#include "KNotificationObject.h"

#include <algorithm>

vector<KObject*> KTrash::trash_can;

// --------------------------------------------------------------------------------------------------------
void KTrash::addObject ( KObject * object ) 
{
    vector<KObject*>::iterator result = find (KTrash::trash_can.begin(), KTrash::trash_can.end(), object);
    if (result == KTrash::trash_can.end())
    {
        KTrash::trash_can.push_back(object);
    }
}

// --------------------------------------------------------------------------------------------------------
void KTrash::recycle () 
{
    vector<KObject*>::iterator iter = KTrash::trash_can.begin();
    if (iter != KTrash::trash_can.end())
    {
        delete (*iter);
        iter++;
    }
    trash_can.clear();
}


