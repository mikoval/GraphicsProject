CC := g++  -std=c++11
RAYTRACER_EXEC ?= raytracer
RASTERIZER_EXEC ?= rasterizer 
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
INCLUDE_DIRS ?= ./include

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS :=  ./include ./include/Common ./include/Rasterizer
INC_FLAGS := $(addprefix -I,$(INC_DIRS))


LIB := -lm -lglfw -lassimp -framework OpenGL
INC :=  -I -Iinclude -I/usr/local/include -I/opt/X11/include

RAYRACER_OBJS := $(filter-out ./build/./src/Rasterizer.cpp.o, $(OBJS))
RASTERIZER_OBJS := $(filter-out ./build/./src/Raytracer.cpp.o, $(OBJS))

$(info    VAR is $(RAYRACER_OBJS))

$(info    VAR is $())


all: $(RASTERIZER_EXEC) $(RAYTRACER_EXEC)

CPPFLAGS ?= $(INC_FLAGS) -Wno-deprecated-declarations -Wall -Wpedantic 

$(RASTERIZER_EXEC): $(RASTERIZER_OBJS)
	$(CC) $(RASTERIZER_OBJS) -o $@ $(LDFLAGS)  $(LIB) $(INC)

$(RAYTRACER_EXEC): $(RAYRACER_OBJS)
	$(CC) $(RAYRACER_OBJS) -o $@ $(LDFLAGS)  $(LIB) $(INC)


# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
