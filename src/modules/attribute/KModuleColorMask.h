/*
 *  KModuleColorMask.h
 *  kodisein
 */
#pragma warning(disable:4786)

#ifndef __KModuleColorMask
#define __KModuleColorMask

#include "KAttributeModule.h"

class KModuleColorMask : public KAttributeModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    vector<bool> color_mask;
 
    void	createConnectors	();
   
    public:
    
                KModuleColorMask	();
    
    void	apply			();
    
    bool	getRedMask		() const { return color_mask[0]; }
    bool	getGreenMask	() const { return color_mask[1]; }
    bool	getBlueMask		() const { return color_mask[2]; }
    bool	getAlphaMask	() const { return color_mask[3]; }
    void	setRedMask		( bool b ) { color_mask[0] = b; }
    void	setGreenMask	( bool b ) { color_mask[1] = b; }
    void	setBlueMask		( bool b ) { color_mask[2] = b; }
    void	setAlphaMask	( bool b ) { color_mask[3] = b; }
};

#endif