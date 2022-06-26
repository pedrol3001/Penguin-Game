EXEC = game

COMPILER = g++
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@
INC_PATHS = -I$(INC_PATH) $(addprefix -I,$(SDL_INC_PATH))

FLAGS = -std=c++11 -Wall
DFLAGS = -ggdb -O0 -DDEBUG
RFLAGS = -O3 -mtune=native

INC_PATH = include
SRC_PATH = src
DEP_PATH = dep
BIN_PATH = bin

FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
INC_FILES = $(wildcard $(INC_PATH)/*.h)
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d,$(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))


folders:
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)

all: $(EXEC)

debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

clean:
	-rm -rdf $(DEP_PATH)
	-rm -rdf $(BIN_PATH)
	-rm -f $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INC_PATHS) $(addprefix $(SRC_PATH)/,$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)

.SECONDEXPANSION:
	-include $$(DEP_FILES)

.PRECIOUS: $(DEP_FILES)
.PHONY: clean folders debug
