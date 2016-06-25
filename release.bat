@ECHO OFF

REM  Generate semver.exe
make clean
make

REM  Increase version number
CALL semver.exe %%1 src/version.h

REM  Re-Generate semver.exe
make clean
make

REM  Rename semver.exe with version number
CALL semver.exe -asemver.exe src/version.h

REM  Move to bin folder
mv semver_*.exe bin/

@ECHO ON