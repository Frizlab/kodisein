/*
 *  KSceneSet.h
 *  kodisein
 */

#ifndef __KSceneSet
#define __KSceneSet

#include "KModule.h"

class KScene;
class KModuleInspector;

class KSceneSet : public KModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    string			filename;
    void			createConnectors	();
    
    public:
                                KSceneSet 		();
    
    bool			save			() const;
    void			setFileName		( const string & );
    string			getFileName		() const { return filename; }
    string 			getDisplayName 		() const;
    KScene *			getIndexedScene		( int = 0 ) const;
    void			initInspector 		( KModuleInspector * );
};

#endif
