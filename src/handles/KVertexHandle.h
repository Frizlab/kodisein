/*
 *  KVertexHandle.h
 *  kodisein
 */

#ifndef __KVertexHandle
#define __KVertexHandle

#include "KHandle.h"

class KModuleInspector;

enum {	KDL_NOTIFICATION_TYPE_VERTEX_MOVED = KDL_NOTIFICATION_TYPE_HANDLE_END, 
        KDL_NOTIFICATION_TYPE_VERTEX_END };

class KVertexHandle : public KHandle
{
    INTROSPECTION
    
    public:
                                KVertexHandle 		( KHandle *, GLfloat, GLfloat, GLfloat );
                                KVertexHandle		( KHandle *, const KVector & );
    
    virtual void		moved			( const KMouseEvent & );
    virtual void 		setPosition 		( const KVector &, bool = true );
    virtual void		notify			() const;
    virtual void		display			( int mode );
};

#endif