/*
 *  KKeyHandler.h
 *  kodisein
 */

#ifndef __KKeyHandler
#define __KKeyHandler

#include "KNotificationObject.h"
#include <vector>

using namespace std;

struct KKey;

enum { KDL_KEYHANDLER_FLAG_BLOCKABLE, KDL_KEYHANDLER_FLAG_END };

// --------------------------------------------------------------------------------------------------------
class KKeyHandler : public KNotificationObject
{
    INTROSPECTION

    public:

    vector<bool>	flags;
    
                        KKeyHandler	();

    virtual bool	handleKey	( const KKey & ) = 0;
};

#endif

