### How to use

## Rules

# all: Default rule, build the target
# run: Run the target. If WEB == 0, execute the generated executable, if WEB == 1, launch main.html using emrun.
# clean: Delete all files related to the building, *.exe, *.js, *.wasm and *.o

## Variables

# WEB: if 1, build/run web target using emscripten, else build/run desktop target
# CXX: compiler to be used. Forced to em++ if WEB == 1
# FLAGS: additional flags to be passed to the compiler (the hardcoded flags takes priority though)
# DEBUG: if 1, build for debugging (keep debug info), else build for release (optimize)

### Variables

override CXXFLAGS += -Wall -Wextra -Wshadow -Werror

DEBUG ?= 0
ifeq ($(DEBUG),0)
	override CXXFLAGS += -O2
endif

override CXXFLAGS += -std=c++11

WEB ?= 0
ifeq ($(WEB),1)
	obj_dir = obj/web
	CXX = em++
else
	obj_dir = obj/desktop
	CXX ?= g++
	ifeq ($(DEBUG),1)
		override CXXFLAGS += -g -Og
	endif
endif
override CXXFLAGS += -DWEB=$(WEB)

$(shell mkdir -p $(obj_dir))

sources := $(wildcard src/*.cpp)
objs := $(sources:src/%.cpp=$(obj_dir)/%.o)

### Rules

.PHONY: all run clean

all: main main.html


main: $(objs)
ifeq ($(WEB),0)
	$(CXX) $(CXXFLAGS) -o $@ $^
ifeq ($(DEBUG),0)
	strip $@
endif
endif

main.js main.html: $(objs)
ifeq ($(WEB),1)
	$(CXX) $(CXXFLAGS) --emrun --bind -o $@ $^
endif

ifeq ($(WEB),0)
run: main
	./$^
else
run: main.js
	- emrun main.html
endif

clean:
	rm -f *.exe *.js *.wasm
	rm -rf obj

.SECONDEXPANSION:

# The prerequisites are the .cpp source file and all included .h files.
$(obj_dir)/%.o: src/%.cpp $$(addprefix src/,$$(shell sed -n 's/^ *\# *include *"\(.*\)"/\1/p' src/$$*.cpp))
	$(CXX) $(CXXFLAGS) -c -o $@ $<
