/*
 *  KConsole.cpp
 *  kodisein
 */

#include "KConsole.h"
#include "KIconButton.h"
#include "KTextWidget.h"
#include "KMessagePanel.h"
#include "KProjection.h"
#include "KColor.h"

#include <SDL.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KConsole, KWindow)

KConsole * KConsole::console = NULL;

// --------------------------------------------------------------------------------------------------------
KConsole::KConsole () : KWindow ()
{
    depth 	= -INT_MAX+1;
    text_widget = new KTextWidget();
    
    text_widget->setTextSize(KSize(20,1));
    text_widget->setMinSize(text_widget->getSize());
    text_widget->flags[KDL_WIDGET_FLAG_FILL_X] = true;
    text_widget->flags[KDL_WIDGET_FLAG_FILL_Y] = true;
    text_widget->flags[KDL_TEXTWIDGET_FLAG_AUTO_SCROLLDOWN] = true; 
    
    KButton * button;
    button = new KIconButton(ICON_CLEAR);
    button->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::clear);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(ICON_DOUBLE_UP);
    button->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollPageUp);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(ICON_DOUBLE_DOWN);
    button->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollPageDown);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(ICON_SINGLE_UP);
    button->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollLineUp);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(ICON_SINGLE_DOWN);
    button->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollLineDown);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(ICON_TOP);
    button->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollToTop);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(ICON_BOTTOM);
    button->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollToBottom);
    button_widget->addChild(button);
    addPickable(button);

    widget->addChild(text_widget);
    widget->layout();
    widget->hide();
}

// --------------------------------------------------------------------------------------------------------
void KConsole::create ()
{
    if (console == NULL)
    {
        console = new KConsole();
    }
}
            
// --------------------------------------------------------------------------------------------------------
void KConsole::clear()
{ 
    text_widget->clear(); 
}

// --------------------------------------------------------------------------------------------------------
void KConsole::checkGLError ( const string & msg )
{ 
    int error = glGetError();
    if (error != GL_NO_ERROR)
    {
        KConsole::printf("[GL_ERROR] %s %s", gluErrorString(error), msg.c_str());
    }
}

// --------------------------------------------------------------------------------------------------------
void KConsole::printError ( const string & str, bool panel )
{ 
    string errorStr = "[ERROR] ";
    errorStr += str; errorStr += "\n";
    ::printf("%s", errorStr.c_str());
    if (panel)  KMessagePanel::displayMessage("[ERROR]", str);
    if (console)
    {
        console->text_widget->print(errorStr);
        if (panel == false && console->isVisible() == false) 
        {
            // show console if no panel displayed
            console->show(); 
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KConsole::dbg ( const char * fmt ...)
{
    va_list argList;
    va_start(argList,fmt);
    string newText = kStringPrintFormArgs(fmt, &argList); newText += "\n";
    va_end(argList);
    ::printf("%s", newText.c_str());
    if (console)
    {
        console->text_widget->print(newText);
    }
}

// --------------------------------------------------------------------------------------------------------
void KConsole::debugf ( bool output, const char * fmt ...)
{
    if (!output) return;
    va_list argList;
    va_start(argList,fmt);
    string newText = kStringPrintFormArgs(fmt, &argList); newText += "\n";
    va_end(argList);
    ::printf("%s", newText.c_str());
    if (console)
    {
        console->text_widget->print(newText);
    }
}

// --------------------------------------------------------------------------------------------------------
void KConsole::printf ( const char * fmt ...)
{
    va_list argList;
    va_start(argList,fmt);
    string newText = kStringPrintFormArgs(fmt, &argList); newText += "\n";
    va_end(argList);
    ::printf("%s", newText.c_str());
    if (console)
    {
        console->text_widget->print(newText);
    }
}

// --------------------------------------------------------------------------------------------------------
void KConsole::relayout ( const KSize & newSize )
{
    KWindow::relayout(newSize);
    text_widget->setLabelText();
}