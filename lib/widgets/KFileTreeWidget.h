/*
 *  KFileTreeWidget.h
 *  kodisein
 */

#ifndef __KFileTreeWidget
#define __KFileTreeWidget

#pragma warning(disable:4786)

#include "KProjectionWidget.h"
#include "KNotificationObject.h"

enum {	KDL_NOTIFICATION_TYPE_SELECT_NODE = KDL_NOTIFICATION_TYPE_NOTIFICATION_END,
        KDL_NOTIFICATION_TYPE_OPEN_DIRECTORY, KDL_NOTIFICATION_TYPE_OPEN_FILE, 
        KDL_NOTIFICATION_TYPE_FILETREE_END };

class KPopupMenu;
class KFileTreeDir;
class KFileTreeDirUp;

class KFileTreeWidget : public KProjectionWidget, public KNotificationObject
{
    INTROSPECTION
    
    protected:

    void		deleteDisplayList ();
    GLuint		display_list;
    KFileTreeDir *	current_dir_node;
    KFileTreeDirUp *	up_node;
    KPopupMenu *	popup_menu;
    
    public:
    
                KFileTreeWidget 	();
                ~KFileTreeWidget	();
    
    void	displayContent		();
    void	displayMenu		();
    void	refresh			();
    string	getCurrentDir		() const;
    void	setCurrentDir		( const string & );

    void	setShowDotFiles		( bool );
    bool	getShowDotFiles		() const;
    void	setShowCubes		( bool );
    bool	getShowCubes		() const; 

    void	menuCallback		( const string & );
    
    bool	pick			( const KMouseEvent & );
    void	picked 			();
    void	unpicked 		();
    void	doubleClicked 		();
    void	focusOnPickedPickable 	( bool = false );
};

#endif
