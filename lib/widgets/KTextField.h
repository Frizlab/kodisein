/*
 *  KTextField.h
 *  kodisein
 */

#ifndef __KTextField
#define __KTextField

#pragma warning(disable:4786)

#include "KLabel.h"
#include "KKeyHandler.h"
#include "KNotificationObject.h"
#include "KColor.h"

enum {	KDL_TEXTFIELD_FLAG_NOTIFY_ON_UNPICK = KDL_LABEL_FLAG_END,
        KDL_TEXTFIELD_FLAG_END};

enum {	KDL_NOTIFICATION_TYPE_TEXTFIELD_PICKED = KDL_NOTIFICATION_TYPE_NOTIFICATION_END, 
        KDL_NOTIFICATION_TYPE_TEXTFIELD_END };

class KTextField : public KLabel, public KKeyHandler
{
    INTROSPECTION

    protected:
    
    int				cursor_pos;
    int				selection_pos;
    int				x_offset;

    KColor			selection_color;
        
    KTextField * 		firstTextFieldInVector 	( const vector<KWidget*> & );
    KTextField * 		lastTextFieldInVector 	( const vector<KWidget*> & );
    KTextField *		nextTextField		();
    KTextField *		prevTextField		();
    
    public:
                                KTextField		( const string & = "" );
    virtual void		selectAll		();
    virtual void                update                  ();
    virtual void		render			();
    virtual void		mouseMoved 		( const KMouseEvent & );
    virtual void		doubleClicked 		();
    virtual string		getSelection		() const;
    virtual void		eraseSelection		();
    virtual void		setPicked		( bool );
    virtual void		setText			( const string & );
    virtual void		printf			( const char * fmt ... );
    virtual void		notify			() { notifyReceivers(text); }

    virtual bool		handleKey		( const KKey & );
};

#endif
