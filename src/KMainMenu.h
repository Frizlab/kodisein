/*
 *  KMainMenu.h
 *  kodisein
 */

#ifndef __KMainMenu
#define __KMainMenu

#pragma warning(disable:4786)

#include "KMenuWindow.h"

class KButtonBox;
class KButton;
class KKeyActionHandler;

class KMainMenu : public KMenuWindow
{
    INTROSPECTION

    private:
        
    KButton * 		rButton;
    KButton * 		zButton;
    KButton * 		tButton;

    KButton * 		pButton;
    KButton * 		oButton;
    KButton * 		mButton;
    
    vector<KMenuItem*>	module_mode_items;
    vector<KMenuItem*>	object_mode_items;
    vector<KMenuItem*>	animation_mode_items;
    
    KButtonBox * 	modeButtonBox;
    KButtonBox * 	startButtonBox;

    KKeyActionHandler *	animation_key_handler;
    void		updateAnimationKeyHandler	();
    
    public:
                        KMainMenu			();

    void		create				();
    void		layout				();
       
    void		mouseModeChanged		();
    void 		applicationModeChanged		( int );
    
    void		setShowShortCuts		( bool );
    bool		getShowShortCuts		() const;
    
    void		projectionHandlerChanged	( const KPickHandler * );
    
    void		displayAboutPanel		();
    void		displayIntroPanel		();
};

#endif
