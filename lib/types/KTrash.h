/*
 *  KTrash.h
 *  kodisein
 */

#ifndef __KTrash
#define __KTrash

#include <vector>

using namespace std;

class KObject;

class KTrash
{
    static vector<KObject*>	trash_can;
    
    public:
    
                                ~KTrash		() { recycle(); }
                                    
    static void			addObject	( KObject * );
    static void			recycle		();	
};

#endif

