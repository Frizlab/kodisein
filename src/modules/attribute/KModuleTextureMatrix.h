/*
 *  KModuleTextureMatrix.h
 *  kodisein
 */

#ifndef __KModuleTextureMatrix
#define __KModuleTextureMatrix

#include "KAttributeModule.h"
#include "KSeparatedMatrix.h"

class KModuleTextureMatrix : public KAttributeModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    KSeparatedMatrix	texture_matrix;
    void		createMatrixConnectors ();

    public:
    
                KModuleTextureMatrix	();

    void	apply			();
    void	postApply		();
};

#endif