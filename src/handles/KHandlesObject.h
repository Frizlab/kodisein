/*
 *  KHandlesObject.h
 *  kodisein
 */

#ifndef __KHandlesObject
#define __KHandlesObject

#include "KHandle.h"
#include "KPickable.h"
#include "KMatrixModule.h"

class KHandlesObject : public KHandle
{
    INTROSPECTION
    
    protected:
    
    int					min_id;
    int					max_id;
    KMatrixModule * 			module;
    PickableVector			handles;
    
    public:
                                        KHandlesObject  	( );
                                        KHandlesObject  	( KMatrixModule * );
                                        
    virtual				~KHandlesObject		();
    
    virtual void			setPicked		( bool );
    virtual void			deleteHandles		();
    virtual void			display			( int mode );
    virtual void			addHandle		( KHandle * handle );

    virtual void 			setPosition 		( const KVector &, bool = true );

    virtual KMatrix			getWorldMatrix		() const;

    virtual void			setOrigin		( void * handleData );
    virtual void			setModule		( KMatrixModule * m ) { module = m; }
    virtual const KMatrixModule *	getModule		() const { return module; }

    virtual bool			hasSubPickables 	() const { return true; }
    virtual const PickableVector *	getSubPickables 	() const { return &handles; }
    virtual void			setMinId		( int i ) { min_id = i; }
    virtual void			setMaxId		( int i ) { max_id = i; }
    virtual int				getMinId		()  { return min_id; }
    virtual int				getMaxId		()  { return max_id; }
};

#endif

