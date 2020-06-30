CC := g++  -std=c++11
RAYTRACER_EXEC ?= raytracer
RASTERIZER_EXEC ?= rasterizer 
PONG_EXEC ?= pong
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
INCLUDE_DIRS ?= ./include

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS :=  ./include ./include/Common ./include/Rasterizer
INC_FLAGS := $(addprefix -I,$(INC_DIRS))


LIB := -lm -lglfw -lassimp -lfreetype -framework OpenGL
INC :=  -I -Iinclude -I/usr/local/include -I/opt/X11/include  -I/usr/local/opt/freetype/include/freetype2


OBJS:=$(filter-out ./build/./src/main/%,$(OBJS))

RAYTRACER_OBJS := ./build/./src/main/Raytracer.cpp.o $(OBJS)
RASTERIZER_OBJS := ./build/./src/main/Rasterizer.cpp.o $(OBJS)
PONG_OBJS := ./build/./src/main/Pong.cpp.o $(OBJS)


all: $(RASTERIZER_EXEC) $(RAYTRACER_EXEC) $(PONG_EXEC)

CPPFLAGS ?= $(INC_FLAGS) -Wno-deprecated-declarations -Wall -Wpedantic 

$(RASTERIZER_EXEC): $(RASTERIZER_OBJS)
	$(CC) $(RASTERIZER_OBJS) -o $@ $(LDFLAGS)  $(LIB) $(INC)

$(RAYTRACER_EXEC): $(RAYTRACER_OBJS)
	$(CC) $(RAYTRACER_OBJS) -o $@ $(LDFLAGS)  $(LIB) $(INC)


$(PONG_EXEC): $(PONG_OBJS)
	$(CC) $(PONG_OBJS) -o $@ $(LDFLAGS)  $(LIB) $(INC)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ $(INC)


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
