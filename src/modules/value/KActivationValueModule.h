/*
 *  KActivationValueModule.h
 *  kodisein
 */

#ifndef __KActivationValueModule
#define __KActivationValueModule

#include "KValueModule.h"

class KActivationValueModule : public KValueModule
{
    INTROSPECTION

    protected:
    
    bool		activated;
    string		activation_key;
    
    public:
               
                        KActivationValueModule	();
                        ~KActivationValueModule	();
                        
    string		getActivationKey	() const { return activation_key; }
    void		setActivationKey	( const string & );
    
    void		toggleActivation	();
    virtual void	activate		() { activated = true; }
    virtual void	deactivate		() { activated = false; }
    
    virtual string	getDocumentation	();
};

#endif