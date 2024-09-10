CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -O3
LDFLAGS ?= 

PREFIX ?= 

MKDIR ?= mkdir

BUILD ?= build

SRC := src
UTILS := src/utils
COMMANDS := src/commands

SRC_FILES = $(wildcard $(SRC)/*.cpp)
UTIL_FILES = $(wildcard $(UTILS)/*.cpp)
COMMAND_FILES = $(wildcard $(COMMANDS)/*.cpp)

SRC_OBJ = $(patsubst $(SRC)/%.cpp,$(BUILD)/src/%.o,$(SRC_FILES))
UTIL_OBJ = $(patsubst $(UTILS)/%.cpp,$(BUILD)/utils/%.o,$(UTIL_FILES))
COMMAND_OBJ = $(patsubst $(COMMANDS)/%.cpp,$(BUILD)/commands/%.o,$(COMMAND_FILES))

aspm: $(SRC_OBJ) $(UTIL_OBJ) $(COMMAND_OBJ)
	$(CXX) $(LDFLAGS) -o $(PREFIX)$@ $^

$(BUILD)/src/%.o: $(SRC)/%.cpp
	@$(MKDIR) -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/utils/%.o: $(UTILS)/%.cpp
	@$(MKDIR) -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/commands/%.o: $(COMMANDS)/%.cpp
	@$(MKDIR) -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -r build
	rm aspm
