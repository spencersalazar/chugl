
# chugin name
CHUGIN_NAME=chugl

# all of the c/cpp files that compose this chugin
C_MODULES=
CXX_MODULES=chugl.cpp chugl_opengl.cpp chugl_api.cpp util_opengl.cpp \
    chugl_ix.cpp chugl_motion.cpp
OBJCXX_MODULES=

# where the chuck headers are
CK_SRC_PATH?=chuck/src/


# ---------------------------------------------------------------------------- #
# you won't generally need to change anything below this line for a new chugin #
# ---------------------------------------------------------------------------- #

# default target: print usage message and quit
current: 
	@echo "[chuck build]: please use one of the following configurations:"
	@echo "   make linux, make osx, or make win32"

ifneq ($(CK_TARGET),)
.DEFAULT_GOAL:=$(CK_TARGET)
ifeq ($(MAKECMDGOALS),)
MAKECMDGOALS:=$(.DEFAULT_GOAL)
endif
endif

.PHONY: osx linux linux-oss linux-jack linux-alsa win32
osx linux linux-oss linux-jack linux-alsa: all

win32:
	make -f makefile.win32

CC=gcc
CXX=g++
OBJCXX=g++
LD=g++

CHUGIN_PATH=/usr/local/lib/chuck

ifneq (,$(strip $(filter osx bin-dist-osx,$(MAKECMDGOALS))))
include makefile.osx
endif

ifneq (,$(strip $(filter linux,$(MAKECMDGOALS))))
include makefile.linux
endif

ifneq (,$(strip $(filter linux-oss,$(MAKECMDGOALS))))
include makefile.linux
endif

ifneq (,$(strip $(filter linux-jack,$(MAKECMDGOALS))))
include makefile.linux
endif

ifneq (,$(strip $(filter linux-alsa,$(MAKECMDGOALS))))
include makefile.linux
endif

FLAGS+=-I.

ifneq ($(CHUCK_DEBUG),)
FLAGS+= -g
else
FLAGS+= -O3
endif

ifneq ($(CHUCK_STRICT),)
FLAGS+= -Werror
endif



# default: build a dynamic chugin
CK_CHUGIN_STATIC?=0

ifeq ($(CK_CHUGIN_STATIC),0)
SUFFIX=.chug
else
SUFFIX=.schug
FLAGS+= -D__CK_DLL_STATIC__
endif

C_OBJECTS=$(addsuffix .o,$(basename $(C_MODULES)))
CXX_OBJECTS=$(addsuffix .o,$(basename $(CXX_MODULES)))
OBJCXX_OBJECTS=$(addsuffix .o,$(basename $(OBJCXX_MODULES)))
OBJS=$(C_OBJECTS) $(CXX_OBJECTS) $(OBJCXX_OBJECTS)

CHUG=$(addsuffix $(SUFFIX),$(CHUGIN_NAME))

all: $(CHUG)

$(CHUG): $(OBJS)
ifeq ($(CK_CHUGIN_STATIC),0)
	$(LD) $(LDFLAGS) -o $@ $^
else
	ar rv $@ $^
	ranlib $@
endif

chugl_opengl.o: chugl.h

$(C_OBJECTS): %.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

$(CXX_OBJECTS): %.o: %.cpp $(CK_SRC_PATH)/chuck_dl.h
	$(CXX) $(FLAGS) -c -o $@ $<

$(OBJCXX_OBJECTS): %.o: %.mm $(CK_SRC_PATH)/chuck_dl.h
	$(OBJCXX) $(FLAGS) -c -o $@ $<

chugl_opengl.cpp: OpenGL/gl.xml ck.py genchugin.py
	PYTHONPATH="PYTHONPATH:OpenGL" python genchugin.py

install: $(CHUG)
	mkdir -p $(CHUGIN_PATH)
	cp $^ $(CHUGIN_PATH)
	chmod 755 $(CHUGIN_PATH)/$(CHUG)

clean: 
	rm -rf $(OBJS) $(CHUG) *.o Release Debug chugl_opengl.cpp

