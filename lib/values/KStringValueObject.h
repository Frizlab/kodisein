/*
 *  KStringValueObject.h
 *  kodisein
 */

#ifndef __KStringValueObject
#define __KStringValueObject

#include "KValueObject.h"

class KStringValueObject : public KValueObject
{
    INTROSPECTION

    public:
                        KStringValueObject 	( const string & n = "string" ) : KValueObject (n) {}
                        
            void	setReceiverValue	( const string & );
            string	getProviderValue	() const;

    virtual void 	setXMLValues 		( string & );
    virtual string	getXMLValues		( int ) const;

    virtual void	addToWidget		( KWidgetArray * );
};

#endif