/*
 *  KModuleGoto.h
 *  kodisein
 */

#ifndef __KModuleGoto
#define __KModuleGoto

#include "KHubModule.h"

class KModuleLabel;

class KModuleGoto : public KHubModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    KModuleLabel *		label;
    string 			label_name;
    int 			active;
    void			createConnectors	();

    public:
    
                                KModuleGoto		();
                               ~KModuleGoto		();
                    
    void			setLabelName		( const string & );
    string 			getLabelName		() const { return label_name; }
    void			setActive			( int );
    int				getActive			() const { return active; }
    
    string 			getDisplayName 		() const;
    
    KModuleLabel *		getLabel		() const { return label; }
    virtual void		displayChildModules	( int );
};

#endif