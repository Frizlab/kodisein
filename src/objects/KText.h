/*
 *  KText.h
 *  kodisein
 */

#ifndef __KText
#define __KText

#include "KMatrixHandle.h"

class KText : public KMatrixHandle
{
    INTROSPECTION

    protected:
            
    void *				font;
    string				text;

    public:
                                        KText 			( KMatrixModule * m );
                            
    virtual void			setFont			( void * f ) { font = f; }
    virtual void *			getFont			()  { return font; }

    virtual void			setText			( const string & s ) { text = s; }
    virtual string			getText			() const { return text; }
    
    virtual void			display 		( int mode );
};

#endif