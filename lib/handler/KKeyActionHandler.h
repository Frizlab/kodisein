/*
 *  KKeyActionHandler.h
 *  kodisein
 */

#ifndef __KKeyActionHandler
#define __KKeyActionHandler

#include "KKeyHandler.h"
#include "KConsole.h"

#include <hash_map>

using namespace std;

// --------------------------------------------------------------------------------------------------------
class KKeyAction : public KNotificationObject
{
    protected:
    
    string 			key_name;
    
    public:
    
                                KKeyAction	( const string & keyName )
                                                : KNotificationObject ()
                                                { key_name = keyName; }
    virtual                    ~KKeyAction	() {}
                               
    virtual const string &	getKeyName	() const { return key_name; }
};

// --------------------------------------------------------------------------------------------------------
struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
		return strcmp(s1, s2) == 0;
  }
};

typedef hash_map<const char*, KKeyAction *, hash<const char*>, eqstr> KeyActionHash;

// --------------------------------------------------------------------------------------------------------
class KKeyActionHandler : public KKeyHandler
{
    INTROSPECTION

    protected:

    KeyActionHash	key_handlers;
    string		last_key;

    public:
    
                KKeyActionHandler	() : KKeyHandler () {}
    virtual		~KKeyActionHandler	();

    KKeyAction * getActionForSequence	( const string &, bool = false );
    bool		addSequenceCallback		( const string, KObject *, KCallbackPtr );
    bool		setSequenceCallback		( const string, KObject *, KCallbackPtr );
    void		removeSequenceCallback	( const string, KObject *, KCallbackPtr );

    bool		isSaveSequenceCallback	( const string & );

    bool		handleKey	 	( const KKey & );
};

#endif
