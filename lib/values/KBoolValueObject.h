/*
 *  KBoolValueObject.h
 *  kodisein
 */

#ifndef __KBoolValueObject
#define __KBoolValueObject

#include "KValueObject.h"

class KBoolValueObject : public KValueObject
{
    INTROSPECTION
        
    public:
                        KBoolValueObject 	( const string & n = "bool value" ) : KValueObject (n) {}
                        
            void	setReceiverValue	( bool );
            bool	getProviderValue	() const;

    virtual void 	setXMLValues 		( string & );
    virtual string	getXMLValues		( int ) const;

    virtual void	addToWidget		( KWidgetArray * );
};

#endif