/*
 *  KFileNameValueObject.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KFileNameValueObject.h"
#include "KFileNameField.h"
#include "KWidgetArray.h"
#include "KModuleInspector.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 (KFileNameValueObject, KValueObject)

// --------------------------------------------------------------------------------------------------------
KFileNameValueObject::KFileNameValueObject (const string & n, bool openFilesOnly, bool selectDirectories ) : KStringValueObject (n) 
{
    open_files_only	= openFilesOnly;
    select_directories	= selectDirectories;
}
 
// --------------------------------------------------------------------------------------------------------
void KFileNameValueObject::selectedFileChanged (const string & fn)
{
    notifyReceivers(fn, KDL_NOTIFICATION_TYPE_SELECTED_FILE_CHANGED);
}
 
// --------------------------------------------------------------------------------------------------------
void KFileNameValueObject::addToWidget ( KWidgetArray * widgetArray )
{
    KWidgetArray * valueWidget = new KWidgetArray ();
    valueWidget->addChild (new KLabel(value_name));
    string filename = getProviderValue();
    KFileNameField * filenameField = new KFileNameField ("");
    filenameField->setTextCols(25);
    filenameField->KWidget::flags[KDL_FILENAMEFIELD_FLAG_OPEN_FILE_MODE]  = open_files_only;
    filenameField->KWidget::flags[KDL_FILENAMEFIELD_FLAG_SELECT_DIR_MODE] = select_directories;
    filenameField->KWidget::flags[KDL_WIDGET_FLAG_FILL_X] = true;
    filenameField->setText(filename);
    valueWidget->addChild (filenameField);
    widgetArray->getWindow()->addPickable (filenameField);
    filenameField->addReceiverCallback(this, (KSetStringPtr)&KFileNameValueObject::setReceiverValue);
    filenameField->addReceiverCallback(this, (KSetStringPtr)&KFileNameValueObject::selectedFileChanged, 
                                                        KDL_NOTIFICATION_TYPE_SELECTED_FILE_CHANGED);
    widgetArray->addChild (valueWidget);
    
    notifyReceivers(filenameField, KDL_NOTIFICATION_TYPE_FILENAMEFIELD_ACTIVATED);
}

