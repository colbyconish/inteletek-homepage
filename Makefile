# Project Configuration
EXE ?= web_server 
SRC_DIR ?= src
BUILD_DIR ?= build
LIB_DIR ?= lib
INC_DIR ?= include
TEST_DIR ?= tests

TEST_PRE ?= test_

# C++ configuration
PRODFLAG=-D_PROD
override CPPFLAGS +=-MMD -MP

OPTFLAGS ?=-Ofast -flto
override CXXFLAGS +=-std=c++17 $(addprefix -I,$(INC_DIR)) $(OPTFLAGS)

override LIBS := $(shell dir $(LIB_DIR)/* 2>/dev/null)

override LDLIBS +=-L$(LIB_DIR) -L/usr/local/lib64
override LDFLAGS +=-ldrogon -ltrantor -ljsoncpp -lossp-uuid -lz

# Static Configuration
override SRCS := $(shell dir $(SRC_DIR)/*.cpp)
override OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
override TEST_SRCS := $(shell dir $(TEST_DIR)/*.test 2>/dev/null)
override TEST_OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
override MAIN_TEST_OBJS := $(patsubst $(BUILD_DIR)/%.o,$(BUILD_DIR)/$(TEST_PRE)%.o,$(OBJS))
override TARGET := $(BUILD_DIR)/$(EXE)
override TEST_TARGET := $(BUILD_DIR)/$(TEST_PRE)$(EXE)
override DEPS := $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

$(OBJS): $(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(PRODFLAG) $(CPPFLAGS) -c $< -o $@

.PHONY: serve
run: $(TARGET)
	$(TARGET)

.PHONY: install
install: $(TARGET)
	ln -s $(shell pwd)/$(TARGET) /usr/local/bin

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

-include $(DEPS)
