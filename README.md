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
Its only dependancy is the standard library. Use CONSOLE=1 switch to compile
using the makefile.

### Emscripten web interface

This is the interface that compiles to WebAssembly using emscripten to make a
webpage executable on a browser. Use WEB=1 switch to compile using the makefile.
