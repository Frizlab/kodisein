/*
 *  KModuleInspector.cpp
 *  kodisein
 */

#include "KModuleInspector.h"
#include "KValueModule.h"
#include "KIconButton.h"
#include "KNumberField.h"
#include "KProjection.h"
#include "KModules.h"
#include "KConsole.h"
#include "KOrthographicProjection.h"

KDL_CLASS_INTROSPECTION_1 (KModuleInspector, KWindow)

// --------------------------------------------------------------------------------------------------------
KModuleInspector::KModuleInspector () : KWindow ( KDL_WINDOW_FEATURES_CLOSE_BUTTON | 
                                                  KDL_WINDOW_FEATURES_MAXIMIZE_BUTTON | 
                                                  KDL_WINDOW_FEATURES_PROJECTION )
{
    type_label = new KLabel("");
    
    values_widget = new KWidgetArray ();
    values_widget->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
    values_widget->flags[KDL_WIDGET_FLAG_FRAMED]	  = true;

    button_widget->addChild(type_label);
    widget->addChild(values_widget);

    maximize_button->setType(ICON_ARROW_DOWN);
     
    widget->hide();
}

// --------------------------------------------------------------------------------------------------------
void KModuleInspector::showOrMaximize ( bool showOrMaximize=true)
{
	if (showOrMaximize)
	{
		if (getVisibility()) maximize();
		else 
		{
			widget->layout();
			// reset the position to make sure the inspector is not outside the screen
			setPosition(KPosition(widget->getPosition()[X], widget->getPosition()[Y]));

			show();
		}
	}
}

// --------------------------------------------------------------------------------------------------------
bool KModuleInspector::isVisibleAndMaximized () const
{
    return (getVisibility() && !isMinimized());
}

// --------------------------------------------------------------------------------------------------------
bool KModuleInspector::isMinimized () const
{
    return (maximize_button->getType() == ICON_ARROW_UP);
}

// --------------------------------------------------------------------------------------------------------
void KModuleInspector::maximize ()
{
    if (maximize_button->getType() == ICON_ARROW_DOWN)
    {
        old_pos  = widget->getViewportPos();
        old_size = widget->getSize();
        
        values_widget->hide	();
        widget->setFrameSpacing	(0);
        widget->setChildSpacing	(0);
        widget->layout		();
        setPosition		(KPosition(0, -INT_MAX));
        setSize 		(KSize(INT_MAX, 0));
        maximize_button->setType(ICON_ARROW_UP);
        widget->flags[KDL_WIDGET_FLAG_FRAMED] = false;
    }
    else
    {
        widget->setFrameSpacing	(KDL_WIDGET_DEFAULT_FRAME_SPACING);
        widget->setChildSpacing	(KDL_WIDGET_DEFAULT_CHILD_SPACING);
        values_widget->show	();
        widget->layout		();
        setSize 		(old_size);
        setPosition		(old_pos);
        maximize_button->setType(ICON_ARROW_DOWN);
        widget->flags[KDL_WIDGET_FLAG_FRAMED] = true;
    }
}

// --------------------------------------------------------------------------------------------------------
void KModuleInspector::setTitle ( const string & t )
{
    type_label->setText(t);
}

// --------------------------------------------------------------------------------------------------------
string KModuleInspector::getTitle () const
{
    return type_label->getText();
}

// --------------------------------------------------------------------------------------------------------
void KModuleInspector::addValueWidget ( KWidget * w )
{
    values_widget->addChild(w);
}

// --------------------------------------------------------------------------------------------------------
void KModuleInspector::setInspectedModule ( KModule * m )
{
    type_label->setText("");
    KPickHandler::removeAllPickables(); // remove all pickables
    values_widget->clear();		// delete all children on values_widget
    addPickable(widget);		// add removed pickables again
    addPickable(close_button);
    addPickable(maximize_button);
    
    if (m)
    {
        m->initInspector(this);
        if (maximize_button->getType() == ICON_ARROW_DOWN)
        {
            values_widget->show();
        }
    }
    else
    {
        values_widget->hide();
    }
    
    values_widget->alignLabels();
    
    if (isVisibleAndMaximized()) 
    {
        widget->layout();
        // reset the position to make sure the inspector is not outside the screen
        setPosition(KPosition(widget->getPosition()[X], widget->getPosition()[Y]));
    }
}


