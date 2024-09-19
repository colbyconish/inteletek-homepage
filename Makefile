# Project Configuration
EXE ?= web_server 
SRC_DIR ?= src
BUILD_DIR ?= build
LIB_DIR ?= lib
INC_DIR ?= include /usr/include/jsoncpp
TEST_DIR ?= tests
TEST_PRE ?= test_
DIR = $(shell pwd)


# C++ configuration
PRODFLAG=-D_PROD
override CPPFLAGS +=-MMD -MP

OPTFLAGS ?=-Ofast -flto
override CXXFLAGS +=-std=c++17 $(addprefix -I,$(INC_DIR)) $(OPTFLAGS)

override LIBS := $(shell dir $(LIB_DIR)/* 2>/dev/null)

override LDLIBS +=-L$(LIB_DIR) -L/usr/local/lib64
override LDFLAGS +=-lossp-uuid -luuid -pthread -ldrogon -ltrantor -ljsoncpp -lz -ldl

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

.PHONY: link
link: $(TARGET)
	ln -fs $(DIR)/www /www
	ln -fs $(DIR)/webserver.json /etc/webserver.json
	ln -fs $(DIR)/$(TARGET) /usr/local/bin/$(EXE)
	cp webserver.service /etc/systemd/system/webserver.service
	systemctl enable webserver
	systemctl start webserver

.PHONY: install
install: $(TARGET)
	cp $(DIR)/www/* /www/
	cp $(DIR)/webserver.json /etc/webserver.json
	cp $(DIR)/$(TARGET) /usr/local/bin/$(EXE)
	cp webserver.service /etc/systemd/system/webserver.service
	systemctl enable webserver
	systemctl start webserver

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

-include $(DEPS)
