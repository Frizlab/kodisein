/*
 *  KModuleLabel.h
 *  kodisein
 */

#ifndef __KModuleLabel
#define __KModuleLabel

#include "KHubModule.h"

class KModuleGoto;

class KModuleLabel : public KHubModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    vector<KModuleGoto*>	gotos;
    string 			label_name;
    int				active;
    void			createConnectors	();

    public:
    
                                KModuleLabel		();
                               ~KModuleLabel		();
    
    static KModuleLabel *	getLabelWithName	( const string & );
    
    void			addGoto			( KModuleGoto * );
    void			removeGoto		( KModuleGoto * );
    
    bool			connectModule		( KModule *, KConnector * = NULL,
                                                                     KConnector * = NULL );
    void			disconnectConnector 	( KConnector * );
    void			setLabelName		( const string & );
    string 			getLabelName		() const { return label_name; }
    void			setActive			( int );
    int				getActive			() const { return active; }
    string 			getDisplayName 		() const;
    
    virtual void		displayChildModules	( int mode );
};

#endif