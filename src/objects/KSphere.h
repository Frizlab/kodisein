/*
 *  KSphere.h
 *  kodisein
 */

#ifndef __KSphere
#define __KSphere

#include "KMatrixHandle.h"

class KSphere : public KMatrixHandle
{
    INTROSPECTION

    protected:
    
    int					slices;
    int					stacks;
    int					orientation;
    int					normals;

    public:
                                        KSphere			( KMatrixModule * m );
                            
    virtual void			display 		( int mode );
    void				setSlices		( float );
    void				setStacks		( float );
    void				setOrientation		( int o ) { orientation = o; }
    void				setNormals		( int n ) { normals = n; }

    float				getSlices		() const { return slices; }
    float				getStacks		() const { return stacks; }
    int					getOrientation	() const { return orientation; }
    int					getNormals		() const { return normals; }
};

#endif