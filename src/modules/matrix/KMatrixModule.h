/*
 *  KMatrixModule.h
 *  kodisein
 */

#ifndef __KMatrixModule
#define __KMatrixModule

#include "KModule.h"

class KHandlesObject;

class KMatrixModule : public KModule
{
    INTROSPECTION
    
    protected:
    
    KHandlesObject *		matrix_object;
    
    public:
    
                                KMatrixModule		();
                                KMatrixModule		( const KMatrixModule & );
                                ~KMatrixModule		();
    
    virtual KMatrixModule *	getFirstChild		() const;
    KMatrixModule *		getNextSibling		() const;
    KMatrixModule *		getPrevSibling		() const;
    
    virtual void		setPicked		( bool );
    virtual void		display			( int mode );
    virtual KHandlesObject *	getMatrixObject		() { return matrix_object; }
    
    virtual const KMatrix &	getMatrix		() const { return *(KMatrix*)matrix_object; }
    virtual KMatrix		getWorldMatrix		() const;

    virtual void		apply			( KMatrix ) const;
    virtual void		initInspector		( KModuleInspector * );

    virtual void		setXMLValues		( string & );
    virtual string		getXMLValues		( int depth = 0 ) const;
};

#endif
