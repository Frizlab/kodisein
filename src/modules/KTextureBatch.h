/*
 *  KTextureBatch.h
 *  kodisein
 */

#ifndef __KTextureBatch
#define __KTextureBatch

#include "KModule.h"

class KTextureFile;
class KTexture;

class KTextureBatch : public KModule
{
    KDS_MODULE_HEADER
    
    friend class KTextureSets;
    
    protected:
    
    void				createConnectors	();
    
    public:
    
                                        KTextureBatch 		();
    
    void				displayConnectors	( int );
    string 				getDisplayName 		() const;
    KTexture * 				getIndexedTexture 	( int, int ) const;
    int					getIndex		() const;
    int					getNumberOfChildBatches	() const;
    KTextureBatch *			getNthChildBatch	( int ) const;
    void				reload			();
};

#endif
