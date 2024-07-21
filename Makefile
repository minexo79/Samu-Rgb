# set arch is arm
ARCH = arm

# project name
PROJECT = samu_rgb

# set cross compile is aarch64-none-linux-gnu-
CROSS_COMPILE = aarch64-none-linux-gnu-
COMPILE_FLAG = -Og -Wall -static
COMPILE_LIBS = -lpthread -lm -lrt

SRCS = $(wildcard src/*.cpp) 			# Assuming your source files are in the current directory and have a .c extension
INCS = $(wildcard include/*.h) 			# Assuming your header files are in the current directory and have a .h extension
OBJS := $(SRCS:%.cpp=build/%.o)			# Transform the source file names into object file names within the build directory

# set compiler and strip
CC = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip

all: build/${PROJECT}

clean:
	rm -rf  build/samu_rgb build/samu_rgb_rel build/src/*.o build/src

build/${PROJECT}: $(OBJS)
	${CC} $(COMPILE_FLAG) -o $@ $^ $(COMPILE_LIBS)
	$(STRIP) $@ -o build/${PROJECT}_rel

build/%.o: %.cpp
	mkdir -p build build/src
	${CC} $(COMPILE_FLAG) -o $@ -c $< $(COMPILE_LIBS)

# include $(INCS)