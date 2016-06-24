CC = gcc

UNITY_ROOT = Unity/2.3

CFLAGS  = -std=c99
CFLAGS += -Wall -Werror
CFLAGS += -DUNITY_FIXTURES
CFLAGS += -Isrc -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src

VPATH   = $(UNITY_ROOT)/src/ $(UNITY_ROOT)/extras/fixture/src/ src/ tests/

# Support coverage calculation
# CFLAGS += -fprofile-arcs -ftest-coverage
# LDLIBS += -lgcov

OBJS_SRC   = fileproxy.o run.o semver.o setting.o utils.o
OBJS_MAIN  = main.o
OBJS_TEST  = TestFileProxy.o TestParse.o TestSemVer.o TestUtils.o TestFileProxyRunner.o TestParseRunner.o TestSemVerRunner.o TestUtilsRunner.o TestMain.o
OBJS_UNITY = unity.o unity_fixture.o

EXEC_NAME_TARGET = semver.exe
EXEC_NAME_TEST = semver_test.exe

all: $(EXEC_NAME_TARGET)

$(EXEC_NAME_TARGET): $(OBJS_SRC) $(OBJS_MAIN)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

check: $(EXEC_NAME_TEST)

$(EXEC_NAME_TEST): $(OBJS_UNITY) $(OBJS_SRC) $(OBJS_TEST)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
	./$(EXEC_NAME_TEST) -v
	
clean:
	rm -f *.o $(EXEC_NAME_TARGET) $(EXEC_NAME_TEST) 

