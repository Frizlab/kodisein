/*
 *  KStatusMenuItem.h
 *  kodisein
 */

#ifndef __KStatusMenuItem
#define __KStatusMenuItem

#include "KMenuItem.h"

class KStatusMenuItem : public KMenuItem
{
    INTROSPECTION
    
    protected:
    
    string 		true_text;
    string 		false_text;
    
    public:
    
                        KStatusMenuItem 	( const string & , const string &, const string & = "" );
                
    void		setState		( bool );
    bool		getState 		() const;
    void		activateItem		();
    void		render			();
    const string &	getTrueText		() const { return true_text; }

    void		setXMLAttributes	( const string & );
    string		getXMLAttributes	() const;
};

#endif

