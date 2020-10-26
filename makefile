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
includes := $(sources:src/%.cpp=%.d)

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
	rm -f *.exe *.js *.wasm *.d
	rm -rf obj

%.d: src/%.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(obj_dir)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(includes)

#Prerequisites are generated in the above includes
$(obj_dir)/%.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
