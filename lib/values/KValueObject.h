/*
 *  KValueObject.h
 *  kodisein
 */

#ifndef __KValueObject
#define __KValueObject

#include "KNotificationObject.h"

class KWidgetArray;

// --------------------------------------------------------------------------------------------------------
class KValueObject : public KObject, public KNotificationObject
{
    INTROSPECTION
    
    public:
    
    string 		value_name;
    
                        KValueObject 		( const string & = "value" );

    virtual void 	setXMLValues 		( string & ) = 0;
    virtual string	getXMLValues		( int ) const = 0;

    virtual void	addToWidget		( KWidgetArray * ) = 0;
};

#endif