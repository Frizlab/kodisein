/*
 *  KTextureSet.h
 *  kodisein
 */

#ifndef __KTextureSet
#define __KTextureSet

#include "KModule.h"

class KTextureBatch;
class KModuleInspector;
class KTexture;

class KTextureSet : public KModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    string			filename;
    void			createConnectors	();
                                KTextureSet 		() { createConnectors(); }
    
    public:
                                
    static KTextureSet *	newTextureSetFromFile	( const string & );
    static KTextureSet * 	newTextureSet		();
    
    bool			save			() const;
    void			reload			();
    
    void			setFileName		( const string & s ) { filename = s; }
    string			getFileName		() const { return filename; }
    
    void 			displayConnectors 	( int );
    string 			getDisplayName 		() const;
    KTexture *			getIndexedTexture	( int = 0, int = 0, int = 0 ) const;
    void			initInspector 		( KModuleInspector * );
};

#endif
