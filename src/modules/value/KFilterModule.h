/*
 *  KFilterModule.h
 *  kodisein
 */

#ifndef __KFilterModule
#define __KFilterModule

#include "KValueModule.h"

enum {	FILTER_INVERT, FILTER_ATTACK, FILTER_DECAY };

class KModuleInspector;

// --------------------------------------------------------------------------------------------------------
class KFilterModule : public KValueModule
{
    INTROSPECTION
    
    float		pos, length;
    int			filter_type;
    bool		smooth;
    
    protected:
    
    void		createConnectors	();
    
    public:
    
                        KFilterModule		( int );
    
    void		setStartPos		( float s ) { pos = s; }
    void		setLength		( float l ) { length = l; }
    void		setSmooth		( bool s )  { smooth = s; }
    float		getStartPos		() const { return pos; }
    float		getLength		() const { return length; }
    bool		getSmooth		() const { return smooth; }
    
    virtual void	displayConnectors	( int );
    virtual float	getValue		() const;
    virtual void	initInspector 		( KModuleInspector * );
    void 		addToWidget		( KWidgetArray *, int = 0 );
};

// --------------------------------------------------------------------------------------------------------
class KModuleInvert : public KFilterModule
{
    KDS_MODULE_HEADER
    
    public:    
                        KModuleInvert 		() : KFilterModule (FILTER_INVERT) {}
};

// --------------------------------------------------------------------------------------------------------
class KModuleAttack : public KFilterModule
{
    KDS_MODULE_HEADER
    
    public:    
                        KModuleAttack		() : KFilterModule (FILTER_ATTACK) {}
};

// --------------------------------------------------------------------------------------------------------
class KModuleDecay : public KFilterModule
{
    KDS_MODULE_HEADER
    
    public:    
                        KModuleDecay 		() : KFilterModule (FILTER_DECAY) {}
};

#endif

