@echo off

call semver.exe %%1 src/version.h

make -f MakefileTarget init
make -f MakefileTarget

call semver.exe -asemver.exe src/version.h

@echo on