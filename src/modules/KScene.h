/*
 *  KScene.h
 *  kodisein
 */

#ifndef __KScene
#define __KScene

#include "KModule.h"

class KScene : public KModule
{
    KDS_MODULE_HEADER
    
    protected:
    
    GLuint 				texture_id_modules;
    GLuint 				texture_id_animation;
    string				filename;
    void				createConnectors	();
        
    public:
    
                                        KScene 		();
                                       ~KScene 		();
                                       
    void 				displayConnectors 	( int );
    string 				getDisplayName 		() const;
    void				setFileName		( const string & );
    string				getFileName		() const { return filename; }
    KScene * 				getNthChildScene 	( int ) const;
    int					getNumberOfChildScenes  () const;
    KConnector * 			getParentConnector	() const;
    int					getIndex		() const;
};

#endif
