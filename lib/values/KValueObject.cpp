/*
 *  KValueObject.cpp
 *  kodisein
 */

#pragma warning(disable:4786)

#include "KValueObject.h"

KDL_CLASS_INTROSPECTION_2 (KValueObject, KObject, KNotificationObject)

// --------------------------------------------------------------------------------------------------------
KValueObject::KValueObject ( const string & n ) : KObject (), KNotificationObject ()
{
    value_name = n;
}
