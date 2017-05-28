# kodisein
Migrated from http://kodisein.sourceforge.net (not mine).

## Compilation Tests on macOS
The original Xcode proj is too old and cannot be opened anymore.

I went in the linux folder and typed `make`. Fixed a few compilation errors, then launched the executable. Segfault. Maybe because I had to remove a functionality to make app compile with 64bits inodes enabled… 🤔 Anyway I tried a different strategy.

The original Xcode project file was too old… I created a new, recent one! And it worked. Tested on macOS Sierra, with Xcode 8.
You'll have to install the libSDL and libSDL_Image (eg. `brew install sdl sdl_image`) before running the project, but that should be all.
