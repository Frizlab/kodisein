/*
 *  KSizeValueObject.h
 *  kodisein
 */

#ifndef __KSizeValueObject
#define __KSizeValueObject

#include "KValueObject.h"
#include "KVector.h"

class KSizeValueObject : public KValueObject
{
    INTROSPECTION
    
    public:
                KSizeValueObject 	( const string & n = "size value" );
                        
    void	setWidthValue		( float );
    void	setHeightValue		( float );
    KSize	getProviderValue	() const;
    void	setReceiverValue	( const KSize & );

    void 	setXMLValues 		( string & );
    string	getXMLValues		( int ) const;

    void	addToWidget		( KWidgetArray * );
};

#endif