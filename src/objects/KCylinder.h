/*
 *  KCylinder.h
 *  kodisein
 */

#ifndef __KCylinder
#define __KCylinder

#include "KMatrixHandle.h"

class KCylinder : public KMatrixHandle
{
    INTROSPECTION

    protected:
    
    float				top_radius;
    int					slices;
    int					stacks;
    int					orientation;
    int					normals;

    public:
                                        KCylinder		( KMatrixModule * m );
                            
    virtual void		display 		( int mode );
    void				setTopRadius	( float t ) { top_radius = t; }
    void				setSlices		( float s ) { slices = (int)s; }
    void				setStacks		( float s ) { stacks = (int)s; }
    void				setOrientation	( int o ) { orientation = o; }
    void				setNormals		( int n ) { normals = n; }

    float				getTopRadius	() const { return top_radius; }
    float				getSlices		() const { return slices; }
    float				getStacks		() const { return stacks; }
    int					getOrientation	() const { return orientation; }
    int					getNormals		() const { return normals; }
};

#endif