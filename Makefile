ifeq ($(OS),Windows_NT)
  TARGET_EXT = .exe
else
  TARGET_EXT = .out
endif

CC = gcc

UNITY_ROOT = Unity/2.3

CFLAGS  = -std=c99
CFLAGS += -Wall -Werror -MMD
CFLAGS += -DUNITY_FIXTURES
CFLAGS += -Isrc -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src

VPATH   = $(UNITY_ROOT)/src/ $(UNITY_ROOT)/extras/fixture/src/ src/ tests/

# Support coverage calculation
CFLAGS += -fprofile-arcs -ftest-coverage
LDLIBS += -lgcov

DIR_OBJS   = objs
OBJS_SRC   = $(DIR_OBJS)/fileproxy.o $(DIR_OBJS)/run.o $(DIR_OBJS)/semver.o $(DIR_OBJS)/setting.o $(DIR_OBJS)/utils.o
OBJS_MAIN  = $(DIR_OBJS)/main.o
OBJS_TEST  = $(DIR_OBJS)/TestFileProxy.o $(DIR_OBJS)/TestFileProxyRunner.o
OBJS_TEST  += $(DIR_OBJS)/TestParse.o $(DIR_OBJS)/TestParseRunner.o
OBJS_TEST  += $(DIR_OBJS)/TestSemVer.o $(DIR_OBJS)/TestSemVerRunner.o
OBJS_TEST  += $(DIR_OBJS)/TestUtils.o $(DIR_OBJS)/TestUtilsRunner.o
OBJS_TEST  += $(DIR_OBJS)/TestMain.o
OBJS_UNITY = $(DIR_OBJS)/unity.o $(DIR_OBJS)/unity_fixture.o

EXEC_NAME_TARGET = semver$(TARGET_EXT)
EXEC_NAME_TEST = semver_test$(TARGET_EXT)

all: $(EXEC_NAME_TARGET)

$(EXEC_NAME_TARGET): $(OBJS_SRC) $(OBJS_MAIN)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
	./$(EXEC_NAME_TARGET) -v


check: $(EXEC_NAME_TEST)

$(EXEC_NAME_TEST): $(OBJS_UNITY) $(OBJS_SRC) $(OBJS_TEST)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
	./$(EXEC_NAME_TEST) -v

$(DIR_OBJS)/%o: %c
	@mkdir -p $(DIR_OBJS)
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	
clean:
	rm -f $(DIR_OBJS)/*.* $(EXEC_NAME_TARGET) $(EXEC_NAME_TEST) 

