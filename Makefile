CC = gcc

UNITY_ROOT = Unity/2.3

CFLAGS  = -std=c99
CFLAGS += -Wall
CFLAGS += -DUNITY_FIXTURES
CFLAGS += -Isrc -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src
VPATH   = $(UNITY_ROOT)/src/ $(UNITY_ROOT)/extras/fixture/src/ src/ tests/

all: semver

semver: main.o fileproxy.o run.o semver.o setting.o utils.o

check: semver_test

semver_test: unity.o unity_fixture.o fileproxy.o run.o semver.o setting.o utils.o TestFileProxy.o TestParse.o TestSemVer.o TestUtils.o TestFileProxyRunner.o TestParseRunner.o TestSemVerRunner.o TestUtilsRunner.o TestMain.o
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
	./semver_test -v
	
clean:
	rm -f *.o *.exe

