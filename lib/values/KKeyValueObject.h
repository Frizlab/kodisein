/*
 *  KKeyValueObject.h
 *  kodisein
 */

#ifndef __KKeyValueObject
#define __KKeyValueObject

#include "KStringValueObject.h"

class KKeyValueObject : public KStringValueObject
{
    INTROSPECTION

    protected:
    
    int			max_sequence;

    public:
                        KKeyValueObject 	( const string & = "", int = 2 );

    void		addToWidget		( KWidgetArray * );
};

#endif