/*
 *  KConsole.cpp
 *  kodisein
 */

#ifndef __KConsole
#define __KConsole

#pragma warning(disable:4786)

#include "KWindow.h"
#include "KStringTools.h"

using namespace std;

class KTextWidget;

class KConsole : public KWindow
{
    INTROSPECTION
    
    protected:
    
                        KConsole		();

    static KConsole *	console;
    KTextWidget * 	text_widget;
    KIconButton *     	maximize_button;
    
    public:
    
    static void		create			();
    static KConsole *	getConsole		() { return console; }
                                        
    static void		printf			( const char * fmt ... );
    static void		debugf			( bool, const char * fmt ... );
	static void		dbg 			( const char * fmt ... );
    static void		print			( const string & s ) { printf("%s",s.c_str()); }
    static void		printError		( const string &, bool = false );
    static void		checkGLError		( const string & = "");
    
    virtual void	relayout		( const KSize & );
    virtual void	clear			();
};

#endif

