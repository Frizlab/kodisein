/*
 *  KTextureSets.h
 *  kodisein
 */

#ifndef __KTextureSets
#define __KTextureSets

#include "KNotificationObject.h"

#include <vector>

class KTextureSet;

class KTextureSets : public KObject
{
    INTROSPECTION
    
    protected:
    
    vector<KTextureSet*>	texture_sets;
    int				current_index;
    
    public:
    
                                KTextureSets 			();
    virtual			~KTextureSets 			() {}
                                
    void			addTextureSet			( KTextureSet * );
    void			removeTextureSet		( KTextureSet * );
    int				getIndexOfTextureSet		( KTextureSet * ) const;
    KTextureSet	*		getCurrentTextureSet		() const;
    KTextureSet	*		getNextTextureSet		() const;
    KTextureSet	*		getPrevTextureSet		() const;
    KTextureSet *		getTextureSetAtIndex		( unsigned int ) const;
    KTextureSet *		getTextureSetWithFileName	( const string & ) const;

    string	 		getCurrentTextureSetFileName 	() const;
    void 	 		setCurrentTextureSetFileName 	( const string & ); 
    void			openFile			( const string & );
    void			open				();
    void			save				();
    void			close				();
    void			reload				();
};

#endif

