/*
 *  KBox.h
 *  kodisein
 */

#ifndef __KBox
#define __KBox

#include "KMatrixHandle.h"

class KBox : public KMatrixHandle
{
    INTROSPECTION

    protected:
            
    int			orientation;

    public:
                        KBox 			( KMatrixModule * m );
                            
	virtual void	display 		( int mode );
    void		setOrientation		( int o ) { orientation = o; }
    int			getOrientation		() const { return orientation; }

};

#endif