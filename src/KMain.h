/*
 *  KMain.h
 *  kodisein
 */
 
#ifndef __KMain
#define __KMain

#ifdef __cplusplus
#define C_LINKAGE	"C"
#else
#define C_LINKAGE
#endif /* __cplusplus */

extern C_LINKAGE int SDL_main (int argc, char* argv[]);

#endif