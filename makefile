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
# LOCALIZE: if not 0, enable localization (requires a *working* libintl implementation)
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
else
	override CXXFLAGS += -g
endif

override CXXFLAGS += -std=c++11

override LIBS += -lasprintf

LOCALIZE ?= 1
WEB ?= 0
CONSOLE ?= 0
QT ?= 0
ifeq ($(WEB),0)
	ifeq ($(CONSOLE),0)
		QT = 1
	endif
endif
ifneq ($(WEB),0)
	target_type = web
	CXX = em++
	TARGET = index.js
	override LDFLAGS += --emrun --bind
	ifneq ($(LOCALIZE),0)
		override LDFLAGS += --preload-file mo
	endif
else
	CXX ?= g++
	ifneq ($(CONSOLE),0)
		target_type = console
		TARGET = generateur-console
	else
		target_type = qt
		override GENERAL_CFLAGS = $(shell pkgconf --cflags Qt5Quick)
		override CXXFLAGS += -fPIC
		override LIBS += $(shell pkgconf --libs Qt5Quick)
		TARGET = generateur-qt
	endif
	ifneq ($(findstring -w64-mingw32-,$(CXX)),)
		TARGET := $(TARGET).exe
	endif
endif
override GENERAL_CFLAGS += -DWEB=$(WEB) -DCONSOLE=$(CONSOLE) -DQT=$(QT) -DLOCALIZE=$(LOCALIZE)
override CXXFLAGS += $(GENERAL_CFLAGS)
MOCFLAGS = $(GENERAL_CFLAGS)

obj_dir = obj/$(lastword $(CXX))-$(target_type)
$(shell mkdir -p $(obj_dir))

sources := $(wildcard src/*.cpp)
deps := $(sources:src/%.cpp=deps/%.d)
ifneq ($(QT),0)
	sources += src/moc_Backend.cpp
endif
objs := $(sources:src/%.cpp=$(obj_dir)/%.o)

ifneq ($(LOCALIZE),0)
	pos := $(wildcard po/*.po)
	mos := $(pos:po/%.po=mo/%/LC_MESSAGES/generateur.mo)
endif

### Rules

.PHONY: all run clean

all: $(mos) $(TARGET)

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
	- emrun $(TARGET:%.js=%.html)
endif

clean:
	rm -f *.exe *.js *.wasm generateur-*
	rm -rf obj deps mo

ifneq ($(QT),0)
src/moc_%.cpp: src/%.h
	moc $(MOCFLAGS) $< -o $@

$(obj_dir)/Backend.o: src/Backend.moc

src/Backend.moc: src/Backend.cpp
	moc $(MOCFLAGS) -i $< -o $@
endif

# When using -j and if the line of the message change in the source file, the
# location information gets duplicated. the sed script removes the old location
# information and keeps only the most recent one.
po/%.po: $(sources)
	xgettext -k_ -c~ $$([ -w $@ ] && echo "-j") -o $@ src/*.cpp
	sed -i "s/#:.* \(.*\)/#: \1/" $@

mo/%/LC_MESSAGES/generateur.mo: po/%.po
	@ mkdir -p mo/$*/LC_MESSAGES
	msgfmt -c -o $@ $<

deps/%.d: src/%.cpp
	@ mkdir -p deps
	$(CXX) $(CXXFLAGS) -DQT=0 -MM -MT '$$(obj_dir)/$*.o $@' -o $@ $<

include $(deps)
