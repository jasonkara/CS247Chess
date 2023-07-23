CXX=g++
CXXFLAGS=-std=c++14 -Wall -g -MMD
BUILD_DIR=build
EXEC=$(BUILD_DIR)/chess
CCFILES=$(wildcard *.cc)
OBJECTS=$(addprefix $(BUILD_DIR)/, ${CCFILES:.cc=.o})
DEPENDS=$(addprefix $(BUILD_DIR)/, ${CCFILES:.cc=.d})

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

-include $(DEPENDS)

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	