/*
 *  KFileNameValueObject.h
 *  kodisein
 */

#ifndef __KFileNameValueObject
#define __KFileNameValueObject

#include "KStringValueObject.h"

class KFileNameValueObject : public KStringValueObject
{
    INTROSPECTION

    protected:
    
    bool		open_files_only;
    bool		select_directories;

    public:
                        KFileNameValueObject 	( const string & = "filename", bool = false, bool = false );

    void 		selectedFileChanged 	( const string & );
    void		addToWidget		( KWidgetArray * );
};

#endif