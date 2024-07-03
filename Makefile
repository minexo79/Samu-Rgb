# set arch is arm
ARCH = arm

# project name
PROJECT = samu_rgb

# set cross compile is aarch64-none-linux-gnu-
CROSS_COMPILE = aarch64-none-linux-gnu-
COMPILE_FLAG = -Og -Wall
COMPILE_LIBS = -lpthread -lm -lrt

SRCS = $(wildcard *.cpp) 			# Assuming your source files are in the current directory and have a .c extension
OBJS := $(SRCS:%.cpp=build/%.o)  	# Transform the source file names into object file names within the build directory

# set compiler and strip
CC = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip

all: build/${PROJECT}

clean:
	rm -rf build/*.o build/vim1sgpio

build/${PROJECT}: $(OBJS)
	${CC} $(COMPILE_FLAG) -o $@ $^ $(COMPILE_LIBS)
	$(STRIP) $@ -o ${PROJECT}_rel

build/%.o: %.cpp
	mkdir -p build
	${CC} $(COMPILE_FLAG) -o $@ -c $< $(COMPILE_LIBS)