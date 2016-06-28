@echo off
setlocal

REM Be careful !!!
set /p input="Did you increase version?    [Y/N]:"
if not "%input%" == "Y" goto EXIT
set /p input="Did you re-build project?    [Y/N]:"
if not "%input%" == "Y" goto EXIT
set /p input="Did you write release notes? [Y/N]:"
if not "%input%" == "Y" goto EXIT
set /p input="Did you commit all changes?  [Y/N]:"
if not "%input%" == "Y" goto EXIT

REM Prepare semver.exe
make clean
make

REM Set VERSION_STR variable
call semverenv.bat src/version.h

REM If VERSION_STR is NULL, then go to EXIT
if %VERSION_STR% == "" goto EXIT

REM Tag and push to remote server
git tag %VERSION_STR%
git push origin --tags

:EXIT
endlocal
@echo on