/*
 *  KHandle.h
 *  kodisein
 */

#ifndef __KHandle
#define __KHandle

#pragma warning(disable:4786)

#include "KSeparatedMatrix.h"
#include "KPickable.h"
#include "KNotificationObject.h"
#include "KEventHandler.h"
#include "KVector.h"

enum {  KDL_NOTIFICATION_TYPE_HANDLE_MOVED = KDL_NOTIFICATION_TYPE_NOTIFICATION_END, 
        KDL_NOTIFICATION_TYPE_HANDLE_END };

class KModuleInspector;
class KHandlesObject;

typedef struct 
{
    const KVector	  * pos;
    const KMouseEvent * mouseEvent;
} KHandleData;

class KHandle : public KSeparatedMatrix, public KPickable, public KNotificationObject
{
    INTROSPECTION

    protected:
    
    KHandle *			parent;
    
    public:
    
                                KHandle 		();
                                KHandle			( KHandle * );
                                
    virtual void		setPicked		( bool );
                                
    virtual void		preDisplay 		( int );
    virtual void		display 		( int ) {}
    virtual void		postDisplay 		( int );

    virtual void		moved			( const KMouseEvent & );
    
    virtual KMatrix		getWorldMatrix		() const;
    
    virtual const KHandle *	getParent		() const { return parent; }
    virtual KHandlesObject *	getRootHandle		() const;
    
    virtual void 		notify		 	() const;
    virtual void		initInspector		( KModuleInspector * );
    virtual void		initInspectorRotation	( KModuleInspector * );
    virtual void		initInspectorPosition	( KModuleInspector * );
    virtual void		initInspectorSize	( KModuleInspector * );
};

#endif
