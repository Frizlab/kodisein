/*
 *  KFace.h
 *  kodisein
 */

#ifndef __KFace
#define __KFace

#include "KVertexHandle.h"
#include "KMatrixHandle.h"

class KFace : public KMatrixHandle
{
    INTROSPECTION

    protected:
    
    vector<KVertexHandle *>		vertices;
    
    public:
                                        KFace 		( KMatrixModule * );
                    
    virtual void			addVertex 	( KVertexHandle * );

    virtual GLfloat			getDepthValue	() const;
    
    virtual void			display		( int );

    virtual void			vertexMoved	( void * );
    virtual void			setXMLValues	( string & );
    virtual string			getXMLValues	( int = 0 ) const;
};

#endif