/*
 *  KTextWidget.h
 *  kodisein
 */

#ifndef __KTextWidget
#define __KTextWidget

#pragma warning(disable:4786)

#include "KLabel.h"

enum {	KDL_TEXTWIDGET_FLAG_AUTO_SCROLLDOWN = KDL_LABEL_FLAG_END,
        KDL_TEXTWIDGET_FLAG_END };

class KTextWidget : public KLabel
{
    INTROSPECTION
    
    protected:
    
    string		full_text;
    unsigned int	current_row;
        
    public:
                        KTextWidget             ();
                                
    virtual void	print			( const string & s ) { printf("%s", s.c_str()); }
    virtual void	printf			( const char * fmt ... );
    virtual void	scrollPageUp		();
    virtual void	scrollPageDown		();
    virtual void	scrollLineUp		();
    virtual void	scrollLineDown		();    
    virtual void	scrollToTop		();
    virtual void	scrollToBottom		();    
    virtual void	setSize			( KSize );
    virtual void	clear			();
    void		setLabelText		();
};

#endif
