/*
 *  KModuleSize.h
 *  kodisein
 */

#ifndef __KModuleSize
#define __KModuleSize

#include "KAttributeModule.h"

class KModuleSize : public KAttributeModule
{
    KDS_MODULE_HEADER
    
    protected:
 
    float	point_size;
    float	line_width;
 
    void	createConnectors	();
   
    public:
    
                KModuleSize		();
    
    void	apply			();
    
    float	getLineWidth		() const { return line_width; }
    void	setLineWidth		( float );
    float	getPointSize		() const { return point_size; }
    void	setPointSize		( float );
};

#endif