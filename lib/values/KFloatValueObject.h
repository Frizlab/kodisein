/*
 *  KFloatValueObject.h
 *  kodisein
 */

#ifndef __KFloatValueObject
#define __KFloatValueObject

#include "KValueObject.h"

class KFloatValueObject : public KValueObject
{
    INTROSPECTION
    
    public:
                        KFloatValueObject 	( const string & n = "float value" );
                        
    virtual void	setReceiverValue	( float );
    void		setValue		( float );
    virtual float	getProviderValue	() const;
    virtual float	getValue		() const;

    virtual void 	setXMLValues 		( string & );
    virtual string	getXMLValues		( int ) const;

    virtual void	addToWidget		( KWidgetArray * );
};

#endif