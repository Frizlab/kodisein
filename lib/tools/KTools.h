/*
 *  KTools.h
 *  kodisein
 */

#ifndef __KTools
#define __KTools

#pragma warning(disable:4786)

#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <SDL_video.h>

#include "KVector.h"

using namespace std;

void 		kDisplayString		( const string &, const KPosition &, bool = true );
void 		kDisplayString		( const string &, const KVector &, void * );
int		kDisplayXPMIcon		( char ** xpmData, const KPosition & pos );
void		kDisplayWireSphere	( float radius, int subdivisions );
void		kDisplaySolidSphere	( float radius, int subdivisions );
void		kDisplaySolidCylinder	( float base, float top, float height, int subdivisions );

extern SDL_PixelFormat KDL_PIXEL_FORMAT;

// --------------------------------------------------------------------------------------------------------
#define RECTANGLE_XY(minx, maxx, miny, maxy, z) {	glNormal3f(0.0, 0.0, 1.0); \
                                                        glVertex3f(maxx, maxy, z); \
                                                        glVertex3f(minx, maxy, z); \
                                                        glVertex3f(minx, miny, z); \
                                                        glVertex3f(maxx, miny, z); }
#define RECTANGLE_YX(minx, maxx, miny, maxy, z) {	glNormal3f(0.0,  0.0, -1.0); \
                                                        glVertex3f(maxx, maxy, z); \
                                                        glVertex3f(maxx, miny, z); \
                                                        glVertex3f(minx, miny, z); \
                                                        glVertex3f(minx, maxy, z); }

#define RECTANGLE_XZ(minx, maxx, minz, maxz, y) {	glNormal3f(0.0, -1.0, 0.0); \
                                                        glVertex3f(maxx, y, maxz); \
                                                        glVertex3f(minx, y, maxz); \
                                                        glVertex3f(minx, y, minz); \
                                                        glVertex3f(maxx, y, minz); }
#define RECTANGLE_ZX(minx, maxx, minz, maxz, y) {	glNormal3f(0.0, 1.0, 0.0); \
                                                        glVertex3f(maxx, y, maxz); \
                                                        glVertex3f(maxx, y, minz); \
                                                        glVertex3f(minx, y, minz); \
                                                        glVertex3f(minx, y, maxz); }
                                                        
#define RECTANGLE_ZY(miny, maxy, minz, maxz, x) {	glNormal3f(-1.0, 0.0, 0.0); \
                                                        glVertex3f(x, maxy, maxz); \
                                                        glVertex3f(x, maxy, minz); \
                                                        glVertex3f(x, miny, minz); \
                                                        glVertex3f(x, miny, maxz); }
#define RECTANGLE_YZ(miny, maxy, minz, maxz, x) {	glNormal3f(1.0, 0.0, 0.0); \
                                                        glVertex3f(x, maxy, maxz); \
                                                        glVertex3f(x, miny, maxz); \
                                                        glVertex3f(x, miny, minz); \
                                                        glVertex3f(x, maxy, minz); }

// --------------------------------------------------------------------------------------------------------
#define CLASS_NAME \
    private: \
    static   const string class_name; \
    public: \
    virtual  const string & getName() const { return class_name; } \
    static   const string & name()          { return class_name; } \
    private: \

#define CLASS_NAME_NAME(className, name) \
    const string className::class_name(name); \

// --------------------------------------------------------------------------------------------------------
#ifdef WIN32
#define OBJECT_ID \
    private: \
    long object_id; \
    void	setObjectId(long i) { object_id = i; } \
    void	initObjectId() { object_id = time(NULL) + rand(); } \
    public: \
    long 	getObjectId() const { return object_id; } \
    private:
#else
#define OBJECT_ID \
    private: \
    long object_id; \
    void	setObjectId(long i) { object_id = i; } \
    void	initObjectId() { object_id = time(NULL) + random(); } \
    public: \
    long 	getObjectId() const { return object_id; } \
    private:
#endif

#endif