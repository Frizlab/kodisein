
#import <SDL.h>
#import "main.h"
#import "KMain.h"
#import "KController.h"
#import <sys/param.h> // for MAXPATHLEN 
#import <unistd.h>    // chdir

static int    gArgc;
static char  **gArgv;

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
@implementation SDLApplication
// invoked from the Quit menu item 
- (void)terminate:(id)sender
{
    // post a SDL_QUIT event 
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
}
@end

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
// the main class of the application, the application's delegate 
@implementation SDLMain

// --------------------------------------------------------------------------------------------------------
// set the working directory to the .app's directory 
- (void) setupWorkingDirectory
{
    char parentdir[MAXPATHLEN];
    char *c;
    
    strncpy ( parentdir, gArgv[0], sizeof(parentdir) );
    c = (char*) parentdir;

    while (*c != '\0')     // go to end 
        c++;
    
    while (*c != '/')      // back up to parent 
        c--;
    
    *c++ = '\0';           // cut off last part (binary name) 
  
    assert ( chdir (parentdir) == 0 );   // chdir to the binary app's parent 
    assert ( chdir ("../../../") == 0 ); // chdir to the .app's parent 
}

// --------------------------------------------------------------------------------------------------------
// called when the user double clicked an kodisein project or texture set file
- (BOOL) application:(NSApplication *)theApplication openFile:(NSString *)filename
{
    SDL_Event user_event; 
    char * buffer = (char*)malloc(MAXPATHLEN+1);

    user_event.type = SDL_USEREVENT;
    user_event.user.code  = KDL_NOTIFICATION_TYPE_APPLICATION_OPEN_FILE;
    user_event.user.data1 = strncpy(buffer, [filename cString], MAXPATHLEN);
    SDL_PushEvent(&user_event);

    return YES;
}

// --------------------------------------------------------------------------------------------------------
// the applications internal event loop is about to start running 
- (void) applicationWillFinishLaunching: (NSNotification *) note
{
    // set the working directory to the .app's parent directory 
    [self setupWorkingDirectory];

    // initialize SDL here, so we can send events in case of a openFile notification
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stderr, "couldn't initialize SDL video: %s\n", SDL_GetError());
        exit(-2);
    }
}

// --------------------------------------------------------------------------------------------------------
// the applications internal event loop has just started running 
- (void) applicationDidFinishLaunching: (NSNotification *) note
{
    int status;

    // hand off to main application code 
    status = SDL_main (gArgc, gArgv);

    exit(status);
}
@end

#ifdef main
#undef main
#endif

// --------------------------------------------------------------------------------------------------------
// Main entry point to executable - should *not* be SDL_main! 
int main(int argc, char *argv[])
{
    int i;
    
    gArgc = argc;
    gArgv = (char**) malloc (sizeof(*argv) * gArgc+2);
    assert (gArgv != NULL);
    for (i = 0; i < argc; i++)
    {
        gArgv[i] = argv[i];
    }
    gArgv[i] = NULL;

    [SDLApplication poseAsClass:[NSApplication class]];
    NSApplicationMain(argc, argv);

    return 0;
}

