/*
 *  KDisk.h
 *  kodisein
 */

#ifndef __KDisk
#define __KDisk

#include "KMatrixHandle.h"

class KDisk : public KMatrixHandle
{
    INTROSPECTION

    protected:
    
    float				inner_radius;
    float				start_angle;
    float				sweep_angle;
    int					slices;
    int					loops;
    int					orientation;
    int					normals;

    public:
                                        KDisk		( KMatrixModule * m );
                            
    virtual void			display 		( int mode );
    void				setInnerRadius		( float );
    void				setStartAngle		( float s ) { start_angle = s; }
    void				setSweepAngle		( float );
    void				setSlices		( float );
    void				setLoops		( float );
    void				setOrientation		( int o ) { orientation = o; }
    void				setNormals		( int n ) { normals = n; }

    float				getInnerRadius	() const { return inner_radius; }
    float				getStartAngle	() const { return start_angle; }
    float				getSweepAngle	() const { return sweep_angle; }
    float				getSlices		() const { return slices; }
    float				getLoops		() const { return loops; }
    int					getOrientation	() const { return orientation; }
    int					getNormals		() const { return normals; }
};

#endif