/*
 *  KMatrixHandle.h
 *  kodisein
 */

#ifndef __KMatrixHandle
#define __KMatrixHandle

#pragma warning(disable:4786)

#include "KHandlesObject.h"

class KMatrixHandle :	public	KHandlesObject
{
    INTROSPECTION
    
    public:
                                        KMatrixHandle		();
                                        KMatrixHandle		( KMatrixModule * m );
                                        
    void				setPicked		( bool );
    void				initRotateHandles	();
    void				initScaleHandles	();
    void				initTranslateHandles	();
    void				xrHandleMoved		( void * handleData );
    void				yrHandleMoved		( void * handleData );
    void				zrHandleMoved		( void * handleData );
    void				xsHandleMoved		( void * handleData );
    void				ysHandleMoved		( void * handleData );
    void				zsHandleMoved		( void * handleData );
    void				xHandleMoved		( void * handleData );
    void				yHandleMoved		( void * handleData );
    void				zHandleMoved		( void * handleData );
    void				xyHandleMoved		( void * handleData );
    void				xzHandleMoved		( void * handleData );
    void				yzHandleMoved		( void * handleData );
};

#endif

