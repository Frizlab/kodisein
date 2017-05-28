
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

/* For some reaon, Apple removed setAppleMenu from the headers in 10.4,
 but the method still is there and works. To avoid warnings, we declare
 it ourselves here. */
@interface NSApplication(SDL_Missing_Methods)
- (void)setAppleMenu:(NSMenu *)menu;
@end

static NSString *getApplicationName(void)
{
    NSDictionary *dict;
    NSString *appName = 0;
    
    /* Determine the application name */
    dict = (NSDictionary *)CFBundleGetInfoDictionary(CFBundleGetMainBundle());
    if (dict)
        appName = [dict objectForKey: @"CFBundleName"];
    
    if (![appName length])
        appName = [[NSProcessInfo processInfo] processName];
    
    return appName;
}

static void setApplicationMenu(void)
{
    /* warning: this code is very odd */
    NSMenu *appleMenu;
    NSMenuItem *menuItem;
    NSString *title;
    NSString *appName;
    
    appName = getApplicationName();
    appleMenu = [[NSMenu alloc] initWithTitle:@""];
    
    /* Add menu items */
    title = [@"About " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    title = [@"Hide " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(hide:) keyEquivalent:@"h"];
    
    menuItem = (NSMenuItem *)[appleMenu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
    [menuItem setKeyEquivalentModifierMask:(NSAlternateKeyMask|NSCommandKeyMask)];
    
    [appleMenu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    title = [@"Quit " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];
    
    
    /* Put menu into the menubar */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:appleMenu];
    [[NSApp mainMenu] addItem:menuItem];
    
    /* Tell the application object that this is now the application menu */
    [NSApp setAppleMenu:appleMenu];
}

/* Create a window menu */
static void setupWindowMenu(void)
{
    NSMenu      *windowMenu;
    NSMenuItem  *windowMenuItem;
    NSMenuItem  *menuItem;
    
    windowMenu = [[NSMenu alloc] initWithTitle:@"Window"];
    
    /* "Minimize" item */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"Minimize" action:@selector(performMiniaturize:) keyEquivalent:@"m"];
    [windowMenu addItem:menuItem];
    
    /* Put menu into the menubar */
    windowMenuItem = [[NSMenuItem alloc] initWithTitle:@"Window" action:nil keyEquivalent:@""];
    [windowMenuItem setSubmenu:windowMenu];
    [[NSApp mainMenu] addItem:windowMenuItem];
    
    /* Tell the application object that this is now the window menu */
    [NSApp setWindowsMenu:windowMenu];
}

/* Replacement for NSApplicationMain */
static void CustomApplicationMain (int argc, char **argv)
{
    SDLMain				*sdlMain;
    
    /* Ensure the application object is initialised */
    [SDLApplication sharedApplication];
    
#ifdef SDL_USE_CPS
    {
        CPSProcessSerNum PSN;
        /* Tell the dock about us */
        if (!CPSGetCurrentProcess(&PSN))
            if (!CPSEnableForegroundOperation(&PSN,0x03,0x3C,0x2C,0x1103))
                if (!CPSSetFrontProcess(&PSN))
                    [SDLApplication sharedApplication];
    }
#endif /* SDL_USE_CPS */
    
    /* Set up the menubar */
    [NSApp setMainMenu:[[NSMenu alloc] init]];
    setApplicationMenu();
    setupWindowMenu();
    
    /* Create SDLMain and make it the app delegate */
    sdlMain = [[SDLMain alloc] init];
    [NSApp setDelegate:sdlMain];
    
    /* Start the main event loop */
    [NSApp run];
}

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

    CustomApplicationMain(argc, argv);
    
    return 255; /* Never reached. */
}
