### How to use

## Rules

# all: Default rule, build the target
# run: Run the target. If WEB == 0, execute the generated executable else launch the webpage using emrun.
# clean: Delete all files related to the building, *.exe, *.js, *.wasm and *.o

## Variables

# WEB: if not 0, build/run web target using emscripten
# CONSOLE: if not 0, build/run the console interface
# If neither WEB nor CONSOLE is defined, the Qt-based desktop interface is built/run
# DEBUG: if 1, build for debugging (keep debug info), else build for release (optimize)
# TARGET: name of the generated executable (if WEB != 0, make sure that the name either ends with .wasm, .js or .html)
# CXX: compiler to be used.
# CXXFLAGS: additional flags to be passed to the compiler (the hardcoded flags takes priority though)
# LDFLAGS: additional flags to be passed to the compiler at linking time
# LIBS: additional libs to be linked against

### Variables

override CXXFLAGS += -Wall -Wextra -Wshadow -Werror

DEBUG ?= 0
ifeq ($(DEBUG),0)
	override CXXFLAGS += -O2
endif

override CXXFLAGS += -std=c++11

WEB ?= 0
CONSOLE ?= 0
QT ?= 0
ifeq ($(WEB),0)
	ifeq ($(CONSOLE),0)
		QT = 1
	endif
endif
ifneq ($(WEB),0)
	obj_dir = obj/web
	CXX = em++
	TARGET = index.html
	override LDFLAGS += --emrun --bind
else
	CXX ?= g++
	ifneq ($(DEBUG),0)
		override CXXFLAGS += -g
	endif
	ifneq ($(CONSOLE),0)
		obj_dir = obj/console
		TARGET = generateur-console
	else
		obj_dir = obj/qt
		override GENERAL_CFLAGS = $(shell pkgconf --cflags Qt5Quick)
		override CXXFLAGS += -fPIC
		override LIBS += $(shell pkgconf --libs Qt5Quick)
		TARGET = generateur-qt
	endif
endif
override GENERAL_CFLAGS += -DWEB=$(WEB) -DCONSOLE=$(CONSOLE) -DQT=$(QT)
override CXXFLAGS += $(GENERAL_CFLAGS)
MOCFLAGS = $(GENERAL_CFLAGS)

$(shell mkdir -p $(obj_dir))

sources := $(wildcard src/*.cpp)
ifneq ($(QT),0)
	sources += src/moc_Backend.cpp
endif
objs := $(sources:src/%.cpp=$(obj_dir)/%.o)


### Rules

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(objs)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
ifeq ($(WEB),0)
    ifeq ($(DEBUG),0)
	strip $@
    endif
endif

$(obj_dir)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(TARGET)
ifeq ($(WEB),0)
	- ./$^
else
	- emrun $(TARGET)
endif

clean:
	rm -f *.exe *.js *.wasm generateur-*
	rm -rf obj

ifneq ($(QT),0)
src/moc_%.cpp: src/%.h
	moc $(MOCFLAGS) $< -o $@

$(obj_dir)/Backend.o: src/Backend.moc

src/Backend.moc: src/Backend.cpp
	moc $(MOCFLAGS) -i $< -o $@
endif
