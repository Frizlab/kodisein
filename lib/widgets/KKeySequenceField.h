/*
 *  KKeySequenceField.h
 *  kodisein
 */

#ifndef __KKeySequenceField
#define __KKeySequenceField

#pragma warning(disable:4786)

#include "KWidget.h"
#include "KNotificationObject.h"

class KKeySequenceField : public KWidget, public KNotificationObject
{
    INTROSPECTION
    
    int				max_sequence_length;
    string			sequence;
    
    public:
                                KKeySequenceField	( const string &, int = 2 );
                                
    void 			setSequence 		( const string & );
    void			setPicked		( bool );
    KSize			getSize			() const;
    void			render			();
};

#endif
