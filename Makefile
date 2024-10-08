# Project Configuration
EXE ?= web_server 
SRC_DIR ?= src
BUILD_DIR ?= build
LIB_DIR ?= lib
INC_DIR ?= include $(BUILD_DIR)/views /usr/include/jsoncpp
VIEW_DIR ?= views
DIR = $(shell pwd)

# C++ configuration
PRODFLAG=-D_PROD
override CPPFLAGS +=-MMD -MP

OPTFLAGS ?=-Ofast -flto
override CXXFLAGS +=-std=c++17 $(addprefix -I,$(INC_DIR)) $(OPTFLAGS)

override LIBS := $(shell dir $(LIB_DIR)/* 2>/dev/null)

override LDLIBS +=-L$(LIB_DIR) -L/usr/local/lib64
override LDFLAGS += -lssl -lcrypto -lossp-uuid -pthread -ldrogon -ltrantor -ljsoncpp -lz -ldl

# Static Configuration
override SRCS := $(shell dir $(SRC_DIR)/*.cpp)
override OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
override VIEWS := $(shell dir $(VIEW_DIR)/*.csp)
override VIEW_OBJS := $(patsubst %.csp,$(BUILD_DIR)/%.cc,$(VIEWS))
override TARGET := $(BUILD_DIR)/$(EXE)
override DEPS := $(OBJS:.o=.d)

$(TARGET): $(OBJS) $(VIEW_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

$(OBJS): $(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(PRODFLAG) $(CPPFLAGS) -c $< -o $@

$(VIEW_OBJS): $(BUILD_DIR)/%.cc: %.csp
	@mkdir -p $(@D)
	dg_ctl create view $< -o $(@D)

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
