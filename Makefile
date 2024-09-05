CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Wconversion
LDFLAGS ?= 

PREFIX ?= 

MKDIR ?= mkdir

BUILD ?= build

SRC := src
LIB := src/lib

SRC_FILES = $(wildcard $(SRC)/*.cpp)
LIB_FILES = $(wildcard $(LIB)/*.cpp)

SRC_OBJ = $(patsubst $(SRC)/%.cpp,$(BUILD)/src/%.o,$(SRC_FILES))
LIB_OBJ = $(patsubst $(LIB)/%.cpp,$(BUILD)/lib/%.o,$(LIB_FILES))

aspm: $(SRC_OBJ) $(LIB_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD)/src/%.o: $(SRC)/%.cpp
	@$(MKDIR) -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $(PREFIX)$@ $<

$(BUILD)/lib/%.o: $(LIB)/%.cpp
	@$(MKDIR) -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $(PREFIX)$@ $<

.PHONY: clean

clean:
	rm -r build
	rm aspm
