@echo off

make clean
make 

@echo on

call semver.exe
call semver.exe -v
call semver.exe -h
call semver.exe -i1.2.3 version.test
call semver.exe version.test
call semver.exe -x version.test
call semver.exe -y version.test
call semver.exe -z version.test
call semver.exe -z -l2 version.test
call semver.exe -aversion.test -l2 version.test 
call semver.exe -s simple.test
call semver.exe -g version.test
call semver.exe -i1.2.3 -nTESTVERSION version2.test
call semver.exe -nTESTVERSION version2.test
call semver.exe -nTESTVERSION -d version2.test
