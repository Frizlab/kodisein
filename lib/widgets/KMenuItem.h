/*
 *  KMenuItem.h
 *  kodisein
 */

#ifndef __KMenuItem
#define __KMenuItem

#pragma warning(disable:4786)

#include "KButton.h"

class KMenuItem : public KButton
{
    INTROSPECTION
    
    protected:
    
    string 			shortcut;

    public:	
                                KMenuItem 	 	( const string &, const string & = "" );
         
    virtual void		setShortcut	 	( const string & );
    virtual string		getShortcut	 	() const { return shortcut; }
    virtual void        	setPicked 	 	( bool );
    virtual void		activate	 	();
    virtual void		activateItem	 	();
    virtual void		deactivate	 	();
    virtual void		highlight	 	();
    virtual void		render		 	();
    virtual void		renderShortCut	 	();

    virtual string		getText			() const;
    virtual KSize		getSize 		() const;
    virtual void		setXMLAttributes	( const string & );
    virtual string		getXMLAttributes	() const;
    virtual void		setXML			( string & );
    virtual string		getXML 			( int = 0 ) const;
};

#endif