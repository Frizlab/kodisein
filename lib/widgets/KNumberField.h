/*
 *  KNumberField.h
 *  kodisein
 */

#ifndef __KNumberField
#define __KNumberField

#pragma warning(disable:4786)

#include "KTextField.h"

class KNumberField : public KTextField
{
    INTROSPECTION

    public:
                                KNumberField		( GLfloat );
                                
    virtual float		getValue		();
    virtual void		notify			();

    virtual bool		handleKey		( const KKey & );
};

#endif
