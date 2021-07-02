# em_generateur

em_generateur is a world generator made in C++. More information is available in
the doc folder.

## How to build

em_generateur comes with three different interfaces, with three different ways
to compile. Since the graphical part and the logical part of the application is
divided, the result is the same accross the different interfaces, only the way
it is shown changes. For additional information about compiling, see the
comments in the provided makefile.

### Qt-based graphical desktop interface

This is the default interface. It requires Qt5Quick to compile and run. The
makefile uses pkgconf to retrieve the flags to be used.

### Console desktop interface

This is the simplest interface, it only features a REPL to be run on a terminal.
Its only dependency is the standard library. Use CONSOLE=1 switch to compile
using the makefile.

### Emscripten web interface

This is the interface that compiles to WebAssembly using emscripten to make a
webpage executable on a browser. Use WEB=1 switch to compile using the makefile.

## Dependencies

In addition to their own dependencies, all the interfaces depend on libasprintf
(for the gnu::autosprintf class), and eventually on libintl for localization.
It should work out of the box when targeting Linux systems (for example, you
only need the gettext package on Arch Linux and the libc-dev and libasprintf-dev
packages on Ubuntu).

It gets a bit harder when compiling for Windows (with MinGW) and for WebAssembly
(with Emscripten). Neither provides libasprintf as far as I know, so you will
probably have to compile it yourself. MinGW32 doesn't provide libintl either so
you will have to compile it too, while Emscripten provides a buggy libintl
implementation which crashes when reading mo files (see
https://github.com/emscripten-core/emscripten/issues/9085), so I would advise
you to compile and use the GNU libintl implementation instead. Both libasprintf
and libintl are available for downloading here:
https://savannah.gnu.org/projects/gettext. To use them after
compiling/installing, don't forget to add -lintl (for MinGW32) or -lgnuintl
(to override Emscripten's libintl implementation).
